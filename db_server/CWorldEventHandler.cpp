/*
 * CWorldEventHandler.cpp
 *
 *  Created on: 2012-3-19
 *      Author: root
 */

#include "CWorldEventHandler.h"
#include "CServerManage.h"

CWorldEventHandler::CWorldEventHandler(DBConnectionPool* pool,IMsgDispatcher* msg_dispatcher):_connection(*pool,true),_msg_dispatcher(msg_dispatcher) {
	// TODO Auto-generated constructor stub
	_is_final = false;
}

CWorldEventHandler::~CWorldEventHandler() {
	// TODO Auto-generated destructor stub
}


void CWorldEventHandler::ExecuteJob(){
	if(_connection->connected() == false){
		LOG(ERROR)<<"Error of connection server db";
		exit(1);
	}
	
	process_server_dump();

	//每10秒扫描下配置文件
	while(!is_final()){
		int online_server_count = CServerManage::GetInstance()->GetMatchServerOnlineCount();
		if(online_server_count == 0){
			usleep(1000000);
			continue;
		}

		int time_now = time(NULL);
		std::ostringstream strbuff;
		strbuff<<"select * from c_fixture where flag <=2 and flag!= 1 and flag !=-1 limit 200";
		mysqlpp::Query query = _connection->query(strbuff.str().c_str());
		mysqlpp::StoreQueryResult res = query.store();
		if(res.num_rows() <= 0){
			usleep(500000);
		}else{
			//TODO
			std::ostringstream strbuff1,strbuff2,strbuff3;
			strbuff1 << "update c_fixture set flag = 1 where mid in(";
			strbuff2 << "update c_fixture set flag = 3 where mid in (";
			bool is_first = false;
			bool is_first2 = false;
			for(size_t i = 0; i < res.num_rows(); ++i) {
				int flag = res[i]["flag"];
				if(flag == 0){//tell db to init match data
					struct MsgInitMatch* msg = new MsgInitMatch();
					msg->mid = res[i]["mid"];
					msg->cid = res[i]["cid"];
					msg->op_cid = res[i]["op_cid"];
					msg->is_new_bie = res[i]["newbie_stat"];
					msg->need_win = res[i]["need_win"];
					msg->match_typ = res[i]["typ"];
					msg->is_home_all_attack = res[i]["has_home_buff"];
					msg->total_time_scale = res[i]["total_time_scale"];
					CMsgEvent* event = new CMsgEvent();
					event->_msg_type = msg->msg_type;
					event->_msg_base = msg;
					_msg_dispatcher->add_msg_to_queue(event);
					if(is_first == false){
						strbuff1<<res[i]["mid"];
						is_first = true;
					}else{
						strbuff1<<","<<res[i]["mid"];
					}
				}else if(flag == 2){//tell game to run match
					//自驱动比赛
					MsgRunMatch* msg = new MsgRunMatch();
					CMsgEvent* event= new CMsgEvent();
					msg->mid = res[i]["mid"];
					event->_msg_type = msg->msg_type;
					event->_msg_base = msg;
					_msg_dispatcher->add_msg_to_queue(event);
					if(is_first2 == false){
						is_first2 = true;
						strbuff2<<res[i]["mid"];
					}else{
						strbuff2<<","<<res[i]["mid"];
					}
				}
			}
			strbuff1<<")";
			strbuff2<<")";
			if(is_first){
				VLOG(1)<<strbuff1.str().c_str();
				mysqlpp::Query query1 = _connection->query(strbuff1.str().c_str());
				query1.store();	
			}
			if(is_first2){
				VLOG(1)<<strbuff2.str().c_str();
				mysqlpp::Query query2 = _connection->query(strbuff2.str().c_str());
				query2.store();
			}
//			mysqlpp::Query query = _connection->query("select * from c_fixture where mid = ");
//			VLOG(1)<<"do action";
			usleep(500000);
		}
	}
}

void CWorldEventHandler::process_server_dump(){
	std::ostringstream strbuff;
	strbuff<<"select * from c_fixture where flag=3 or flag=1";
	mysqlpp::Query query = _connection->query(strbuff.str().c_str());
	mysqlpp::StoreQueryResult res = query.store();
	if(res.num_rows() <= 0){
		return;
	}
	std::ostringstream str_tmp,str_del,str_event;
	str_tmp<<"UPDATE c_fixture set flag= 0 where mid in(";
	str_del <<"DELETE FROM match_action where mid in (";
	time_t zeit= time(NULL);
	str_event<<"update e_user set flag=0,zeit=";
	str_event<<zeit;
	str_event<<"+900 where typ=3 and flag=0 and mapping_id in(";
	for(size_t i = 0; i < res.num_rows(); ++i) {
		int mid = res[i]["mid"];
		str_tmp<<mid;
		str_del<<mid;
		str_event<<mid;
		if(i != (res.num_rows()-1)){
			str_tmp<<",";
			str_del<<",";
			str_event<<",";
		}
	}
	str_tmp<<")";
	str_del<<")";
	str_event<<")";
	VLOG(0)<<str_tmp.str().c_str();
	VLOG(0)<<str_del.str().c_str();
	VLOG(0)<<str_event.str().c_str();

	mysqlpp::Query query_update = _connection->query(str_tmp.str().c_str());
	query_update.store();
	mysqlpp::Query query_del = _connection->query(str_del.str().c_str());
	query_del.store();
	mysqlpp::Query query_ev = _connection->query(str_event.str().c_str());
	query_ev.store();
}

void CWorldEventHandler::check_server_status(){
	std::ostringstream strbuff;
	strbuff<<"SELECT * FROM match_server_config WHERE last_update_zeit = 0";
	mysqlpp::Query query = _connection->query(strbuff.str().c_str());
	mysqlpp::StoreQueryResult res = query.store();
	if(res.num_rows() <= 0){
		return;
	}
	for(size_t i = 0; i < res.num_rows(); ++i) {
		//int server_index  =
		int gs_run_status = res[i]["gs_run_status"];
	}
}
