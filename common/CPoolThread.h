/*
 * CPoolThread.h
 *
 *  Created on: 2012-2-22
 *      Author: gl
 */

#ifndef CPOOLTHREAD_H_
#define CPOOLTHREAD_H_

#include "CThread.h"
#include "JobDequeue.h"
#include "CEventThread.h"

namespace omg{

typedef std::list<CEventThread*> LIST_THREAD;

class CPoolThread{// public omg::CThread {
public:
	CPoolThread(int,int);
	virtual ~CPoolThread();

	virtual void Run();
	virtual void ExitInstance();
	virtual bool InitInstance();
	CEventThread* GetIdleThread();

	int GetThreadNum();

	void StopThreadPool();

	bool AddJob(IJob* job);

	void CancelJob(IJob* job);

	bool SuspendJob(IJob* job);

	bool ResumeJob(IJob* job);
protected:
	CEventThread* AddNewThread();


protected:
		int m_threadnum;
		int max_thread_num;
		LIST_THREAD	m_list_thread;
		bool m_runflag;
		MutexLock m_mutex;
		JobDequeue	m_dequeue;

};

}

#endif /* CPOOLTHREAD_H_ */
