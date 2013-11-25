/*
 * RunMatchJob.cpp
 *
 *  Created on: Mar 12, 2012
 *      Author: guanlei
 */

#include "RunMatchJob.h"

RunMatchJob::RunMatchJob(Match* match,CConnectToDB* pDBConnection) {
	// TODO Auto-generated constructor stub
	this->_match = match;
	this->_connection_to_db = pDBConnection;
}

RunMatchJob::~RunMatchJob() {
	// TODO Auto-generated destructor stub
	this->_match = NULL;
	this->_connection_to_db = NULL;
}

void RunMatchJob::ExecuteJob() {
	SoccerMatch *match = _match->get_move();
	MatchEndStatus *end_status = match->get_match_last_end_status();
	//上100个时间片没有跑结束，要继续跑
	LOG(INFO)<<"run match  "<<_match->get_match_id();
	if(_match->get_match_id() == -1){
		return;
	}
	int run_time_scale = 0;
	int start_round_type = 0;
	if (end_status->_current_end_sub_typ == OVERTIME) {
		end_status->ReSet();
		start_round_type = -1;
		bool resv = false;
		if(_match->_round_info.att_uid != _match->_fixture_info->u1.uid){
			resv = true;
		}
		MatchRecorder recorder(match,_match->_first_half,resv);
		_match->match_continue_move(&recorder, run_time_scale);
		ExportAllMatchData(recorder,run_time_scale,start_round_type);
	} else {
		//判断半场时间
		if(end_status->_current_end_status == END_HALF_TIME){
			_match->_first_half = false;
		}
		_match->judge_attack_defend(end_status);
		bool resv = false;
		if(_match->_round_info.att_uid != _match->_fixture_info->u1.uid){
			resv = true;
		}
		MatchRecorder recorder(match,_match->_first_half,resv);
		start_round_type = _match->get_current_round_info().typ;
		_match->check_team_op_before_move();
		end_status->ReSet();
		if(_match->is_half_time_now()){
			_match->update_player_cond_half_time();
		}

		_match->match_new_move(&recorder,run_time_scale);
		ExportAllMatchData(recorder,run_time_scale,start_round_type);
	}
	//如果比赛结束了，//通知gate,game比赛结束
	if((_match->is_match_end())){
		SendMatchEndMsg();
		LOG(INFO)<<"比赛结束"<<_match->get_match_id();
		//_match->export_all_skill_player_used();
		//_match->ex
		CMatchManager::GetInstance()->RemoveMatch(_match->get_match_id());
	}else{//加入定时器
		AddNextMatchMoveEvent(run_time_scale,_match->get_match_id());
	}
}

