#ifndef _TEST_JOB_H_
#define _TEST_JOB_H_

#include "../common/IJob.h"
#include "stdio.h"


class TestJob : public omg::IJob
{
	public:
		TestJob(){}
		virtual ~TestJob(){}
		virtual void ExecuteJob(){
			VLOG(1)<<"EXECUTE JOB";
		}

};


#endif
