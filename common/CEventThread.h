/*
 * CEventThread.h
 *
 *  Created on: 2012-2-22
 *      Author: gl
 */

#ifndef CEVENTTHREAD_H_
#define CEVENTTHREAD_H_

#include "CThread.h"
#include "IJob.h"
#include "lock.h"

namespace omg {

class CEventThread: public omg::CThread {
public:
	CEventThread(int threadnum=0);
	virtual ~CEventThread();

	virtual void Run();
	void StopThread();
	bool GetBusyFlag();
	void SetJob(IJob*);

	IJob* GetJob();
	int 	GetWorkProcess();

protected:
	bool m_work;
	bool m_runflag;
	IJob* m_job;

public:
	int	_deal_work_count;
	int m_threadnum;
	MutexLock	m_mutex_lock;

};

inline bool CEventThread::GetBusyFlag()
{
	return m_work;
}

inline IJob* CEventThread::GetJob()
{
	return m_job;
}

inline void CEventThread::StopThread()
{
	m_mutex_lock.lock();
	m_runflag = false;
	m_mutex_lock.unlock();
}

inline int CEventThread::GetWorkProcess(){
	return this->_deal_work_count;
}
}


/* namespace omg */
#endif /* CEVENTTHREAD_H_ */
