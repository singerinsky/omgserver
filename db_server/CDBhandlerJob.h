/*
 * CDBhandlerJob.h
 *
 *  Created on: 2012-3-16
 *      Author: root
 */

#ifndef CDBHANDLERJOB_H_
#define CDBHANDLERJOB_H_

#include <sstream>
#include "../net/IMsgDispatcher.h"
#include "../common/IJob.h"
#include "../common/lock.h"
#include "../common/queue.h"
#include <mysql++/mysql++.h>
#include "DBConnectionPool.h"

using namespace omg;
class db_event
{
    public:
        int seq;
        std::string sql_str;
};

class CDBQueryhandlerJob: public omg::IJob {
    public:
        CDBQueryhandlerJob(DBConnectionPool* pool,int number):_conn(*pool,true){
            _task_all = 0;
            _task_processed = 0;
            _id = number;
        };
        virtual ~CDBQueryhandlerJob();
        virtual void ExecuteJob();
        void 	AddTask(db_event *event);

        int		GetTaskInProcess(){
            return _task_all - _task_processed;
        }
        int getId(){
            return _id;
        }
    private:
        mysqlpp::ScopedConnection _conn;
        int  _task_all;
        int  _task_processed;
        int  _id;

        void QueryClientLoginInfo(db_event*);
    private:
        omg::ConcurrenceLockQueue<db_event,omg::MutexLock>	_msg_queue;
        //omg::WRQueue<CMsgEvent,omg::MutexLock>	_msg_queue;

};

#endif /* CDBHANDLERJOB_H_ */
