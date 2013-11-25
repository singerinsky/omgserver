/*
 * CMatchTaskManage.h
 *
 *  Created on: 2012-8-27
 *      Author: guanlei
 */

#ifndef CMATCHTASKMANAGE_H_
#define CMATCHTASKMANAGE_H_
#include <list>
using namespace std;

class CMatchTaskManage {
public:
	CMatchTaskManage();
	virtual ~CMatchTaskManage();

protected:
	static CMatchTaskManage* _m_instance;
/*	std::list<CDBQueryhandlerJob*>::iterator _next_process;
	std::list<CDBQueryhandlerJob*> _job_list;*/
};

#endif /* CMATCHTASKMANAGE_H_ */
