/*
 * CDBhandlerJob.cpp
 *
 *  Created on: 2012-3-16
 *      Author: root
 */

#include "CDBhandlerJob.h"
#include "../message/message_define.h"
#include "CServerManage.h"

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
            if(event->operate_type == QUERY_LOGIN_INFO)
            {
                QueryClientLoginInfo(event);
            }
            else if(event->operate_type == COMMON_UPDATE_DEL)
            {
                DoCommonDelOrUpdate(event); 
            }
            else
            {
                DoCommonInsert(event); 
            }
            delete event;
        }
    }
}

void CDBQueryhandlerJob::QueryClientLoginInfo(db_event* event)
{
    mysqlpp::Query query = _conn->query(event->sql_str.c_str());
    cs_client_login_response response;
    if(mysqlpp::StoreQueryResult ret = query.store())
    {
        LOG(INFO)<<"found "<<ret.num_rows();
        response.body.set_ret(1);
        response.body.set_player_id(ret[0]["uid"]);
        response.body.set_player_name(ret[0]["real_name"]);
    }else
    {
        response.body.set_ret(-2);
        LOG(INFO)<<"nothing found!!"; 
    }
    game_client_spr ptr = CServerManage::GetInstance()->GetGameServerByIndex(event->seq);
    if(ptr)
    {
        ptr->send_packet_msg(&response); 
    }
}

void CDBQueryhandlerJob::DoCommonDelOrUpdate(db_event* event)
{
    mysqlpp::Query query = _conn->query(event->sql_str.c_str()); 
    mysqlpp::SimpleResult ret = query.execute();
    if(!ret)
    {
        LOG(ERROR)<<"-1:"<<query.error();
        return; 
    }
    if(ret.rows() <= 0)
    {
        LOG(ERROR)<<"-1:"<<event->sql_str.c_str();
    }
    else
    {
        LOG(INFO)<<"1:"<<event->sql_str.c_str(); 
    }
}

int CDBQueryhandlerJob::DoCommonInsert(db_event* event)
{
    mysqlpp::Query query = _conn->query(event->sql_str.c_str());
    mysqlpp::SimpleResult ret = query.execute();
    if(!ret)
    {
        LOG(ERROR)<<"-1:"<<query.error();
        return -1; 
    }
    LOG(INFO)<<"1:"<<event->sql_str.c_str();
    return ret.insert_id(); 
}

