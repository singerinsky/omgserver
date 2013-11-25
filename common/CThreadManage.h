/*
 * CThreadManage.h
 *
 *  Created on: 2012-2-22
 *      Author: gl
 */

#ifndef CTHREADMANAGE_H_
#define CTHREADMANAGE_H_
#include <list>
#include "CEventThread.h"
#include "CThread.h"
#include "lock.h"
#include "CPoolThread.h"
#include "IJob.h"


namespace omg {

class CThreadManage {
public:
	  ~CThreadManage();

	  static void ClosePoolThread();

	  static bool BeginPoolThread(int num,int max_num);

	  static bool AddJob(IJob* job);

	  static void CancelJob(IJob* job);

	  static bool SuspendJob(IJob* job);

	  static bool ResumeJob(IJob* job);

	  //static THREAD_HANDLE GetHandle();
protected:
	   CThreadManage();
private:
	  static CPoolThread* m_pool_thread;
	  MutexLock m_lock;
};

} /* namespace omg */
#endif /* CTHREADMANAGE_H_ */