void RunMatchJob::ExportAllMatchData(MatchRecorder& recorder, int pITimeScale,int round_type) {
	omg::StringBuilder *all_player_data = NULL;
	MsgMatchPlayerRoundData* msg_player = NULL;
	if(_match->is_fast_match()){
		all_player_data = new omg::StringBuilder(sizeof(MsgMatchPlayerRoundData));
		MsgMatchPlayerRoundData msg;
		all_player_data->append((const char*) &msg, sizeof(msg) - sizeof(void*));
		msg_player = (MsgMatchPlayerRoundData*)all_player_data->c_str();
		msg_player->msg_size = all_player_data->len();
		msg_player->player_count = 0;
	}else{
		all_player_data = recorder.export_str_player();
		msg_player = (MsgMatchPlayerRoundData*) all_player_data->c_str();
	}
	msg_player->is_fast_match = _match->is_fast_match();

	msg_player->mid = _match->get_match_id();
	msg_player->time_scale_start = _match->get_time_scale() - pITimeScale;
	msg_player->is_encode = 1;
	msg_player->round_type = round_type;
	msg_player->half_time = (short)recorder.is_half();
	if((_match->get_move()->get_match_last_end_status()->_current_end_sub_typ == OVERTIME) || (_match->get_move()->get_match_last_end_status()->_next_round_typ == N_STRIKE_BACK)){
		msg_player->is_new_round = 1;
	}else{
		msg_player->is_new_round = 0;
	}
	if(_match->is_match_end()){
		if(recorder.has_pently_data()){
			msg_player->is_match_end = 2;
		}else{
			msg_player->is_match_end = 1;
		}
	}else{
		msg_player->is_match_end = 0;
	}
	msg_player->round_end_status = _match->get_move()->get_match_last_end_status()->_current_end_status;
	msg_player->total_sacle_number = pITimeScale;
	_match->borcast_all_gate((const char*)msg_player,msg_player->msg_size);

	delete all_player_data;


	//获取球的数据
	omg::StringBuilder *all_ball_data = recorder.export_str_ball();
	MsgGameBallRoundData* ball_msg =
			(MsgGameBallRoundData*) all_ball_data->c_str();
	ball_msg->mid = _match->get_match_id();
	ball_msg->time_scale_start = _match->get_time_scale() - pITimeScale;
	ball_msg->msg_size = all_ball_data->len();
	if((_match->is_fast_match() == false)){
		_match->borcast_all_gate((const char*)ball_msg,ball_msg->msg_size);
	}
	delete all_ball_data;
	
	if(recorder.has_pently_data()){
		MsgMatchPentlyResultData *pently_data = recorder.export_pently_data();
		pently_data->mid = _match->get_match_id();
		_match->borcast_all_gate((const char*)pently_data,pently_data->msg_size);
		delete pently_data;
	}


	//获取比赛的球队的技能的使用
	MsgGameTeamSkillData team_skill_data;
	team_skill_data.mid = _match->get_match_id();
	team_skill_data.time_scale_start = _match->get_time_scale() - pITimeScale;
	team_skill_data.team_skill_1 = 	_match->get_move()->get_attack_team()->get_last_round_skill_used();
	team_skill_data.team_cid_1 = 	_match->get_move()->get_attack_team()->get_team_cid();
	team_skill_data.team_cid_2 = 	_match->get_move()->get_defend_team()->get_team_cid();
	team_skill_data.team1_att_energy = _match->get_move()->get_attack_team()->get_team_attack_mp();
	team_skill_data.team1_def_energy =	_match->get_move()->get_attack_team()->get_team_def_mp();
	team_skill_data.team2_att_energy = _match->get_move()->get_defend_team()->get_team_attack_mp();
	team_skill_data.team2_def_energy = _match->get_move()->get_defend_team()->get_team_def_mp();
	LOG(INFO)<<"team"<<team_skill_data.team_cid_1<<":"<<team_skill_data.team_skill_1;
	_match->borcast_all_gate((const char*)&team_skill_data,team_skill_data.msg_size);
/*	_match->get_move()->get_team(1)->reset_skill_used();
	_match->get_move()->get_team(2)->reset_skill_used();*/

	//获取事件的数据
	omg::StringBuilder* all_event_data = recorder.export_str_event();
	MsgGameEventRoundData *event_msg = (MsgGameEventRoundData*)all_event_data->c_str();
	event_msg->time_scale_start = _match->get_time_scale() - pITimeScale;
	event_msg->mid = _match->get_match_id();
	event_msg->time_scale = _match->get_move()->get_compare_log()->time_scale;
	event_msg->cmp_type = _match->get_move()->get_compare_log()->compare_type;
	event_msg->from_pid = _match->get_move()->get_compare_log()->from_pid;
	event_msg->to_pid = _match->get_move()->get_compare_log()->to_pid;
	event_msg->rst = _match->get_move()->get_compare_log()->result;

	event_msg->msg_size = all_event_data->len();
	_match->borcast_all_gate((const char*)event_msg,event_msg->msg_size);
	delete all_event_data;

	MsgGameEventDBWB* wbmsg = new MsgGameEventDBWB();
	wbmsg->mid = _match->get_match_id();
	wbmsg->event_count = 1;
	recorder.export_event_db(*wbmsg,_match->get_time_scale());
	if(wbmsg->event[0].type <1 || wbmsg->event[0].type >9){
		delete wbmsg;
	}else{
		_connection_to_db->SendMsg((MsgBase*)wbmsg);
	}

	//获取比赛的使用技能
	omg::StringBuilder* all_skill_data = recorder.export_str_skill();
	MsgGamePlayerSkillData *skill_msg = (MsgGamePlayerSkillData*)all_skill_data->c_str();
	skill_msg->time_scale_start = _match->get_time_scale() - pITimeScale;
	skill_msg->mid = _match->get_match_id();
	skill_msg->msg_size = all_skill_data->len();
	_match->borcast_all_gate((const char*)skill_msg,skill_msg->msg_size);
	delete all_skill_data;

	//发送比赛的结果数据
	MsgMatchResultData result;
	result.mid = _match->get_match_id();
	result.time_scale_start = _match->get_time_scale() - pITimeScale;
	result.team1.cid = _match->get_move()->get_team(1)->get_team_cid();
	result.team1.point = _match->get_team_soccer(result.team1.cid);
	result.team2.cid = _match->get_move()->get_team(2)->get_team_cid();
	result.team2.point = _match->get_team_soccer(result.team2.cid);
	_match->borcast_all_gate((const char*)&result,result.msg_size);

	SendNewTeamFormationPos(pITimeScale);
}

