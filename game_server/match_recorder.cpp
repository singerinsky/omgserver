#include "match_recorder.h"
#include <map>

using namespace omg;

void MatchRecorder::update(void) {
	export_item(_ball_frames, _match->get_ball(), "ball");

	for (int i = 1; i <= RECORDER_PLAYER_COUNT; ++i) {
		update_player(i);
	}
}

void MatchRecorder::update_player(int player_id) {
	int index = player_id - 1;
	PlayerFrameList &player_frames = _players_frames[index];

	if (player_id == 11) {
		SoccerPlayer *gk_player = _match->get_attack_team()->get_gk_player();
		export_item(player_frames, gk_player, "att_gk");
		return;
	} else if (player_id == 22) {
		SoccerPlayer *gk_player = _match->get_defend_team()->get_gk_player();
		export_item(player_frames, gk_player, "def_gk");
		return;
	}

	SoccerPlayer *player = _match->get_player(index < 11 ? 1 : 2,
			index < 11 ? index : index - 11);

/*	for (std::vector<PlayerRedYellowInj>::iterator it = prcyci.begin(); it
			!= prcyci.end(); ++it) {
		if (player->get_union_pid() == it->pid) {
			return;
		}
	}*/

	export_item(player_frames, player, NULL);
}

StringBuilder *MatchRecorder::export_str_player() {

	int flag = 0; // 什么也不做
/*	if (_penalty_count > 0) // 点球大战计数器
	{
		_reverse = 0; // 方向进攻方向

		if (_penalty_count % 2 == 0) {
			flag = 1; // player_id 取反
		}
	}*/

	StringBuilder *str = new StringBuilder(40*1024); // 压缩前长度

	MsgMatchPlayerRoundData msg;//= new MsgMatchRoundData();
	msg.mid = 1;
	msg.player_count = RECORDER_PLAYER_COUNT;
	str->append((const char*) &msg, sizeof(msg) - sizeof(void*));

	for (int i = 0; i < RECORDER_PLAYER_COUNT; ++i) {
		PlayerRoundInfo info;
		info.time_sacle_numbers = _players_frames[i].size();
		info.pid = (*_players_frames[i].begin())->get_player_id();
		info.cond = (*_players_frames[i].begin())->get_player_cond();
		str->append((const char*) &info, sizeof(info) - sizeof(void*));
		save_data(_players_frames[i].begin(), _players_frames[i].end(), str,
				_reverse, _is_half, flag);
	}
	((MsgMatchPlayerRoundData*) str->get_buffer())->msg_size = str->len();
	return str;
}

StringBuilder *MatchRecorder::export_str_ball() {

	int string_len = 100;

	string_len += _ball_frames.size() * 20;
	StringBuilder *str = new StringBuilder(string_len); // 压缩前长度

	MsgGameBallRoundData msg;
	msg.mid =1;
	msg.time_counts = _ball_frames.size();
	str->append((const char*)&msg,sizeof(msg) - sizeof(void*));

	save_data(_ball_frames.begin(), _ball_frames.end(), str, _reverse, _is_half, 0);
	((MsgGameBallRoundData*)str->get_buffer())->msg_size = str->len();

	return str;
}

StringBuilder *MatchRecorder::export_str_event() {
	omg::StringBuilder* str = new StringBuilder(sizeof(GameEvent)*_event_frames.size() + 100);

	MsgGameEventRoundData msg;
	msg.mid = _match_id;
	msg.event_count = _event_frames.size();
	str->append((const char*)&msg,sizeof(msg) - sizeof(void*));
	for (std::vector<MatchEvent>::const_iterator cite_event =
			_event_frames.begin(); cite_event != _event_frames.end(); ++cite_event)//event
	{
		char buff[sizeof(GameEvent)+1];
		GameEvent *event =(GameEvent*)buff;
		event->event_type = cite_event->type;
		//event->cid = cite_event->cid;
		event->src_pid = cite_event->pid;
		event->target_pid = cite_event->op_pid;
		event->time_scale = cite_event->timescale;
		buff[sizeof(GameEvent)] = '\0';
		str->append(buff,sizeof(GameEvent));
	}
	return str;
}

