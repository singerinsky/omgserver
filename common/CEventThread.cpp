/*
 * CEventThread.cpp
 *
 *  Created on: 2012-2-22
 *      Author: gl
 */

#include "CEventThread.h"

namespace omg {

CEventThread::CEventThread(int threadnum) {
	m_runflag = true;
	m_work = false;
	m_threadnum = threadnum;
	m_job = NULL;
	m_mutex_lock.init();
	_deal_work_count = 0;
}

CEventThread::~CEventThread() {
	// TODO Auto-generated destructor stub
}

void CEventThread::Run()
{
	while(m_runflag)
	{
		if(NULL != m_job)
		{
			m_work = true;
			m_job->ExecuteJob();
			m_mutex_lock.lock();
			m_work = false;
			delete m_job;
			m_job = NULL;
			m_mutex_lock.unlock();
		}
		else
		{
			OSSleep(0);
		}
	}
}


void CEventThread::SetJob(IJob* job)
{
	m_mutex_lock.lock();
	m_job = job;
	m_work = true;
	ThreadSuspend();
	m_mutex_lock.unlock();
	_deal_work_count++;
}

} /* namespace omg */