void RunMatchJob::SendNewTeamFormationPos(int pTimeScale) {
	MsgTeamNewPlayerFormationPos msg;
	SoccerTeam *home_team = _match->get_move()->get_home_team();
	SoccerTeam *away_team = _match->get_move()->get_away_team();
	msg.mid = _match->get_match_id();
	msg.time_scale_start = _match->get_time_scale() - pTimeScale;
	msg.home_cid = home_team->get_team_cid();
	msg.away_cid = away_team->get_team_cid();

	SoccerPlayer* player = NULL;
	for (int i = 1; i < 12; i++) {
		player = home_team->get_player_by_pos_index(i);
		if (player == NULL) {
			msg.home_new_formation_pos[i-1] = 0;
		} else {
			msg.home_new_formation_pos[i-1] = player->get_union_pid();
		}
	}

	for (int i = 1; i < 12; i++) {
		player = away_team->get_player_by_pos_index(i);
		if (player == NULL) {
			msg.away_new_formation_pos[i-1] = 0;
		} else {
			msg.away_new_formation_pos[i-1] = player->get_union_pid();
		}
	}
	_match->borcast_all_gate((const char*)&msg,msg.msg_size);
}


void RunMatchJob::AddNextMatchMoveEvent(int run_time_scale, int mid) {
    //should start ....move match after 9 sec[1m~[~^
    time_t now;
    time(&now);
    int next_time_scale = 0;
    if(run_time_scale >= 198){
            next_time_scale = static_cast<int>(round((run_time_scale)/15.5 - 0.5));
    }else{
            next_time_scale = static_cast<int>(round((((double)run_time_scale)/15.5)));
    }

    if(_match->_time_scale == _match->_total_time_scale/2){
    	  next_time_scale = static_cast<int>(round((run_time_scale)/15.5 + 2.5));
    }

    //是否快速比赛，立马生成新的比赛数据
    if(_match->is_fast_match()){
    	next_time_scale = -1;
    }

    TimerObject object;
    object.timeout = time(NULL) + next_time_scale;
    object.type = MATCH_MOVE;
    object.param = mid;
    CGameTimerEventHandler::GetInstance()->AddTimer(object);
}

