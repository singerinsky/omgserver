/*
 * CMsgDispatcher.cpp
 *
 *  Created on: 2012-2-2
 *      Author: guanlei
 */

#include "CMsgDispatcher.h"
#include "CAllServerManage.h"
#include "CArenaManage.h"
#include "CGateTimerEventHandler.h"
CMsgDispatcher* CMsgDispatcher::_m_instance;
extern std::map<std::string,std::string> g_test_player_map;
extern const char* gm_login_public_key;

CMsgDispatcher::~CMsgDispatcher() {
	// TODO Auto-generated destructor stub
}

void* CMsgDispatcher::on_run(void) {
    on_timeout(&_timer_mgr);
	while (1) {
        int64_t now_ms = get_run_ms();
        _timer_mgr.run_until(now_ms);
		dispatch_msg();
	}
	return NULL;
}

void CMsgDispatcher::on_timeout(timer_manager* timer_mgr)
{
   _dispatcher_timer.set_expired(get_run_ms()+1000); 

   if(timer_mgr->add_timer(&_dispatcher_timer) != 0 )
   {
    VLOG(1)<<"error add timer";
   }
}


bool CMsgDispatcher::check_msg_valide(CMsgEvent* msg_event,EPollSocket* scoket) {
	if(scoket == NULL){
		return true;
	}
	//GM COMMAND
	if(msg_event->_msg_type != MSG_TYPE_LOGIN && msg_event->_msg_type != MSG_TYPE_GM_LOGIN && (scoket->_conn_state == CONN_UNVRIFY)){
		LOG(ERROR)<<"error of hacke"<<msg_event->_msg_type<<":"<<scoket->_conn_state<<":"<<scoket->get_client_ip_str();
        LOG(ERROR)<<gm_login_public_key;
		return false;
	}

	if(msg_event->_msg_type == MSG_TYPE_LOGIN && scoket->_conn_state == CONN_VRIFY){
		LOG(ERROR)<<"RELOGIN....."<<scoket->fd;
		return false;
	}

	return true;
}

bool CMsgDispatcher::add_msg_to_queue(CMsgEvent* msg_event, EPollSocket *socket) {
	if (check_msg_valide(msg_event,socket)) {
		if (msg_event->_msg_type == MSG_TYPE_LOGIN) {
			return do_login(msg_event, socket);
		}else if(msg_event->_msg_type == MSG_TYPE_GM_LOGIN){
			do_gm_login(msg_event,socket);
			return true;
		}
		else {
			this->_msg_queue.enqueue(msg_event);
            return true;
		}
	} else {
		LOG(ERROR)<<"error msg.......";
        return false;
	}

}

