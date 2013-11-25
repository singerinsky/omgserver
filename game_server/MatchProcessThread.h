/*
 * MatchProcessThread.h
 *
 *  Created on: 2012-11-5
 *      Author: guanlei
 */

#ifndef MATCHPROCESSTHREAD_H_
#define MATCHPROCESSTHREAD_H_

#include "../net/thread.h"
#include "../common/queue.h"
#include "RunMatchJob.h"

class MatchProcessThread: public omg::Thread {
public:
	MatchProcessThread(int process_thread_id,const char* name=NULL):Thread(name){
		_thread_id = process_thread_id;
	}
	virtual ~MatchProcessThread();
	void* on_run();
	void		add_job_to_queue(RunMatchJob* job){
		_job_queue.enqueue(job);
	}

protected:
	omg::ConcurrenceQueue<RunMatchJob,omg::MutexLock,omg::MutexLock>	_job_queue;
	int _thread_id;
};

#endif /* MATCHPROCESSTHREAD_H_ */
