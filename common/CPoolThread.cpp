/*
 * CPoolThread.cpp
 *
 *  Created on: 2012-2-22
 *      Author: gl
 */

#include "CPoolThread.h"

namespace omg{
CPoolThread::CPoolThread(int num,int max_thread) {
	m_list_thread.clear();
	m_threadnum = num;
	max_thread_num = max_thread;
	m_runflag = true;
	m_mutex.init();
}

CPoolThread::~CPoolThread() {
	// TODO Auto-generated destructor stub
}

void CPoolThread::ExitInstance(){
	if(!m_list_thread.empty()){
		LIST_THREAD::iterator itr;
		for(itr = m_list_thread.begin();itr!= m_list_thread.end();itr++)
		{
			CEventThread* ptThread = *itr;
			ptThread->StopThread();
			THREAD_HANDLE tid = ptThread->GetHandle();
			if(pthread_join(tid,NULL)){
				return;
			}
			delete ptThread;
		}
	}
	m_list_thread.clear();
}

bool CPoolThread::InitInstance(){
	for(int i = 0; i < m_threadnum; i++)
	{
		VLOG(3)<<"Create thread"<<i;	
		CEventThread* pthread = new CEventThread(i);
		if(NULL != pthread)
		{
			pthread->Create();
	//		pthread->ThreadResume();
			m_list_thread.push_back(pthread);
		}
	}
	return true;
}

CEventThread* CPoolThread::AddNewThread(){
	m_threadnum++;
	CEventThread* pthread = new CEventThread(m_threadnum);
	if(NULL != pthread){
		pthread->Create();
		m_list_thread.push_back(pthread);
		VLOG(1)<<"add new thread";
		return pthread;
	}
	return NULL;
}


CEventThread* CPoolThread::GetIdleThread()
{
	m_mutex.lock();
	LIST_THREAD::iterator itr;
	CEventThread* pthread = NULL;
	for(itr = m_list_thread.begin(); itr != m_list_thread.end(); itr++)
	{
		pthread = *itr;
		if(!pthread->GetBusyFlag())
		{
			m_mutex.unlock();
			return pthread;
		}
	}
	//all thread is busy ,create new one
	if(m_list_thread.size() > (unsigned int)max_thread_num){
		m_mutex.unlock();
		return NULL;
	}
	pthread = AddNewThread();
	m_mutex.unlock();
	return pthread;
}

void CPoolThread::Run()
{
	int num = 0;
	CEventThread* pthread = NULL;
	while(m_runflag)
	{
		m_mutex.lock();
		num = m_dequeue.GetJobAmount();
		m_mutex.unlock();
		if(0 != num)
		{
			for(int i=0; i< num; i++)
			{
				pthread =  GetIdleThread();
				if(NULL != pthread)
				{
					pthread->SetJob(m_dequeue.GetJob());
				}
			}
		}
		else
		{
			VLOG(1)<<"no job will block ..........";
			//OSSleep(1);
			VLOG(1)<<"job continue ........";
		}
	}
}


void CPoolThread::StopThreadPool()
{
	m_mutex.lock();
	m_runflag = false;
	m_mutex.unlock();
}

bool CPoolThread::AddJob(IJob* job)
{
	CEventThread* thread = GetIdleThread();
	if(thread != NULL){
		thread->SetJob(job);
		return true;
	}else{
		return false;
	}
//	ThreadSuspend();
}

void CPoolThread::CancelJob(IJob* job)
{
/*	m_mutex.lock();
	m_dequeue.CancelJob(job);
	m_mutex.unlock();
*/
}

bool CPoolThread::SuspendJob(IJob* job)
{
	m_mutex.lock();
	LIST_THREAD::iterator itr;
	CEventThread* pthread = NULL;
	for(itr = m_list_thread.begin(); itr != m_list_thread.end(); itr++)
	{
		pthread = *itr;
		if(job == pthread->GetJob())
		{
			pthread->ThreadSuspend();
			m_mutex.unlock();
			return true;
		}
	}
	m_mutex.unlock();
	return false;
}

bool CPoolThread::ResumeJob(IJob* job)
{
	m_mutex.lock();
	LIST_THREAD::iterator itr;
	CEventThread* pthread = NULL;
	for(itr = m_list_thread.begin(); itr != m_list_thread.end(); itr++)
	{
		pthread = *itr;
		if(job == pthread->GetJob())
		{
			pthread->ThreadResume();
			m_mutex.unlock();
			return true;
		}
	}
	m_mutex.unlock();
	return false;
}

}