bool MatchRecorder::export_event_db(MsgGameEventDBWB& msg,int time_scale) {
	bool has_shoot = false;
	int goal_side_cid = 0;
	for (std::vector<MatchEvent>::const_iterator cite_event =
			_event_frames.begin(); cite_event != _event_frames.end(); ++cite_event)//event
	{
		if (cite_event->type >= 1 && cite_event->type <= 9) {
			goal_side_cid = msg.event[0].cid = cite_event->cid;
			msg.event[0].timescale = time_scale;
			msg.event[0].pid = cite_event->pid;
			msg.event[0].op_pid = cite_event->op_pid;
			msg.event[0].type = cite_event->type;
			has_shoot = true;
		}
	}

	if(has_shoot == false){
		return false;
	}
	return true;
}



StringBuilder *MatchRecorder::export_str_skill(void){
	omg::StringBuilder* str = new StringBuilder(sizeof(PlayerUseSkill)*_players_skill_vec.size()+100);

	MsgGamePlayerSkillData msg;
	msg.mid = _match_id;
	msg.skill_count = _players_skill_vec.size();
	str->append((const char*)&msg,sizeof(msg) - sizeof(void*));
	for(std::vector<PlayerUseSkill>::const_iterator itr = _players_skill_vec.begin();itr != _players_skill_vec.end();++itr){
		char buff[sizeof(PlayerUseSkill)+1];
		PlayerUseSkill skill_use = *itr;
		memcpy(buff,&skill_use,sizeof(PlayerUseSkill));
		buff[sizeof(PlayerUseSkill)] = '\0';
		str->append(buff,sizeof(PlayerUseSkill));
	}
	return str;
}


MsgMatchPentlyResultData* MatchRecorder::export_pently_data(){
	MsgMatchPentlyResultData *msg = new MsgMatchPentlyResultData();
	msg->mid = _match_id;
	msg->round_count = _match_pently_list.size();
	for(int i=0;i<_match_pently_list.size();i++){
		msg->pently[i].gk_player_id = _match_pently_list[i].gk_player_id;
		msg->pently[i].shooter_player_id = _match_pently_list[i].shooter_player_id;
		msg->pently[i].shoot_success = _match_pently_list[i].shoot_success;
		msg->pently[i].shoot_type = _match_pently_list[i].shoot_dir;
		msg->pently[i].save_type = _match_pently_list[i].save_dir;
		msg->pently[i].shooter_skill = _match_pently_list[i].shooter_skill;
		msg->pently[i].keep_skill = _match_pently_list[i].keep_skill;
		LOG(INFO)<<"SHOOT ."<<msg->pently[i].shooter_skill<<":"<<msg->pently[i].keep_skill;
	}
	return msg;
}

