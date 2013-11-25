/*
 * CThread.cpp
 *
 *  Created on: 2012-2-22
 *      Author: gl
 */

#include "CThread.h"
namespace omg{

extern unsigned int g_nThreadStackSize;

void * _ThreadEntry(void *pParam){
	CThread* pThread = (CThread*)pParam;
	if(pThread->InitInstance()){
		pThread->Run();
	}

	pThread->ExitInstance();
	return NULL;

}

CThread::CThread() {
	m_hThread = 0;
	pthread_mutex_init(&m_mutex,NULL);
	pthread_cond_init(&m_cond,NULL);
}

CThread::~CThread() {
	// TODO Auto-generated destructor stub
}

bool CThread::Create(){
	bool ret = true;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	ret = (::pthread_create(&m_hThread,&attr,&_ThreadEntry,this)==0);
	return ret;
}

bool CThread::InitInstance(){
	return true;
}

void CThread::ExitInstance(){
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
}


void CThread::OSSleep(int seconds)
{
	ThreadResume(NULL);
}


THREAD_HANDLE CThread::GetCurrentHandle()
{
	return ::pthread_self();
}

void CThread::ThreadResume(timespec *time_wait){
	pthread_mutex_lock(&m_mutex);
	timespec tm;
	timeval now;
	if(time_wait == NULL){
		gettimeofday(&now,NULL);
		tm.tv_sec = now.tv_sec + 60*60*24*365;
		tm.tv_nsec = now.tv_usec + 0;	
		time_wait = &tm;
	}
	pthread_cond_timedwait(&m_cond,&m_mutex,time_wait);
	pthread_mutex_unlock(&m_mutex);
}

void CThread::ThreadSuspend(){
	pthread_mutex_lock(&m_mutex);
	pthread_cond_signal(&m_cond);
	pthread_mutex_unlock(&m_mutex);
}
}










