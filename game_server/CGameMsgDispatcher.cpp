/*
 * CGameMsgDispatcher.cpp
 *
 *  Created on: 2012-2-2
 *      Author: guanlei
 */

#include "CGameMsgDispatcher.h"

extern int server_index;

CGameMsgDispatcher::~CGameMsgDispatcher() {
	// TODO Auto-generated destructor stub
}

void* CGameMsgDispatcher::on_run(void) {
	while (!is_final()) {
		dispatch_msg();
	}
	return NULL;
}

bool CGameMsgDispatcher::check_msg_valide(CMsgEvent* msg_event) {
	return true;
}

bool CGameMsgDispatcher::add_msg_to_queue(CMsgEvent* msg_event,
		EPollSocket *socket) {
	if (check_msg_valide(msg_event)) {
		this->_msg_queue.enqueue(msg_event);
	} else {
		LOG(ERROR)<<"error msg.......";
	}

    return true;
}

void CGameMsgDispatcher::dispatch_msg() {
	CMsgEvent* event = _msg_queue.dequeue();
	if (event != NULL) {
		int msg_type = event->_msg_type;
		switch (msg_type) {
		case MSG_TYPE_CLIENT_CHANGE_FORMATION:
		{
			VLOG(1)<<"客户端换阵型卡!!!";
			MsgClientChangeFormation* data = (MsgClientChangeFormation*)event->_msg_base;
			int rst = VerifyOperate(data->mid,data->cid,MSG_TYPE_CLIENT_CHANGE_FORMATION,data->time,public_key,data->code);
			if(rst != 0){
				VLOG(1)<<"未验证通过的操作！！！";
			}else{
				VLOG(1)<<"操作成功！";
				int mid = data->mid;
				Match* match = CMatchManager::GetInstance()->GetMatch(mid);
				if(match != NULL){
					SoccerMatch* soccer_match = match->get_move();
					SoccerTeam* team = soccer_match->get_team_by_cid(data->cid);
					team->set_current_formation_card_id(data->formation_id);
				}
			}
			delete[] (char*)data;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_CLIENT_CHANGE_MOVE:
		{
			VLOG(1)<<"客户端换进攻卡";
			MsgClientChangeMove* msg = (MsgClientChangeMove*)event->_msg_base;
			int rst = VerifyOperate(msg->mid,msg->cid,MSG_TYPE_CLIENT_CHANGE_MOVE,msg->time,public_key,msg->code);
			if(rst != 0){
				VLOG(1)<<"未验证通过的操作!!";
			}else{
				VLOG(1)<<"操作成功！";
				int mid = msg->mid;
				Match* match = CMatchManager::GetInstance()->GetMatch(mid);
				if(match != NULL){
					SoccerMatch* soccer_match = match->get_move();
					SoccerTeam *team = soccer_match->get_team_by_cid(msg->cid);
					team->set_current_move_card_id(msg->move_id);
				}
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		//换人
		case MSG_TYPE_CLIENT_CHANGE_PLAYER:
		{
			VLOG(1)<<"客户端换人";
			MsgClientChangePlayer* msg = (MsgClientChangePlayer*)event->_msg_base;
			int rst = VerifyOperate(msg->mid,msg->cid,MSG_TYPE_CLIENT_CHANGE_PLAYER,msg->time,public_key,msg->code);
			if(rst != 0){
				VLOG(1)<<"未验证通过的操作!!";
			}else{
				VLOG(1)<<"操作成功！";
				int mid = msg->mid;
				Match* match = CMatchManager::GetInstance()->GetMatch(mid);
				if(match != NULL){
					VLOG(1)<<"换人。。。。。";
					match->set_new_formation(msg->cid,msg->new_formation_pos_map_pid,msg->new_suitable);
				}
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_CLIENT_COACH_SPEAK:
		{
			VLOG(1)<<"教练的训导！";
			MsgClientCoachSpeak *msg = (MsgClientCoachSpeak*)event->_msg_base;
			int rst = VerifyOperate(msg->mid,msg->cid,MSG_TYPE_CLIENT_COACH_SPEAK,msg->time,public_key,msg->code);
			if(rst != 0){
				LOG(ERROR)<<"ERROR OF COCAH SPEAK!";
			}else{
				int mid = msg->mid;
				Match* match = CMatchManager::GetInstance()->GetMatch(mid);
				if(match != NULL){
					SoccerTeam* team = match->get_move()->get_team_by_cid(msg->cid);
					team->coach_speak_effect(msg->speak_type);					
					LOG(INFO)<<"喊话操作！！"<<msg->speak_type;
				}

				MsgClientSpeakBrocast	borcast_msg;
				borcast_msg.mid = mid;
				borcast_msg.cid = msg->cid;
				borcast_msg.speak_type = msg->speak_type;
				match->borcast_all_gate((const char*)&borcast_msg,borcast_msg.msg_size);
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_CLIENT_TERMINAL_MATCH:
		{
			VLOG(1)<<"客户端请求快速结束比赛!";
			MsgClientTerminalMatch* msg = (MsgClientTerminalMatch*)(event->_msg_base);
			int rst = VerifyOperate(msg->mid,msg->cid,MSG_TYPE_CLIENT_TERMINAL_MATCH,msg->time,public_key,msg->code);
			if(rst != 0){
				VLOG(1)<<"未验证通过的操作!!";
			}else{
				VLOG(1)<<"操作成功！";
				int mid = msg->mid;
				Match* match = CMatchManager::GetInstance()->GetMatch(mid);
				if(match != NULL){
					match->set_quick_terminal(true);
				}
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		//挑战匹配成功
		case MSG_TYPE_CLIENT_MATCHING_SUCCESS:
		{
			MsgServerMatchingSuccess* msg = (MsgServerMatchingSuccess*)(event->_msg_base);
			//生成key，记录gate的信息
			ArenaMatchInfo* match_info = new ArenaMatchInfo();
			match_info->uid = msg->home_uid;
			match_info->op_uid = msg->away_uid;
			match_info->_conn = event->_msg_from;
			int wait_id = CMatchManager::GetInstance()->GetNewWaitId();
			snprintf(match_info->key,30,"%d_%d_%d",wait_id,msg->home_uid,msg->away_uid);
			CMatchManager::GetInstance()->AddArenaWaitPair(match_info->key,match_info);

			//发送msg通知db
			MsgMatchArenaStartArena* db_msg = new MsgMatchArenaStartArena();
			db_msg->away_cid = msg->away_uid;
			db_msg->home_cid = msg->home_uid;
			db_msg->key = wait_id;
			_connection_to_db->SendMsg((MsgBase*)db_msg);

			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_SERVER_REQ: {
			LOG(INFO)<<"gate server quest info";
			MsgServerReq msg;
			msg._index = server_index;
			msg._server_typ = 2;
			event->_msg_from->sendData((const char*)&msg,sizeof(msg));
			CSocketClient* client = (CSocketClient*)(event->_msg_from);
			GateConManager::GetInstance()->ModiferConnectionToRegister(client->get_socket_ip_port_info());
		}
		break;
		case MSG_TYPE_MATCH_INFO:
		{
			MsgMatchTeamInfo* msg = (MsgMatchTeamInfo*)event->_msg_base;
			FixtureInfo * info = new FixtureInfo(msg);
			Match *match = new Match(info,msg->mid,info->type,info->u1.uid,info->u2.uid);
			match->get_move();
			//更新球员的属性
			match->update_player_info(info,0,0);
			//更新球队的属性
			match->set_team_info(info);
			match->set_team_skill_info(*msg);
			int rst = CMatchManager::GetInstance()->AddMatch(msg->mid,match);
			info->init_lineup_score();
			if(rst == 0){
				LOG(ERROR)<<"重复比赛数据"<<msg->mid;
			}

			LOG(INFO)<<"Match "<<msg->mid<<"is ready ,wait for player enter ";
			//如果是实况杯，通知gate
			if(info->type == 3 || info->type == 4){
				char	key[30];
				memset(key,'\0',30);
				snprintf(key,30,"%d_%d_%d",msg->match_key,msg->op1.uid,msg->op2.uid);
				LOG(INFO)<<"match key "<<key;
				ArenaMatchInfo* pair_info = CMatchManager::GetInstance()->GetArenaWaitPair(key);
				if(pair_info != NULL ){
					MsgArenaerMatchingSuccessAck ack;
					ack.mid = match->get_match_id();
					ack.uid = msg->op1.uid;
					ack.op_uid = msg->op2.uid;
					IConnection* conn = pair_info->_conn;
					conn->sendData((const char*)&ack,ack.msg_size);
					LOG(INFO)<<"send message to gate to tell match is ready"<<ack.mid;
				}

			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_CLIENT_PVN_MATCH_START:
		{
			MsgClientPVNStartMatch* msg = (MsgClientPVNStartMatch*)event->_msg_base;
			int mid = msg->mid;
			Match* match = CMatchManager::GetInstance()->GetMatch(mid);
			MsgClientStartMatchAck ack_msg;
			ack_msg.cid = msg->cid;
			ack_msg.mid = mid;
			ack_msg.depoist_change_player = false;
			ack_msg.depoist_use_skill	 = false;

			if(match != NULL){
				ack_msg.rst = 1;
				IConnection* conn = event->_msg_from;
				if(conn && (conn->connected())){
					LOG(INFO)<<"Add gate server"<<conn->getConnectionId()<<" to match" ;
					match->add_listener_list(conn->getConnectionId(),conn);
					//发送比赛信息
					SignGateMatchInfo(match,conn);
					conn->sendData((const char*)&ack_msg,ack_msg.msg_size);
				}

				if(match->get_time_scale() >= 1){
					match->get_team_depoist_state(msg->cid,ack_msg.depoist_change_player,ack_msg.depoist_use_skill);
				}else if(match->get_time_scale() == 0){
					match->_time_scale++;
					RunMatchJob* match_run = new RunMatchJob(match,_connection_to_db);
					int process_thread_id = mid%_process_list.size();
					_process_list[process_thread_id]->add_job_to_queue(match_run);
				}
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_MATCH_MOVE:// use the thread to do this job
		{
			MsgGameRunMatch *msg = (MsgGameRunMatch*)event->_msg_base;
			int mid = msg->mid;
			VLOG(1)<<"Starting run match..."<<mid;
			Match* match = CMatchManager::GetInstance()->GetMatch(mid);
			if(match == NULL){
				delete[] (char*)msg;
				LOG(ERROR)<<"No match "<<mid<<" was found.....";
				return;
			}
			RunMatchJob* match_run = new RunMatchJob(match,_connection_to_db);
			int process_thread_id = mid%_process_list.size();
			_process_list[process_thread_id]->add_job_to_queue(match_run);
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_MATCH_CHECK:
		{
			MsgGameMatchStatusCheck *msg = (MsgGameMatchStatusCheck*)event->_msg_base;
			CheckMatchStatus(msg->mid);
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_CLIENT_USE_TEAM_SKILL:
		{
			MsgClientUseSkill* msg = (MsgClientUseSkill*)event->_msg_base;
			int mid = msg->mid;
			int cid = msg->cid;
			Match* match = CMatchManager::GetInstance()->GetMatch(mid);
			int success_rate;
			int final_rate;
			if(match != NULL){
				bool rst = match->player_team_use_skill(cid,msg->team_skill_id,final_rate,success_rate);
				if(rst == true){
					MsgClientUseSkillBrocast ack_msg;
					ack_msg.cid = cid;
					ack_msg.mid = mid;
					ack_msg.team_skill_id = msg->team_skill_id;
					ack_msg.time_stamp = time(NULL);
					ack_msg.skill_success_rate = final_rate/100;
					ack_msg.skill_temp_rate = success_rate/100;
					match->borcast_all_gate((const char*)&ack_msg,ack_msg.msg_size);
					LOG(INFO)<<"send skill info ";
				}else{
					MsgClientUseSkillBrocast ack_msg;
					ack_msg.cid = cid;
					ack_msg.mid = mid;
					ack_msg.team_skill_id = 0;
					ack_msg.time_stamp = time(NULL);
					ack_msg.skill_success_rate = 0;
					ack_msg.skill_temp_rate = 0;
					match->borcast_all_gate((const char*)&ack_msg,ack_msg.msg_size);
				}
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_CLIENT_REQUEST_TEAM_SKILL_INFO:{
			MsgClientRequestSkillInfo* msg = (MsgClientRequestSkillInfo*)event->_msg_base;
			int mid = msg->mid;
			int cid = msg->cid;
			Match* match = CMatchManager::GetInstance()->GetMatch(mid);
			if(match != NULL){
				int skill_id = match->get_move()->get_team_by_cid(cid)->get_skill_used();
				MsgClientRequestSkillInfoAck msg;
				msg.cid = cid;
				msg.mid = mid;
				msg.state = skill_id;
				msg.time_stamp = time(NULL);
				match->borcast_all_gate((const char*)&msg,msg.msg_size);
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_CLIENT_DEPOIST_OPERATE:
		{
			MsgClientDepoistOperate* msg = (MsgClientDepoistOperate*)event->_msg_base;
			int mid = msg->mid;
			int cid = msg->cid;
			Match* match = CMatchManager::GetInstance()->GetMatch(mid);
			LOG(INFO)<<"MsgClientDepoistOperate................PREOCESS"<<mid<<":"<<cid<<":"<<msg->depoist_change_player<<":"<<msg->depoist_use_skill;
			if(match != NULL){
				SoccerTeam* team = match->get_move()->get_team_by_cid(cid);
				if(team != NULL){
					team->set_team_despoit_state(msg->depoist_change_player,msg->depoist_use_skill);
				}
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		case MSG_TYPE_CLIENT_QUERY_FAST_MATCH:{
			MsgClientQueryFastMatch *msg = (MsgClientQueryFastMatch*)event->_msg_base;
			int mid = msg->mid;
			int cid = msg->operate_cid;
			if(0 != VerifyOperate(mid,cid,MSG_TYPE_CLIENT_QUERY_FAST_MATCH,msg->time,public_key,msg->code)){
				LOG(ERROR)<<"Error request fast end match!"<<cid;
				delete[] (char*)msg;
				event->_msg_base = NULL;
				break;
			}

			bool rst =false;
			Match *match = CMatchManager::GetInstance()->GetMatch(mid);
			if(match != NULL){
				match->set_fast_match(true);
				rst = true;
				SoccerTeam* team = match->get_move()->get_team_by_cid(cid);
				team->set_team_despoit_state(true,true);
			}else{
				LOG(ERROR)<<"Fast match id"<<mid<<" not found!";
			}
			MsgClientQueryFastMatchAck ack_msg;
			ack_msg.mid = mid;
			ack_msg.cid = cid;
			ack_msg.rst = rst;
			match->borcast_all_gate((const char*)&ack_msg,ack_msg.msg_size);
			delete[] (char*)msg;
			event->_msg_base = NULL;
		}
		break;
		default:
			LOG(ERROR)<<"unknown message"<<msg_type;
		}

		if(event != NULL){
			delete event;
		}
	} else {
	//	VLOG(1)<<"null msg .....";
		timespec ts;
		ts.tv_nsec = 20000000;
		ts.tv_sec = 0;
		nanosleep(&ts,NULL);
	}
}

MsgBase* CGameMsgDispatcher::CompressMsg(MsgBase* msgbase){
	unsigned char* buffer = new unsigned char[8*1024];//(unsigned char*)malloc(8*1024);
	unsigned long len_after_compress = 8*1024;
	memcpy(buffer,(const char*)msgbase,sizeof(MsgBase));
	int rst = compress(buffer+sizeof(MsgBase),&len_after_compress,(((unsigned char*)msgbase)+sizeof(MsgBase)),msgbase->msg_size - sizeof(MsgBase));
	if(rst < 0){
		LOG(ERROR)<<"Error compress data!!!";
		delete[] buffer;
		return NULL;
	}
	((MsgBase*)buffer)->msg_size = len_after_compress+sizeof(MsgBase);
	return (MsgBase*)buffer;
}

int	CGameMsgDispatcher::VerifyChangePlayerOperate(int mid,int cid,int pid,int operate_type,int zeit_time,const char* key,const char* code){
	//md5($zeit.md5($public_key.$operate_type))
	std::ostringstream str;
	str<<public_key;
	str<<operate_type;
	str<<mid;
	str<<cid;
	str<<pid;
	std::string source_str(str.str());
	std::string md5_str = md5(source_str);
	std::ostringstream str1;
	str1<<zeit_time;
	str1<<md5_str.c_str();
	std::string md5_middle(str1.str());
	std::string md5final = md5(md5_middle);
	int rst = strncmp(md5final.c_str(),code,16);
	return rst;
}

int	CGameMsgDispatcher::VerifyOperate(int mid,int cid,int operate_type,int zeit_time,const char* key,const char* code){
	//md5($zeit.md5($public_key.$operate_type))
	std::ostringstream str;
	str<<public_key;
	str<<operate_type;
	str<<mid;
	str<<cid;
	std::string source_str(str.str());
	std::string md5_str = md5(source_str);
	std::ostringstream str1;
	str1<<zeit_time;
	str1<<md5_str.c_str();
	std::string md5_middle(str1.str());
	std::string md5final = md5(md5_middle);
	int rst = strncmp(md5final.c_str(),code,16);
	return rst;
}

void CGameMsgDispatcher::AddMatchStatusCheckTimeEvent(int mid,int type ){
	//should start ....move match after 9 sec
	time_t now;
	time(&now);

	int next_time_scale = 0;
	if(type == 3){
		next_time_scale = 30;
	}else{
		next_time_scale = 8*60;
	}
	TimerObject object;
	object.timeout = time(NULL) + next_time_scale;
	object.type = MATCH_STATUS_CHECK;
	object.param = mid;
	CGameTimerEventHandler::GetInstance()->AddTimer(object);
}

void CGameMsgDispatcher::CheckMatchStatus(int mid) {
	return;
	Match* match = CMatchManager::GetInstance()->GetMatch(mid);
	if(match == NULL) {
		VLOG(1)<<"No match "<<mid<<" was found.....";
		return;
	} else {
		if(match->get_time_scale() == 1){
			//资格赛自动开始
			if(match->_fixture_info->type == 3){
				MsgGameRunMatch* msg = new MsgGameRunMatch();
				msg->mid = mid;
				CMsgEvent* event = new CMsgEvent();
				event->_msg_type = msg->msg_type;
				event->_msg_base = msg;
				this->add_msg_to_queue(event,NULL);
			}else{
				//没有开始移除
				CMatchManager::GetInstance()->RemoveMatch(mid);
			}
		}
	}
}

void CGameMsgDispatcher::BrocastAllGateServer(MsgBase* pMsgBase){
	GateConManager::GetInstance()->BrocastAllConnection(pMsgBase);
}

void CGameMsgDispatcher::SignGateMatchInfo(Match* match,IConnection* conn){
	//普通的比赛话，通知网关服务器，生成比赛。如果是跨服挑战赛的话，就不发。等待gate的确认。
	MsgGameServerMatchStart new_match_msg;
	new_match_msg.mid = match->get_match_id();
	new_match_msg.uid = match->_uid1;
	new_match_msg.op_uid = match->_uid2;
	new_match_msg.server_index = server_index;
	new_match_msg.match_type = match->_match_typ;
	if(conn->connected()){
		conn->sendData((const char*)&new_match_msg,sizeof(new_match_msg));
	}
	//初始化后要加上比赛的开始检查
}

