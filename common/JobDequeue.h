/*
 * IJobDequeue.h
 *
 *  Created on: 2012-2-23
 *      Author: gl
 */

#ifndef CJOBDEQUEUE_H_
#define CJOBDEQUEUE_H_

#include <list>
#include "IJob.h"
#include "head.h"

namespace omg {

class JobDequeue {
public:
	JobDequeue();
	virtual ~JobDequeue();

	void DeleteAllJob();

	bool CancelJob(IJob* job);

	void AddJob(IJob* job);

	IJob* GetJob();


	int GetJobAmount();

	protected:
		std::list<IJob*> m_jobs;
	};

	inline int JobDequeue::GetJobAmount()
	{
		return m_jobs.size();
	}

} /* namespace omg */
#endif /* CJOBDEQUEUE_H_ */
