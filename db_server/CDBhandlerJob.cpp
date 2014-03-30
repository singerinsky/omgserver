/*
 * CDBhandlerJob.cpp
 *
 *  Created on: 2012-3-16
 *      Author: root
 */

#include "CDBhandlerJob.h"

CDBQueryhandlerJob::~CDBQueryhandlerJob() {
    // TODO Auto-generated destructor stub
}

void CDBQueryhandlerJob::AddTask(db_event* event) {
    this->_task_all++;
    this->_msg_queue.enqueue(event);
}

void CDBQueryhandlerJob::ExecuteJob() {
    while(1){
        db_event* event = _msg_queue.dequeue();
        if (event != NULL) {
            this->_task_processed++;
            QueryClientLoginInfo(event);
            delete event;
        }
    }
}

void CDBQueryhandlerJob::QueryClientLoginInfo(db_event* event)
{
    LOG(INFO)<<"DO SQL QUREY";
    LOG(INFO)<<event->sql_str.c_str();
    mysqlpp::Query query = _conn.query(event->sql_str.c_str());
    if(mysqlpp::StoreQueryResult ret = query.store())
    {
        LOG(INFO)<<"found "<<ret.num_rows();
    }else
    {
        LOG(INFO)<<"nothing found!!"; 
    }
}


