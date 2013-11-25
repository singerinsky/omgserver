/*
 * JobDequeue.cpp
 *
 *  Created on: 2012-2-23
 *      Author: gl
 */

#include "JobDequeue.h"

namespace omg {

JobDequeue::JobDequeue()
{
}

JobDequeue::~JobDequeue()
{
}

void JobDequeue::DeleteAllJob()
{
	std::list<IJob*>::iterator itr = this->m_jobs.begin();
	while(itr != this->m_jobs.end()){
		delete *itr;
		itr++;
	}
}


bool JobDequeue::CancelJob(IJob* job)
{
	if(NULL == job)
	{
		return false;
	}

	std::list<IJob*>::iterator itr = this->m_jobs.begin();
	while(itr != this->m_jobs.end()){
		if(*itr == job){
			this->m_jobs.erase(itr);
			break;
		}
		itr++;
	}
	return true;
}

void JobDequeue::AddJob(IJob* job)
{
	if(NULL == job)
	{
		return;
	}

	this->m_jobs.push_back(job);
}

IJob* JobDequeue::GetJob()
{
	return *(this->m_jobs.begin());
}


} /* namespace omg */
