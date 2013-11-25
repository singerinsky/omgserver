/*
 * CThreadManage.cpp
 *
 *  Created on: 2012-2-22
 *      Author: gl
 */

#include "CThreadManage.h"

namespace omg {

CPoolThread* CThreadManage::m_pool_thread = NULL;

CThreadManage::CThreadManage() {
	// TODO Auto-generated constructor stub

}

CThreadManage::~CThreadManage() {
	// TODO Auto-generated destructor stub
}



bool CThreadManage::AddJob(IJob* job)
{
	return m_pool_thread->AddJob(job);
}

void CThreadManage::CancelJob(IJob* job)
{
	m_pool_thread->CancelJob(job);
}

void CThreadManage::ClosePoolThread()
{
	if(NULL != m_pool_thread)
	{
		m_pool_thread->ExitInstance();
	}
}


bool CThreadManage::BeginPoolThread(int num,int max_thread)
{
	bool create = false;
	m_pool_thread = new CPoolThread(num,max_thread);
	if(NULL != m_pool_thread)
	{
		create = m_pool_thread->InitInstance();
	}
	return create;
}

bool CThreadManage::SuspendJob(IJob* job)
{
	return m_pool_thread->SuspendJob(job);
}

bool CThreadManage::ResumeJob(IJob* job)
{
	return m_pool_thread->ResumeJob(job);
}

} /* namespace omg */
