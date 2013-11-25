/*
 * MatchProcessThread.cpp
 *
 *  Created on: 2012-11-5
 *      Author: guanlei
 */

#include "MatchProcessThread.h"

MatchProcessThread::~MatchProcessThread() {
	// TODO Auto-generated destructor stub
}

void* MatchProcessThread::on_run(){
	while(1){
		RunMatchJob* job = _job_queue.dequeue();
		if (job != NULL) {
			job->ExecuteJob();
			delete job;
		}else{
			timespec ts;
			ts.tv_nsec = 500000000;
			ts.tv_sec = 0;
			nanosleep(&ts,NULL);
		}
	}
	return NULL;
}