StringBuilder *MatchRecorder::export_str(void) {

	int string_len = 100; // 时间

	string_len += (_ball_frames.size() * 28); // 球


	string_len += (_event_frames.size() * sizeof(MatchEvent)); // 比赛中的event

	string_len += (_buff_frames.size() * sizeof(MatchBuff)); // 球员增加属性

	string_len += (prcyci.size() * sizeof(PlayerRedYellowInj)); // 球员受伤

	string_len += (dpid.size() * sizeof(DefPlayerID)); // 防守球员高亮显示

	int flag = 0; // 什么也不做
	if (_penalty_count > 0) // 点球大战计数器
	{
		_reverse = 0; // 方向进攻方向

		if (_penalty_count % 2 == 0)
		{
			flag = 1; // player_id 取反
		}
	}

	StringBuilder *str = new StringBuilder(string_len); // 压缩前长度

	////////////////////////////////////////////////////// 时间
	if (_start_time < 0)
	{
		_start_time = 0;
	}
	str->append_format("%03X", _start_time);
	str->append_char(',');

	////////////////////////////////////////////////////// 服务器开始时间
	str->append_format("%03X", time(NULL));
	str->append_char(',');

	////////////////////////////////////////////////////// 球
	save_data(_ball_frames.begin(), _ball_frames.end(), str, _reverse, _is_half, flag);
	str->append_char(',');

	////////////////////////////////////////////////////裁判

	////////////////////////////////////////////////////比赛中的事件
	//001 timescale
	//01 type
	//06 pid in
	//00 pid to
	for (std::vector<MatchEvent>::const_iterator cite_event = _event_frames.begin();
			cite_event != _event_frames.end(); ++cite_event)//event
	{
		int symbol = 0;
		int i_temp = cite_event->pid;
		if (i_temp < 0)
		{
			i_temp = abs(i_temp);
			symbol = 1;
		}

		int symbol2 = 0;
		int i_temp2 = cite_event->op_pid;
		if (i_temp2 < 0)
		{
			i_temp2 = abs(i_temp2);
			symbol2 = 1;
		}
		str->append_format("%03X%02X?%03X!%X?%03X!%X;"
				, cite_event->timescale * TIME_SCALE
				, cite_event->type
				, i_temp
				, symbol
				, i_temp2
				, symbol2);
	}
	str->append_char(',');

	////////////////////////////////////////////////////使用属性卡
	//00 pid
	//00 type
	for (std::vector<MatchBuff>::const_iterator cite = _buff_frames.begin();
			cite != _buff_frames.end(); ++cite)
	{
		str->append_format("%02X%X;", cite->position_id, cite->op_buff_typ);
	}
	str->append_char(',');

	////////////////////////////////////////////////////// 进攻方
	int symbol = 0;
	int i_temp = who_att;
	if (who_att < 0)
	{
		i_temp = abs(who_att);
		symbol = 1;
	}
	str->append_format("%03X!%X!%X;", i_temp, symbol, move_typ);
	str->append_char(',');
	//////////////////////////////////////////////////////比赛 红牌 黄牌 受伤
	str->append_format("%X%X%X;", _match_end_r_y_i.red_card, _match_end_r_y_i.yellow_card, _match_end_r_y_i.inj);
	str->append_char(',');

	////////////////////////////////////////////////////受伤 黄牌
	for (std::vector<PlayerRedYellowInj>::iterator ve_it = prcyci.begin();
			ve_it != prcyci.end(); ++ve_it)
	{
		int symbol = 0;
		int i_temp = ve_it->pid;
		if (i_temp < 0)
		{
			i_temp = abs(i_temp);
			symbol = 1;
		}
		str->append_format("%03X!%X?%X?%X;"
				, i_temp // pid
				, symbol // +-
				, ve_it->red_card // 红牌 > 0
				, ve_it->inj); // 受伤 > 0

	}
	str->append_char(',');

	////////////////////////////////////////////////////同步球员顺序
	for (std::map<int, PlayerRedYellowInj>::iterator it = _pid_info.begin();
			it != _pid_info.end(); ++it)
	{
		if (it->first == 1)
		{
			str->append_format("%d!%d!%d!%d!%d;", it->first, gk_pid_1, it->second.inj, it->second.yellow_card, it->second.red_card);
		}
		else if (it->first == 12)
		{
			str->append_format("%d!%d!%d!%d!%d;", it->first, gk_pid_2, it->second.inj, it->second.yellow_card, it->second.red_card);
		}
		else
		{
			str->append_format("%d!%d!%d!%d!%d;", it->first, it->second.pid, it->second.inj, it->second.yellow_card, it->second.red_card);
		}
	}
	str->append_char(',');

	////////////////////////////////////////////////////// 防守球员高亮显示
	for (std::vector<DefPlayerID>::iterator ve_it = dpid.begin();
			ve_it != dpid.end(); ++ve_it)
	{
		int symbol = 0;
		int i_temp = ve_it->pid;
		if (i_temp < 0)
		{
			i_temp = abs(i_temp);
			symbol = 1;
		}
		str->append_format("%03X!%03X!%X;"
				, ve_it->time_scale * TIME_SCALE
				, i_temp // pid
				, symbol); // +-
	}
	str->append_char(',');
	str->append_char('!');
	str->append_char(',');

	//镜头的数据暂时不要
	//save_data(_camera_frames.begin(), _camera_frames.end(), str);

	return str;
}


