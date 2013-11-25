/*
 * CThread.h
 *
 *  Created on: 2012-2-22
 *      Author: gl
 */

#ifndef CTHREAD_H_
#define CTHREAD_H_

#include <pthread.h>
#include "../common/head.h"

namespace omg{
typedef pthread_t THREAD_HANDLE;

class CThread {
public:
	CThread();
	virtual ~CThread();
	virtual bool Create();
	virtual void Run()=0;
	virtual bool InitInstance();
	virtual void ExitInstance();
	inline	THREAD_HANDLE	GetHandle();

	void OSSleep(int seconds);

	static THREAD_HANDLE GetCurrentHandle();

	void ThreadResume(struct timespec *time=NULL);

	void ThreadSuspend();

private:

	THREAD_HANDLE m_hThread;

public:
	pthread_mutex_t m_mutex;
	pthread_cond_t m_cond;


};

inline THREAD_HANDLE CThread::GetHandle(){
	return m_hThread;
}

}
#endif /* CTHREAD_H_ */
