/*
 * CWorldEventHandler.h
 *
 *  Created on: 2012-3-19
 *      Author: root
 */

#ifndef CWORLDEVENTHANDLER_H_
#define CWORLDEVENTHANDLER_H_

#include <mysql++/mysql++.h>
#include "../net/IMsgDispatcher.h"
#include "../common/IJob.h"
#include "DBConnectionPool.h"
#include "DBEvent.h"
#include <time.h>

class CWorldEventHandler: public omg::IJob {
public:
	CWorldEventHandler(DBConnectionPool* pool,IMsgDispatcher*);
	virtual ~CWorldEventHandler();
	void ExecuteJob();
	bool is_final(){
		return _is_final;
	}
	void set_final(bool set_final){
		_is_final = set_final;
	}
	void process_server_dump();

	void check_server_status();
private:
	mysqlpp::ScopedConnection _connection;
	IMsgDispatcher* _msg_dispatcher;
	bool _is_final;
};

#endif /* CWORLDEVENTHANDLER_H_ */