void RunMatchJob::SendMatchEndMsg(){
	MsgGameToGateServerMatchEnd msg;
	msg.mid = this->_match->get_match_id();
	msg.is_encode = 0;
	_match->borcast_all_gate((const char*)&msg,msg.msg_size);
	//_match->export_team_round_split()
	std::string statis_str;
	//int msg_size = _match->export_match_statis_info(statis_str);
	int msg_buffer_size = sizeof(MsgGameToDbServerMatchEnd) + statis_str.size();
	char* msg_buffer = new char[msg_buffer_size];

	FixtureInfo* info = this->_match->get_fixture_info();
	//比赛的数据
	MsgGameToDbServerMatchEnd* db_msg = (MsgGameToDbServerMatchEnd*)msg_buffer;
	strncpy(db_msg->statis_data,statis_str.c_str(),statis_str.size());
	db_msg->statis_data[statis_str.size()] = '\0';
	LOG(INFO)<<db_msg->statis_data<<":"<<statis_str.size();
	db_msg->msg_type = MSG_TYPE_GTODB_SERVER_MATCH_END;
	db_msg->msg_size = msg_buffer_size;
	db_msg->is_encode = 0;
	db_msg->shot_h = 0;
	db_msg->shot_a = 0;
	db_msg->shot_on_h = 0;
	db_msg->shot_on_a = 0;
	db_msg->mid = this->_match->get_match_id();
	db_msg->away_cid = this->_match->_fixture_info->u2.uid;
	db_msg->away_score = this->_match->get_team_soccer(db_msg->away_cid);
	db_msg->home_cid = this->_match->_fixture_info->u1.uid;
	db_msg->home_score = this->_match->get_team_soccer(db_msg->home_cid);
	db_msg->home_possession = this->_match->get_team_possession(db_msg->home_cid);
	db_msg->away_possession = this->_match->get_team_possession(db_msg->away_cid);
	db_msg->shot_a = this->_match->get_team_shot_count(db_msg->away_cid );
	db_msg->shot_h = this->_match->get_team_shot_count(db_msg->home_cid);
	db_msg->shot_on_a = this->_match->get_team_shot_on_count(db_msg->away_cid );
	db_msg->shot_on_h = this->_match->get_team_shot_on_count(db_msg->home_cid);
	db_msg->pently_a =	this->_match->get_team_pently_on_count(db_msg->away_cid);
	db_msg->pently_h =  this->_match->get_team_pently_on_count(db_msg->home_cid);
	db_msg->typ = info->type;

	//all npc player no need
	if((info->u1.uid <0) && (info->u2.uid<0)){
		return;
	}

	//球员的属性写回
	MsgGameToDbServerPlayerUpdate* player_update_msg = new MsgGameToDbServerPlayerUpdate();
	player_update_msg->mid = this->_match->get_match_id();
	std::ostringstream strbuff;
	strbuff<< setiosflags(ios_base::fixed) <<setprecision(1);
	if(true||info->u1.uid > 0){
		std::map<int,PlayerInfo>::iterator itr = info->u1.players.begin();
		while(itr != info->u1.players.end()){
			PlayerInfo& player_info = itr->second;
			if(player_info.has_been_to_pitch == false){
				itr++;
				continue;
			}

			if(info->u1.uid <0 ){
							player_info.cond = 100;
			}
			strbuff<<"(";
			strbuff<<_match->get_match_id();
			strbuff<<","<<player_info.pid<<",\""<<player_info.player_name;
			strbuff<<"\","<<info->u1.uid<<",";
			strbuff<<player_info.p_shot_count<<",0,0,"<<player_info.p_score;
			strbuff<<","<<player_info.p_goal_count<<","<<player_info.p_assist_count<<","<<player_info.p_steals_count;
			strbuff<<","<<player_info.red_card<<","<<player_info.yellow_card<<","<<player_info.inj<<",0,0,"<<player_info.cond<<",0)";
			itr++;
			//if(itr != info->u1.players.end()){
				strbuff<<",";
			//}
		}
	}

	if(true||info->u2.uid > 0){
		std::map<int,PlayerInfo>::iterator itr = info->u2.players.begin();
		while(itr != info->u2.players.end()){
			PlayerInfo& player_info = itr->second;
			if(player_info.has_been_to_pitch == false){
				itr++;
				continue;
			}

			if(info->u2.uid <0 ){
				player_info.cond = 100;
			}

			strbuff<<"(";
			strbuff<<_match->get_match_id();
			strbuff<<","<<player_info.pid<<",\""<<player_info.player_name;
			strbuff<<"\","<<info->u2.uid<<",";
			strbuff<<player_info.p_shot_count<<",0,0,"<<player_info.p_score;
			strbuff<<","<<player_info.p_goal_count<<","<<player_info.p_assist_count<<","<<player_info.p_steals_count;
			strbuff<<","<<player_info.red_card<<","<<player_info.yellow_card<<","<<player_info.inj<<",0,0,"<<player_info.cond<<",0)";
			itr++;
			//if(itr != info->u2.players.end()){
			strbuff<<",";
		//	}
		}
	}
	strncpy(player_update_msg->data,strbuff.str().c_str(),strbuff.str().length());
	if(player_update_msg->data[strbuff.str().length() - 1] == ','){
		player_update_msg->data[strbuff.str().length() - 1] = '\0';
	}
	player_update_msg->data[strbuff.str().length()] = '\0';
	_connection_to_db->SendMsg(player_update_msg);
	_connection_to_db->SendMsg(db_msg);
}



