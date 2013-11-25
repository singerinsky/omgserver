/*
 * CDBTaskManage.h
 *
 *  Created on: 2012-3-22
 *      Author: guanlei
 */

#ifndef CDBTASKMANAGE_H_
#define CDBTASKMANAGE_H_
#include <list>
#include "CDBhandlerJob.h"
using namespace std;

class CDBTaskManage {
public:
	CDBTaskManage(){
		_next_process = _job_list.begin();
	}
	virtual ~CDBTaskManage();
	static CDBTaskManage* GetInstance(){
		if(_m_instance == NULL){
			_m_instance = new CDBTaskManage();
		}
		return _m_instance;
	}

	void AddProcessThread(CDBQueryhandlerJob* job){
		_job_list.push_back(job);
	}

	void AddTaskEvent(CMsgEvent* event){
		if(_next_process == _job_list.end()){
			_next_process = _job_list.begin();
		}
		(*_next_process)->AddTask(event);
		_next_process++;
	}

private:
	static CDBTaskManage* _m_instance;
	std::list<CDBQueryhandlerJob*>::iterator _next_process;
	std::list<CDBQueryhandlerJob*> _job_list;
};

#endif /* CDBTASKMANAGE_H_ */