void CMsgDispatcher::dispatch_msg() {
	CMsgEvent* event = _msg_queue.dequeue();
	if (event != NULL) {
		int msg_type = event->_msg_type;
		switch (msg_type) {
		case MSG_TYPE_ALIVE: {//
			MsgAlive *msg = (MsgAlive*) event->_msg_base;
			int player_id = msg->player_id;
			GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(player_id);
			if(player != NULL){
				msg->zeit = time(NULL);
				player->send_msg(msg);
		
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_LOGIN_OUT:{
			MsgLoginOut *out = (MsgLoginOut*)event->_msg_base;
			GateWayPlayer *player = GateWayPlayerManager::GetInstance()->GetGateWayPlayerBySockFd(event->_client_id);
			if((player!= NULL) && (player->get_player_state() == WAIT_FOR_ARENAER_MACHING)){
				VLOG(1)<<"DO LOGOUT..."<<player->get_player_id();
				CArenaManage::get_instance()->leave_arena(player->get_player_id(),player->get_arenaer_stage_id());
			}
			if(player != NULL){
				int mid = player->get_match_watch();
				std::map<int, MatchInfo*>::iterator itr =_match_watcher.find(mid);
				if(itr != _match_watcher.end()){
					itr->second->remove_watcher_player(player->get_player_id());
				}

				GateWayPlayerManager::GetInstance()->RemoveGatePlayerMap(player->get_player_id());
			}

			delete[] (char*)out;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MATCH_PVP_CHAT_MSG:
		{
			MsgChatPVP * chat_msg = (MsgChatPVP*)event->_msg_base;
			int recv_id = chat_msg->recv_id;
			GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(recv_id);
			LOG(INFO)<<"player "<<chat_msg->send_id<<" say"<<chat_msg->msg_content;
			if(player){
				player->send_msg(chat_msg);
			}
			delete[] (char*)chat_msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_CHANGE_FORMATION://玩家换阵形
		{
			MsgClientChangeFormation* msg = (MsgClientChangeFormation*)event->_msg_base;
			int mid = msg->mid;
			GServerInfo* server_info = GetMatchRunServer(mid);
			if(server_info != NULL){
				server_info->_c_socket->sendData((const char*)msg,msg->msg_size);
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case	MSG_TYPE_CLIENT_CHANGE_MOVE://玩家换进攻卡
		{
			MsgClientChangeMove *msg = (MsgClientChangeMove*)event->_msg_base;
			int mid = msg->mid;
			GServerInfo* server_info = GetMatchRunServer(mid);
			if(server_info != NULL){
				server_info->_c_socket->sendData((const char*)msg,msg->msg_size);
			}
			delete event;
		}
		break;
		case	MSG_TYPE_CLIENT_CHANGE_PLAYER://玩家换人
		{
			MsgClientChangePlayer* msg = (MsgClientChangePlayer*)event->_msg_base;
			int mid = msg->mid;
			GServerInfo* server_info = GetMatchRunServer(mid);
			if(server_info != NULL){
				server_info->_c_socket->sendData((const char*)msg,msg->msg_size);
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case	MSG_TYPE_CLIENT_COACH_SPEAK://喊话
		{
			MsgClientCoachSpeak *msg = (MsgClientCoachSpeak*)event->_msg_base;
			GServerInfo* server_info = GetMatchRunServer(msg->mid);
			if(server_info != NULL){
				server_info->_c_socket->sendData((const char*)msg,msg->msg_size);
				LOG(INFO)<<"玩家喊话"<<msg->cid<<":"<<msg->speak_type;
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_USE_TEAM_SKILL://使用技能
		{
			MsgClientUseSkill* msg = (MsgClientUseSkill*)event->_msg_base;
			forward_to_game_server(event->_msg_base,msg->mid);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_USE_TEAM_SKILL_BROCAST://广播使用的技能
		{
			MsgClientUseSkillBrocast* msg = (MsgClientUseSkillBrocast*)event->_msg_base;

			VLOG(1)<<"USE ............"<<msg->mid;
			brocast_msg_to_match_watcher(msg->mid,msg);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_TERMINAL_MATCH://快速结束比赛
		{
			MsgClientTerminalMatch* msg = (MsgClientTerminalMatch*)(event->_msg_base);
			int mid = msg->mid;
			GServerInfo * server_info = GetMatchRunServer(mid);
			if(server_info != NULL){
				server_info->_c_socket->sendData((const char*)msg,msg->msg_size);
			}
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_PVN_MATCH_START://开始比赛,如果是跨服挑战赛，就转发到game_server
		{
			MsgClientPVNStartMatch* msg = (MsgClientPVNStartMatch*)(event->_msg_base);
			BrocastAllServer((const char*)msg,msg->msg_size);
/*			int mid = msg->mid;
			if(mid > 0){//正常比赛,
				MATCH_WATCH_ITR itr = _match_watcher.find(mid);
				if(itr != _match_watcher.end()){
					bool rst = (itr->second)->is_player_in(msg->cid);
					if(rst == false){
						(itr->second)->_watch_list.push_back(msg->cid);
					}
					GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(msg->cid);
					if(player != NULL){
						player->add_match_watch(mid);
					}
				}

				GServerInfo * game_server = GetMatchRunServer(mid);
				if(game_server != NULL) {
					game_server->SendData((const char*)msg,msg->msg_size);
				}
			}else{//转发到特定的game-server

			}*/
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_WATCH_MATCH:{
			MsgClientPVNStartMatch* msg = (MsgClientPVNStartMatch*)(event->_msg_base);
			int mid = msg->mid;
			MATCH_WATCH_ITR itr = _match_watcher.find(mid);
			if(itr != _match_watcher.end()){
				bool rst = (itr->second)->is_player_in(msg->cid);
				if(rst == false){
					(itr->second)->_watch_list.push_back(msg->cid);
				}
				GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(msg->cid);
				if(player != NULL){
					player->add_match_watch(mid);
					MsgClientWatchMatchAck ack;
					ack.mid = mid;
					ack.rst = true;
					player->send_msg((const MsgBase*)&ack);
				}
			}else{
				GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(msg->cid);
				if(player != NULL){
					MsgClientWatchMatchAck ack;
					ack.mid = mid;
					ack.rst = false;
					player->send_msg((const MsgBase*)&ack);
				}
			}

			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_SERVER_REQ://game server send the register message
		{
			VLOG(1)<<"GAME SERVER REGISTER";
/*			MsgServerReq* msg = (MsgServerReq*)event->_msg_base;
			int server_type = msg->_server_typ;
			int server_index = msg->_index;*/
		}
		break;
		case MSG_TYPE_GTOG_SERVER_NEW_MATCH://New match init
		{
			MsgGameServerMatchStart* msg = (MsgGameServerMatchStart*)event->_msg_base;
			int mid = msg->mid;
			if(_match_watcher.find(mid) == _match_watcher.end()){
				MatchInfo* match_info = new MatchInfo();
				match_info->server_index = msg->server_index;
				match_info->match_type = (msg->match_type);
				_match_watcher[msg->mid] = match_info;
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_MATCHING_SUCCESS_START:
		{
			MsgArenaerMatchingSuccess* msg_ack = (MsgArenaerMatchingSuccess*)event->_msg_base;
			int mid = msg_ack->mid;
			int uid = msg_ack->uid;
			int op_uid = msg_ack->op_uid;
			send_arena_matching_success(mid,uid,op_uid);
		}
		break;
		case MSG_TYPE_GTOG_SERVER_ROUND_PLAYER_DATA://match player data
		{
			MsgMatchPlayerRoundData* m = (MsgMatchPlayerRoundData*)(event->_msg_base);
			SendMatchPlayerData(m);
			delete[] (char*)(event->_msg_base);
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_GTOG_SERVER_ROUND_BALL_DATA://ball data msg
		{
			MsgMatchBallRoundData* msg = (MsgMatchBallRoundData*)(event->_msg_base);
			SendMatchBallData(msg);
			delete[] (char*)(event->_msg_base);
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_GTOG_SERVER_RESULT_DATA://match data
		{
			MsgMatchResultData* msg = (MsgMatchResultData*)(event->_msg_base);
			SendMatchResultData(msg);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_GTOG_SERVER_EVENT_DATA://match event
		{
			MsgMatchEventRoundData* msg = (MsgMatchEventRoundData*)(event->_msg_base);
			SendMatchEventData(msg);
			delete[] (char*)(event->_msg_base);
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_GTOG_SERVER_MATCH_END://match end
		{
			MsgGameToGateServerMatchEnd* msg = (MsgGameToGateServerMatchEnd*)(event->_msg_base);
			RemoveMatch(msg->mid);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_GTOG_SERVER_SKILL_DATA://player skill data
		{
			MsgGamePlayerSkillData* msg = (MsgGamePlayerSkillData*)(event->_msg_base);
			SendMatchSkillData(msg);
			delete[] (char*)(event->_msg_base);
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_GTOG_SERVER_TEAM_SKILL_DATA://team skill data
		{
			MsgGameTeamSkillData	*msg = (MsgGameTeamSkillData*)(event->_msg_base);
			SendMatchTeamSkillData(msg);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_GTOG_TEAM_NEW_FORMATION://team change player
		{
			MsgTeamNewPlayerFormationPos *msg = (MsgTeamNewPlayerFormationPos*)(event->_msg_base);
			SendMatchTeamNewFormation(msg);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_GTOG_SERVER_PENTLY_RESULT://点球
		{
			MsgMatchPentlyResultData* msg = (MsgMatchPentlyResultData*)(event->_msg_base);
			send_match_pently_to_all_watch(msg);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		//GM 命令
		case MSG_TYPE_GM_SERVER_INFO:
		case MSG_TYPE_GM_QUERY_MATCH_INFO:
		case MSG_TYPE_GM_MODIFER_MATCH:
		case MSG_TYPE_GM_QUERY_GATE_SERVER_PLAYER_ONLINE:
			gm_command(event);
			break;
		case MSG_TYPE_CLIENT_DO_ARENA_MATCHING:
		{
			MsgServerArenaDoMatch* msg = (MsgServerArenaDoMatch*)(event->_msg_base);
			for(int i=1;i<5;i++){
				CArenaManage::get_instance()->do_matching(i);
			}
			VLOG(1)<<"do matching....";
			//再次加事件
			_timer_handler->add_arena_event();

			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_MATCHING_SUCCESS:
		{
			MsgServerMatchingSuccess* msg = (MsgServerMatchingSuccess*)(event->_msg_base);
			GServerInfo* server_info = PickMatchServer();
			if(server_info != NULL){
				server_info->_c_socket->sendData((const char*)msg,msg->msg_size);
			}

			GateWayPlayer* home_player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(msg->home_uid);
			if(home_player != NULL){
				home_player->send_msg((const MsgBase*)msg);
			}

			if(msg->away_uid != -1){
				GateWayPlayer* away_player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(msg->away_uid);
				if(away_player != NULL){
					away_player->send_msg((const MsgBase*)msg);
				}
			}

			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_ENTER_ARENA:
		{
			MsgArenaerEnter* msg = (MsgArenaerEnter*)(event->_msg_base);
			GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(msg->player_id);
			if(player != NULL){
				player->enter_arenar(msg->stage_id);
				player->set_attack_value(msg->attack_value);
				player->set_defend_value(msg->defend_value);
				CArenaManage::get_instance()->enter_arena(player);
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYEP_SPEAK_BROCAST:
		{
			MsgClientSpeakBrocast	*msg = (MsgClientSpeakBrocast*)(event->_msg_base);
			borcast_player_speak(msg->mid,msg);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_REQUEST_TEAM_SKILL_INFO:{
			MsgClientRequestSkillInfo* msg = (MsgClientRequestSkillInfo*)(event->_msg_base);
			forward_to_game_server(event->_msg_base,msg->mid);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_REQUEST_TEAM_SKILL_INFO_ACK:{
			MsgClientRequestSkillInfoAck* msg = (MsgClientRequestSkillInfoAck*)(event->_msg_base);
			SendTeamSkillInfoToPlayer(msg);
			VLOG(0)<<"REQUEST ACK "<<msg->cid<<":"<<msg->state;
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_REQUEST_MATCH_START_ACK:{
			MsgClientStartMatchAck* ack_msg = (MsgClientStartMatchAck*)(event->_msg_base);
			SendStartMatchAckTOPlayer(ack_msg);
			if(ack_msg->rst  == 1){//确认比赛的存在
				LOG(INFO)<<"match is running on game server ";
				//把玩家加入关注的列表
				MATCH_WATCH_ITR itr = _match_watcher.find(ack_msg->mid);
				if(itr != _match_watcher.end()){
					bool rst = (itr->second)->is_player_in(ack_msg->cid);
					if(rst == false){
						(itr->second)->_watch_list.push_back(ack_msg->cid);
					}
					GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(ack_msg->cid);
					if(player != NULL){
						player->add_match_watch(ack_msg->mid);
					}
				}
			}
/*			GServerInfo *server_info =  CALLServerManage::GetInstance()->GetServerByIndexId(ack_msg->server_index);
			if(server_info != NULL){

			}*/

			delete[] (char*)ack_msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_DEPOIST_OPERATE:{
			MsgClientDepoistOperate *msg = (MsgClientDepoistOperate*)(event->_msg_base);
			forward_to_game_server(event->_msg_base,msg->mid);
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_QUERY_FAST_MATCH:{
			MsgClientQueryFastMatch* msg = (MsgClientQueryFastMatch*)(event->_msg_base);
			forward_to_game_server(event->_msg_base,msg->mid);
			LOG(INFO)<<"Player request fast end mach"<<msg->mid;
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		case MSG_TYPE_CLIENT_QUERY_FAST_MATCH_ACK:{
			MsgClientQueryFastMatchAck* msg = (MsgClientQueryFastMatchAck*)(event->_msg_base);
			int player_id = msg->cid;
			GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(player_id);
			if(player != NULL){
				player->send_msg((const MsgBase*)msg);
			}
			delete[] (char*)msg;
			event->_msg_base = NULL;
			delete event;
		}
		break;
		default:
			LOG(ERROR)<<"unknown message"<<msg_type;
		}
	}else{
		timespec ts;
		ts.tv_nsec = 20000000;
		ts.tv_sec = 0;
		nanosleep(&ts,NULL);
	}
}

bool CMsgDispatcher::do_login(CMsgEvent* msg_event, EPollSocket* socket) {
	MsgLogin* login = (MsgLogin*) msg_event->_msg_base;
	int uid = login->uid;
	int mid = login->mid;
	int zeit = login->zeit;
	int rand_int = login->rand_int;
	std::ostringstream strbuff;
	strbuff<<zeit;
	std::ostringstream str_tmp;
	str_tmp<<public_key;
	str_tmp<<rand_int;
	str_tmp<<mid;
	str_tmp<<uid;
	std::string source_str(str_tmp.str());
	std::string md5_str = md5(source_str);
	strbuff<<md5_str.c_str();
	std::string tmp_string(strbuff.str());
	std::string final_str = md5(tmp_string);
	int rst = strncmp(final_str.c_str(),login->code,16);
	if(rst != 0){
		LOG(ERROR)<<"uknown login.......uid:"<<uid<<" mid:"<<mid<<" zeit:"<<zeit<<" rand_int:"<<rand_int<<" rst:"<<login->code<<":"<<final_str.c_str();
		dis_connection(socket,-2);
		return false;
	}

#ifdef _MY_DEBUG_
	std::string ip = socket->get_client_ip_str();

	std::map<std::string,std::string>::iterator itr= g_test_player_map.find(ip);
	if(itr != g_test_player_map.end()){
		VLOG(2)<<(itr->second).c_str()<<" 用账户"<<uid<<" 登陆了。";
	}else{
		dis_connection(socket,-2);
		return false;
	}
#endif

	GateWayPlayer* player  = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(uid);
	if(player == NULL){
		player = new GateWayPlayer(socket,uid,_timer_mgr);
/*		if(mid < 0 ){*/
			//加入竞技场的链接
		GateWayPlayerManager::GetInstance()->AddPlayerMap(uid,player);
/*		}else{
			GateWayPlayerManager::GetInstance()->AddPlayerMap(uid, player);
			MATCH_WATCH_ITR itr = _match_watcher.find(mid);
			if(itr != _match_watcher.end()){
				bool rst = (itr->second)->is_player_in(uid);
				if(rst == false){
					(itr->second)->_watch_list.push_back(uid);
				}
			}
		}*/
	}else{
		do_logout(player);
		player->reset(socket,uid);
	}

	LOG(INFO)<<"Player "<<uid<<" login success!";
	MsgLoginAck msg;
	msg.ret = 1;
	player->send_msg(&msg);
	return 1;
}

bool CMsgDispatcher::do_gm_login(CMsgEvent* msg_event,EPollSocket* socket){
	GMMsgGmLogin *msg = (GMMsgGmLogin*)msg_event->_msg_base;
	std::ostringstream str_tmp;
	str_tmp<<msg->gm_uid;
	str_tmp<<msg->time;
	str_tmp<<gm_login_public_key;
	std::string str_final(str_tmp.str());
	std::string md5_str = md5(str_final);
	int rst = strncmp(md5_str.c_str(),msg->code,20);
	if(rst != 0){
/*		VLOG(1)<<"gm login success!";
		socket->_session->login_success();
		socket->_session->set_gm(true);
		bool result = GateWayPlayerManager::GetInstance()->AddPlayerMap(msg->gm_uid,socket->_session);
		if(result == true){
			MsgLoginAck msg;
			msg.ret = 1;
			socket->_session->send_msg(&msg);
		}else{
			return false;
		}*/
	}else{
		return false;
	}
	return true;
}


bool CMsgDispatcher::do_logout(GateWayPlayer* player,int rst) {
/*	if(player->get_player_state() == WAIT_FOR_ARENAER_MACHING){
		CArenaManage::get_instance()->leave_arena(player->get_player_id(),player->get_arenaer_stage_id());
	}*/

	MsgLoginAck msg;
	msg.ret = rst;//重复登陆
	player->send_msg(&msg);
/*	int match_watch_id = player->get_match_watch();
	if(match_watch_id != 0){
		std::map<int,MatchInfo* >::iterator itr = _match_watcher.find(match_watch_id);
		if(itr != _match_watcher.end()){
			(itr->second)->remove_watcher_player(player->get_player_id());
		}
	}
	GateWayPlayerManager::GetInstance()->RemoveGatePlayerMap(player->get_player_id());*/
	EPollSocket* socket = player->get_epoll_socket();
	delete socket;
	return true;
}

bool CMsgDispatcher::dis_connection(EPollSocket*socket,int rst) {
	MsgLoginAck msg;
	msg.ret = rst;//重复登陆
	socket->send_msg(&msg);
	delete socket;
	return true;
}

void CMsgDispatcher::SendMatchPlayerData(MsgMatchPlayerRoundData* m){
	int mid = m->mid;
	MsgBase* msg_base = CompressMsg(m);
	if(msg_base == NULL){
		delete m;
		return;
	}
	std::map<int,MatchInfo* >::iterator itr = _match_watcher.find(mid);
	if(itr != _match_watcher.end()){
		send_match_info_to_all_watch(itr->second,msg_base);
	}
    delete[] (char*)msg_base;
}

void CMsgDispatcher::SendMatchBallData(MsgMatchBallRoundData* m){
	MsgBase* msg_base = CompressMsg(m);
	if(msg_base == NULL){
		delete m;
		return;
	}
	std::map<int,MatchInfo* >::iterator itr = _match_watcher.find(m->mid);
	if(itr != _match_watcher.end()){
		send_match_info_to_all_watch((itr->second),msg_base);
	}
    delete[] (char*)msg_base;
}

void CMsgDispatcher::SendTeamSkillInfoToPlayer(MsgClientRequestSkillInfoAck*msg){
	GateWayPlayer * player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(msg->cid);
	if(player != NULL){
		player->send_msg((const MsgBase*)msg);
	}

}

void CMsgDispatcher::SendStartMatchAckTOPlayer(MsgClientStartMatchAck* msg){
	GateWayPlayer * player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(msg->cid);
	if(player != NULL){
		player->send_msg((const MsgBase*)msg);
	}
}


void CMsgDispatcher::SendMatchResultData(MsgMatchResultData* m){
	std::map<int,MatchInfo* >::iterator itr = _match_watcher.find(m->mid);
	if(itr != _match_watcher.end()){
		send_match_info_to_all_watch(itr->second,(MsgBase*)m);
	}
}

void CMsgDispatcher::SendMatchEventData(MsgMatchEventRoundData* m){
	MsgBase* msg_base = CompressMsg(m);
	if(msg_base == NULL){
		delete m;
		return;
	}
	std::map<int,MatchInfo* >::iterator itr = _match_watcher.find(m->mid);
	if(itr != _match_watcher.end()){
		send_match_info_to_all_watch(itr->second,msg_base);
	}
    delete[] (char*)msg_base;
}

void CMsgDispatcher::SendMatchSkillData(MsgGamePlayerSkillData* m){
	MsgBase* msg_base = CompressMsg(m);
	if(msg_base == NULL){
		delete m;
		return;
	}
	std::map<int,MatchInfo* >::iterator itr = _match_watcher.find(m->mid);
	if(itr != _match_watcher.end()){
		send_match_info_to_all_watch(itr->second,msg_base);
	}
    delete[] (char*)msg_base;
}


void CMsgDispatcher::SendMatchTeamSkillData(MsgGameTeamSkillData* m){
	std::map<int,MatchInfo* >::iterator itr = _match_watcher.find(m->mid);
	if(itr != _match_watcher.end()){
		send_match_info_to_all_watch(itr->second,(MsgBase*)m);
	}
}

void CMsgDispatcher::SendMatchTeamNewFormation(MsgTeamNewPlayerFormationPos* m){
	std::map<int,MatchInfo* >::iterator itr = _match_watcher.find(m->mid);
	if(itr != _match_watcher.end()){
		send_match_info_to_all_watch(itr->second,(MsgBase*)m);
	}
}


void CMsgDispatcher::send_match_pently_to_all_watch(MsgMatchPentlyResultData* m){
	std::map<int,MatchInfo*>::iterator itr = _match_watcher.find(m->mid);
	if(itr != _match_watcher.end()){
		send_match_info_to_all_watch(itr->second,(MsgBase*)m);
	}
}


void CMsgDispatcher::send_arena_matching_success(int mid,int uid,int op_uid){
	MsgArenaerMatchingSuccess msg;
	msg.mid = mid;
	GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(uid);
	if (player != NULL) {
		(player)->send_msg(&msg);
	}

	player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(op_uid);
	if (player != NULL) {
		(player)->send_msg(&msg);
	}

}

void CMsgDispatcher::brocast_msg_to_match_watcher(int mid,MsgBase* msg){
	std::map<int,MatchInfo*>::iterator itr = _match_watcher.find(mid);
		if(itr != _match_watcher.end()){
			send_match_info_to_all_watch(itr->second,msg);
		}
}

void CMsgDispatcher::borcast_player_speak(int mid,MsgClientSpeakBrocast* m){
	std::map<int,MatchInfo*>::iterator itr = _match_watcher.find(mid);
	if(itr != _match_watcher.end()){
		send_match_info_to_all_watch(itr->second,(MsgBase*)m);
	}
}

#define BUFFER_SIZE 8*1024

MsgBase* CMsgDispatcher::CompressMsg(MsgBase* msgbase){
    char* buffer = new char[BUFFER_SIZE];
	if(buffer == NULL){
		return NULL;
	}
	unsigned long len_after_compress = 32*1024;
	if(msgbase->msg_size > 32*1024){
		LOG(ERROR)<<"Msg size is too big"<<msgbase->msg_size;
	}
	memcpy(buffer,(const char*)msgbase,sizeof(MsgBase));
	unsigned char* encode_data = (unsigned char*)buffer+sizeof(MsgBase);
	unsigned char* src_data = ((unsigned char*)msgbase) + sizeof(MsgBase);
	int rst = compress(encode_data,&len_after_compress,src_data,msgbase->msg_size - sizeof(MsgBase));
	if(rst < 0){
        delete[] buffer;
		return NULL;
	}
	((MsgBase*)buffer)->msg_size = len_after_compress+sizeof(MsgBase);
	return (MsgBase*)buffer;
}

void CMsgDispatcher::RemoveMatch(int mid){
	//断线
	std::map<int,MatchInfo*>::iterator itr = _match_watcher.find(mid);
	if(itr != _match_watcher.end()){
		remove_all_watcher((itr->second), true);
		delete itr->second;
		_match_watcher.erase(itr);
	}
}

GServerInfo* CMsgDispatcher::GetMatchRunServer(int mid){
	/*if(mid < 0){
		return CALLServerManage::GetInstance()->GetServerByIndexId(CROSS_SERVER);
	}

*/	std::map<int,MatchInfo*>::iterator itr = _match_watcher.find(mid);
	int server_index = itr->second->server_index;
	return CALLServerManage::GetInstance()->GetServerByIndexId(server_index);
}

GServerInfo* CMsgDispatcher::PickMatchServer(){
	GServerInfo* server_info = CALLServerManage::GetInstance()->GetOneServer();
	if(server_info == NULL){
		return NULL;
	}
	return server_info;
}

GServerInfo* CMsgDispatcher::GetDefaultServer(){
	GServerInfo* server_info = CALLServerManage::GetInstance()->GetServerByIndexId(1);
	if(server_info == NULL){
		return NULL;
	}
	return server_info;
}

void CMsgDispatcher::gm_command(CMsgEvent* event){
	MsgBase* base = event->_msg_base;
	VLOG(0)<<"coming game master msg......"<<base->msg_type;
	if(base->msg_type == MSG_TYPE_GM_QUERY_GATE_SERVER_PLAYER_ONLINE){
		std::list<int> list = GateWayPlayerManager::GetInstance()->export_all_player_online();
		GMMsgQueryPlayerInfoAck info;
		info.player_count = list.size();
		std::list<int>::iterator itr = list.begin();
		int i=0;
		while(itr != list.end()){
			int player_id = *itr;
			itr++;
			info.player_id[i] = player_id;
			i++;
		}
		info.msg_size = 16 + 4*i;
		/*GateWayPlayer *player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(event->_client_id);
		session->send_msg((char*)&info,info.msg_size);*/
	}
}

void CMsgDispatcher::send_match_info_to_all_watch(MatchInfo* info, MsgBase* msg) {
	std::list<int>::iterator itr = info->_watch_list.begin();
	while (itr != info->_watch_list.end()) {
		GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(*itr);
		if (player != NULL) {
			(player)->send_msg(msg);
		}
		itr++;
	}
}

void CMsgDispatcher::remove_all_watcher(MatchInfo* info, bool need_logout) {
	std::list<int>::iterator itr = info->_watch_list.begin();
	while (itr != info->_watch_list.end()) {
		GateWayPlayer* player = GateWayPlayerManager::GetInstance()->GetGateWayPlayer(*itr);
		if(player != NULL){
			player->add_match_watch(0);
		}
		itr++;
	}
}

void CMsgDispatcher::forward_to_game_server(MsgBase* msg,int mid){
	GServerInfo* server_info = GetMatchRunServer(mid);
	if(server_info != NULL){
		server_info->_c_socket->sendData((const char*)msg,msg->msg_size);
	}
}

void CMsgDispatcher::BrocastAllServer(const char* msg,int msg_size){
	CALLServerManage::GetInstance()->BrocastAllServer(msg,msg_size);
}
