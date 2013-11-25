#ifndef _MATCH_ENGIN_EVENTS_H_
#define _MATCH_ENGIN_EVENTS_H_

#include "../common/cmmmo_define.h"
#include "msg.h"
#include <map>
#include <vector>
#include "../soccer_ai/soccer_player.h"
#include "../soccer_ai/soccer_team.h"
#include "GameConfigManage.h"
//一场比赛的预计的时间片
#define TOTAL_NORMAL_MATCH_SCALE 2000

struct NextFormationPos {
	int pid[16];
	int suitable[16];
};

struct NextRoundOperate {
	int _round_index;
	bool is_change_player;
	NextFormationPos pos;
	int _next_formation_id;
	int _next_move_card_id;
	int _next_action_card_id;
	int _next_action_player_id;
	int _next_event_id;
	int _speak_id;
	NextRoundOperate(void) {
		_round_index = 0;
		_next_move_card_id = -1;
		_next_action_card_id = -1;
		_next_action_player_id = 0;
		_next_event_id = 0;
		is_change_player = false;
		_speak_id = -1;
	}

};

struct PlayerInfo {
	PlayerInfo(void) {
		p_score = 0; // 球员得分
		p_goal_count = 0; // 进球
		p_assist_count = 0; // 助攻
		p_foul_count = 0; // 犯规
		p_shot_count = 0; // 射正
		p_no_shot_count = 0; // 射偏
		p_steals_count = 0; // 抢断
		red_card = 0;
		yellow_card = 0;
		inj = 0;
		is_gk = false;
		footedness = 2;
		foul_probability = 30;
		next_round_has_buff = false;
		has_been_to_pitch = false;
		is_on_pitch = false;
		attr.clear();
	}

	void init(void) {
		p_score = 0; // 球员得分
		p_goal_count = 0; // 进球
		p_assist_count = 0; // 助攻
		p_foul_count = 0; // 犯规
		p_shot_count = 0; // 射正
		p_no_shot_count = 0; // 射偏
		p_steals_count = 0; // 抢断
		red_card = 0;
		yellow_card = 0;
		inj = 0;
		is_gk = false;
		footedness = 2;
		foul_probability = 30;
		ca = 0;
		main_pos = 0;
		next_round_has_buff = false;
		attr.clear();
	}

	int pid;
	char player_name[20];
	int pos_index;
	int pos_id;
	int ca;
	int main_pos;
	bool is_gk;
	int cond;
	int att_value;
	int def_value;
	double per_cond_dis;
	int level;
	bool has_been_to_pitch;
	bool is_on_pitch; //是否在场上

	double p_score; // 球员得分
	int p_goal_count; // 进球
	int p_assist_count; // 助攻
	int p_foul_count; // 犯规
	int p_shot_count; // 射正
	int p_no_shot_count; // 射偏
	int p_steals_count; // 抢断

	int red_card; // 红牌 > 0
	int yellow_card; // 黄牌 > 2
	int inj; // 受伤 > 0
	int foul_probability; // 犯规概率(初始化 30)
	int footedness; // 左右脚
	bool next_round_has_buff;// 下一轮的球员是否有buff
	std::map<int, double> attr;
	unsigned short skill_count;
	PlayerSkill skills[10];

	void add_p_score(double value) // 球员得分
	{
		p_score += value;
	}

	void del_p_score(void) // 球员得分
	{
		p_score -= 0.2;
	}

	void add_p_goal_count(void) // 进球struct MatchBuff
	{
		/*    	int mid;
		 int round_id;
		 int pid;
		 int buff_typ;
		 int buff_value;
		 int op_buff_typ;
		 int position_id;
		 int uid;
		 int op_uid;*/
	}

	void add_p_assist_count(void) // 助攻
	{
		++p_assist_count;
	}

	void add_p_foul_count(void) // 犯规
	{
		++p_foul_count;
	}

	void add_p_shot_count(void) // 射正
	{
		++p_shot_count;
	}

	void add_p_no_shot_count(void) // 射偏
	{
		++p_no_shot_count;
	}

	void add_p_steals_count(void) // 抢断
	{
		++p_steals_count;
	}
};

struct SquadInfo {
	SquadInfo(void) {
		score = 0;
		score_info = 0;
		possession = 50;
		shoot_count = 0;
		break_count = 0;
		pass_count = 0;
		shoot_count = 0;
		round_remain = -1;
		score_penalty = 0;
		can_force_offside = false;
		can_avoid_offside = false;
		club_level = 0;
		tactical_points = 0;
		ms_shoot_count = 0;
		formation_level = 0;
		is_all_attack = false;
		_kick_off_count = 0;
	}

	int uid;
	int mid;
	int club_level;
	int formation_id;
	int formation_level;
	int round_remain; // 总进攻数量
	double score;
	int score_info;
	int possession; //控球率
	double att_value;
	double default_att_value;
	double default_def_value;
	double def_value;
	int shoot_count; // 射正
	int ms_shoot_count; // 射门 偏
	int break_count;
	int pass_count;
	int cross_count;
	int tactical_points;
	int hosptial_effect;
	int score_penalty; // 点球大战进球数
	bool can_force_offside;
	bool can_avoid_offside;
	double	alias_tactic_plus;
	short	fitness_coach;
	//是否有球员爆棚
	bool is_all_attack;
	unsigned short _kick_off_count;

	//NPC下一轮的操作
	NextRoundOperate _next_op;

	// pid, PlayerInfo
	std::map<int, PlayerInfo> players;

	//1~11position,pid
	std::map<int, int> pos_map;

	int get_gk_player_pid(void) {
		return pos_map[1];
	}

	int get_player_pos_by_pid(int pid) {
		std::map<int, int>::iterator itr = pos_map.begin();
		while (itr != pos_map.end()) {
			if (itr->second == pid) {
				return itr->first;
			}
			itr++;
		}
		return 0;
	}

	PlayerInfo* get_def_max_player_in_back() {
		std::map<int, PlayerInfo>::iterator itr = players.begin();
		double def_value = 0;
		PlayerInfo* max_def_player = NULL;
		while (itr != players.end()) {
			if ((itr->second.is_gk == false) && (itr->second.def_value
					> def_value) && (itr->second.is_on_pitch == false)
					&& (itr->second.has_been_to_pitch == false)) {
				max_def_player = &(itr->second);
				def_value = itr->second.def_value;
			}
			itr++;
		}
		return max_def_player;
	}

	PlayerInfo* get_attack_max_player_in_back() {
		std::map<int, PlayerInfo>::iterator itr = players.begin();
		double attack_value = 0;
		PlayerInfo* max_def_player = NULL;
		while (itr != players.end()) {
			if ((itr->second.is_gk == false) && (itr->second.att_value
					> attack_value) && (itr->second.is_on_pitch == false)
					&& (itr->second.has_been_to_pitch == false)) {
				max_def_player = &(itr->second);
				attack_value = itr->second.att_value;
			}
			itr++;
		}
		return max_def_player;
	}

	PlayerInfo* get_condition_max_player_in_back() {
		std::map<int, PlayerInfo>::iterator itr = players.begin();
		int cond = 0;
		PlayerInfo* max_cond_player = NULL;
		while (itr != players.end()) {
			if ((itr->second.is_gk == false) && (itr->second.cond > cond)
					&& (itr->second.is_on_pitch == false)
					&& (itr->second.has_been_to_pitch == false)) {
				max_cond_player = &(itr->second);
				cond = itr->second.cond;
			}
			itr++;
		}
		return max_cond_player;
	}

	void add_p_score(int pid, double value) // 球员得分
	{
		PlayerInfo *p = get_player_by_pid(pid);
		if (p != NULL) {
			p->add_p_score(value);
		}
	}

	void del_p_score(int pid) // 球员得分
	{
		PlayerInfo *p = get_player_by_pid(pid);
		if (p != NULL) {
			p->del_p_score();
		}
	}

	void add_p_goal_count(int pid) // 进球
	{
		PlayerInfo *p = get_player_by_pid(pid);
		if (p != NULL) {
			p->p_goal_count++;
		}
	}

	void add_p_assist_count(int pid) // 助攻
	{
		PlayerInfo *p = get_player_by_pid(pid);
		if (p != NULL) {
			p->add_p_assist_count();
		}
	}

	void add_p_foul_count(int pid) // 犯规
	{
		PlayerInfo *p = get_player_by_pid(pid);
		if (p != NULL) {
			p->add_p_foul_count();
		}
	}

	void add_p_shot_count(int pid) // 射正
	{
		PlayerInfo *p = get_player_by_pid(pid);
		if (p != NULL) {
			p->add_p_shot_count();
		}
	}

	void add_p_no_shot_count(int pid) // 射偏
	{
		PlayerInfo *p = get_player_by_pid(pid);
		if (p != NULL) {
			p->add_p_no_shot_count();
		}
	}

	void add_p_steals_count(int pid) // 抢断
	{
		PlayerInfo *p = get_player_by_pid(pid);
		if (p != NULL) {
			p->add_p_steals_count();
		}
	}

	PlayerInfo *get_player_by_pid(int pid) {
		std::map<int, PlayerInfo>::iterator it = players.find(pid);
		if (it != players.end()) {
			return &(it->second);
		}

		return NULL;
	}

	PlayerInfo &get_player_by_position(int pos) {
		PlayerInfo& player = players[pos_map[pos]];
		return player;
	}

	void init_lineup_score(void) {
		for (int i = 1; i <= 11; ++i) {
			get_player_by_position(i).p_score = 6;
		}
	}

	void add_half_score(void) {
		for (int i = 1; i <= 11; ++i) {
			get_player_by_position(i).p_score += 0.5;
		}
	}

	template<class ATTR_T, class ADD_PLUS>
	void add_all_player_attr(ATTR_T _T, ADD_PLUS _plus) {
		std::map<int, PlayerInfo>::iterator itr = players.begin();
		while (itr != players.end()) {
			if (itr->second.attr.find(_T) != itr->second.attr.end()) {
				itr->second.attr[_T] = (itr->second.attr[_T] * _plus) / 100;
			}
			itr++;
		}
	}

	void get_player_withOUt_buff_next_round(
			std::vector<PlayerInfo*>& playerInfo) {
		std::map<int, PlayerInfo>::iterator itr = players.begin();
		while (itr != players.end()) {
			if (itr->second.next_round_has_buff == false) {
				playerInfo.push_back(&(itr->second));
			}
			itr++;
		}
	}

	int get_score_lowest_player_in_list(std::vector<int>& players_vec) {
		//最大不会超过
		int score_number = 100;
		int player_id = 0;

		std::vector<int>::iterator itr = players_vec.begin();
		while (itr != players_vec.end()) {
			if (score_number >= players[*itr].p_score) {
				player_id = *itr;
				score_number = players[*itr].p_score;
			}
			itr++;
		}
		return player_id;
	}

	int get_score_lower_than_value_in_list(std::vector<int>& players_vec,int lowest_score){
		std::vector<int>::iterator itr = players_vec.begin();
		while (itr != players_vec.end()) {
			if (lowest_score >= players[*itr].p_score) {
				return *itr;
			}
			itr++;
		}
		return 0;
	}


	int get_highest_player_from_list(std::vector<PlayerInfo*> &playerList) {
		int pos = 0;
		int scoer = 0;
		std::vector<PlayerInfo*>::iterator itr = playerList.begin();
		while (itr != playerList.end()) {
			if ((*itr)->p_score > scoer) {
				pos = (*itr)->pos_id;
				scoer = (*itr)->p_score;
			}

			itr++;
		}
		return pos;
	}

	int get_highest_player(void) {
		int pos = 0;
		int scoer = 0;
		std::map<int, PlayerInfo>::iterator itr = players.begin();
		while (itr != players.end()) {
			if (itr->second.p_score > scoer) {
				pos = itr->second.pos_id;
				score = itr->second.p_score;
			}
			itr++;
		}
		return pos;
	}

	int pick_replace_player(int player_pos, int replaced_order) {
		/*		int pos = SoccerTeam::check_position(player_pos);
		 if(pos == 1){

		 }else if(pos == 2){

		 }else if(pos == 3){

		 }*/
		return 12 + replaced_order;
	}
};

typedef std::map<int, FormationDefine> CARD_FORMATION;

struct FixtureInfo {
	FixtureInfo(MsgMatchTeamInfo *info) {
		type = info->type;
		need_pently_shoot = info->need_win;
		newbie_stat = info->is_home_in_new_bie;
		total_time_scale = info->total_time_scale;
		if (total_time_scale <= 0 || total_time_scale > 3000) {
			total_time_scale = 2000;
		}
		if (info->is_home_all_attack) {
			u1.is_all_attack = true;
		}

		u1.uid = info->op1.uid;
		u1.formation_id = info->op1.formation_id;
		u1.formation_level = info->op1.formation_level;
		u1.club_level = info->op1.club_level;
		u1.att_value = info->op1.att_value;
		u1.def_value = info->op1.def_value;
		u1.alias_tactic_plus = ((double)(info->op1.alias_tactic_plus))/10000.;
		u1.default_att_value = info->op1.default_att_value;
		u1.default_def_value = info->op1.default_def_value;
		u1.fitness_coach	= info->op1.fitness_coach;
		u1._next_op._next_move_card_id = info->op1.tactic_id;
		u1._next_op._speak_id = info->op1.default_coach_speak;
		for (int i = 0; i < 16; i++) {
			PlayerInfo p;
			p.pid = info->op1.player_info[i].pid;
			memcpy(p.player_name, info->op1.player_info[i].player_name, 19);
			p.player_name[19] = '\0';//游戏中球员的名字
			p.level = info->op1.player_info[i].level;
			p.pos_index = info->op1.player_info[i].pos_index;
			//5,6,7比赛初始体力都100
			if (type==1 || type== 2) {
				p.cond = info->op1.player_info[i].cond;
			} else {
				p.cond = 100;
			}
			p.att_value = info->op1.player_info[i].att_value;
			p.def_value = info->op1.player_info[i].def_value;
			p.is_gk = (bool) info->op1.player_info[i].is_gk;
			for (int attr_index = 0; attr_index < 19; attr_index++) {
				p.attr[attr_index] = info->op1.player_info[i].attr[attr_index];
			}
			p.skill_count = info->op1.player_info[i].skill_count;
			int skill_count = 0;
			if (info->op1.player_info[i].skill_count > 8) {
				LOG(ERROR) << "Error player skill info" << p.pid;
			} else {
				for (; skill_count < info->op1.player_info[i].skill_count; skill_count++) {
					p.skills[skill_count].skill_id
							= info->op1.player_info[i].player_skills[skill_count].skill_id;
					p.skills[skill_count].skill_level
							= info->op1.player_info[i].player_skills[skill_count].skill_level;
					p.skills[skill_count].skill_chance
							= info->op1.player_info[i].player_skills[skill_count].skill_chance;
				}
			}
			double temp_value = 0.;
			if(newbie_stat == 0){
				p.per_cond_dis = 0.;
			}else{
				if (u1.uid < 0 && u2.uid > 0) {
					temp_value = (double) (p.attr[2] * 100
							/ (double) info->npc_rate) / 50;
				} else {
					temp_value = (double) p.attr[2] / (double) p.level;
				}

				if (temp_value > 4.) {
					temp_value = 4.;
				}
				temp_value = 4. - temp_value;
				double total_match_cond_dis = 1. - (0.98 - temp_value * 0.14);
				if (type == 2) {
					total_match_cond_dis = total_match_cond_dis
							* ((double) u1.club_level + 50.) * 0.01;
				}
				if (type == 7 || type == 8 || type == 9) {//体力消耗加倍
					p.per_cond_dis = total_match_cond_dis * 1.2 / total_time_scale;
				} else {
					p.per_cond_dis = total_match_cond_dis / total_time_scale;
				}
			}

			u1.players[p.pid] = p;
			u1.pos_map[i + 1] = p.pid;
		}
		u2.uid = info->op2.uid;
		u2.formation_id = info->op2.formation_id;
		u2.formation_level = info->op2.formation_level;
		u2.club_level = info->op2.club_level;
		u2.att_value = info->op2.att_value;
		u2.def_value = info->op2.def_value;
		u2.alias_tactic_plus = (double)(info->op2.alias_tactic_plus)/10000.;
		u2._next_op._next_move_card_id = info->op2.tactic_id;
		u2.default_att_value = info->op2.default_att_value;
		u2.default_def_value = info->op2.default_def_value;
		u2.fitness_coach	= info->op2.fitness_coach;
		u2._next_op._speak_id = info->op2.default_coach_speak;
		for (int i = 0; i < 16; i++) {
			PlayerInfo p;
			p.pid = info->op2.player_info[i].pid;
			memcpy(p.player_name, info->op2.player_info[i].player_name, 20);
			p.player_name[19] = '\0';//游戏中球员的名字
			p.level = info->op2.player_info[i].level;
			p.pos_index = info->op2.player_info[i].pos_index;
			//5,6,7比赛初始体力都100
			if (type==1 || type== 2) {
				p.cond = info->op2.player_info[i].cond;
			} else {
				p.cond = 100;
			}
			p.att_value = info->op2.player_info[i].att_value;
			p.def_value = info->op2.player_info[i].def_value;
			p.is_gk = (bool) info->op1.player_info[i].is_gk;
			for (int attr_index = 0; attr_index < 19; attr_index++) {
				p.attr[attr_index] = info->op2.player_info[i].attr[attr_index];
			}
			p.skill_count = info->op2.player_info[i].skill_count;
			for (int skill_count = 0; skill_count < p.skill_count; skill_count++) {
				p.skills[skill_count].skill_id
						= info->op2.player_info[i].player_skills[skill_count].skill_id;
				p.skills[skill_count].skill_level
						= info->op2.player_info[i].player_skills[skill_count].skill_level;
				p.skills[skill_count].skill_chance
						= info->op2.player_info[i].player_skills[skill_count].skill_chance;
			}
			double temp_value = 0.;
			if (u2.uid < 0 && u1.uid > 0) {
				temp_value = (double) (p.attr[2] * 100
						/ (double) info->npc_rate) / 50;
			} else {
				temp_value = (double) p.attr[2] / (double) p.level;
			}

			if (temp_value > 4.) {
				temp_value = 4.;
			}
			temp_value = 4. - temp_value;
			double total_match_cond_dis = 1. - (0.98 - temp_value * 0.14);
			//如果是玩家联赛的话，减慢消耗
			if (type == 2) {
				total_match_cond_dis = total_match_cond_dis
						* ((double) u2.club_level + 50.) * 0.01;
			}

			if (type == 7 || type == 8 || type == 9) {//体力消耗加倍
				p.per_cond_dis = total_match_cond_dis * 1.2 / total_time_scale;
			} else {
				p.per_cond_dis = total_match_cond_dis / total_time_scale;
			}

			u2.players[p.pid] = p;
			u2.pos_map[i + 1] = p.pid;
		}

		u1.possession = static_cast<int>((u1.att_value + u1.def_value) * 100. / (u1.att_value
				+ u1.def_value + u2.att_value + u2.def_value));
		u2.possession = 100 - u1.possession;
		u1._next_op._next_formation_id = info->op1.formation_id;
		u1._next_op._next_move_card_id = info->op1.tactic_id;

		u2._next_op._next_formation_id = info->op2.formation_id;
		u2._next_op._next_move_card_id = info->op2.tactic_id;
		init_round_kick_off_count();
	}
	SquadInfo u1; // 挑战者
	SquadInfo u2; // 被挑战者
	int type;
	int newbie_stat;
	int need_pently_shoot; // 0 没有 1 有 是否需要有点球大战
	int is_double_elimination; // 双淘汰是否是第2场
	int double_elimination_score1; // 双淘汰第1场比分
	int double_elimination_score2; // 双淘汰第1场比分
	int total_time_scale; //整場比賽時間片數量

	CARD_FORMATION card_formation;

	SquadInfo *get_SquadInfo(int uid) {
		if (u1.uid == uid) {
			return &u1;
		}

		return &u2;
	}

	void init_lineup_score(void) {
		u1.init_lineup_score();
		u2.init_lineup_score();
	}

	void init_round_kick_off_count() {
		int home_value = static_cast<int>(u1.att_value + u1.def_value);
		int away_value = static_cast<int>(u2.att_value + u2.def_value);
		if(type == 1 || type == 6){
			double percent = (double)home_value / (double)(home_value + away_value);
			u1._kick_off_count = static_cast<unsigned short>(10 * percent);
			u2._kick_off_count = static_cast<unsigned short>(10 - u1._kick_off_count);
		}else{
			if(home_value > away_value){
				u1._kick_off_count = static_cast<unsigned short>(10*(1.5*(double)home_value-0.5*(double)away_value)/((double)home_value+(double)away_value));
				if(u1._kick_off_count > 10){
					u1._kick_off_count = 10;
				}
				u2._kick_off_count = 10 - u1._kick_off_count;
			}else{
				u2._kick_off_count = static_cast<unsigned short>(10*(1.5*(double)away_value-0.5*(double)home_value)/((double)home_value+(double)away_value));
				if(u2._kick_off_count > 10){
					u2._kick_off_count = 10;
				}
				u1._kick_off_count = 10 - u2._kick_off_count;
			}
			LOG(INFO)<<"u1 value"<<home_value<<" u2 value"<<away_value<<"  "<<u1._kick_off_count<<":"<<u2._kick_off_count;
		}
	}

	void get_next_round_kick_off_att_team(int& att_team_id, int& def_team_id) {
		if ((u1._kick_off_count == 0) && (u2._kick_off_count == 0)) {
			init_round_kick_off_count();
		}

		if(u1._kick_off_count >= u2._kick_off_count){
				att_team_id = u1.uid;
				def_team_id = u2.uid;
				dis_squad_kick_off_count(u1.uid);
		}else{
				att_team_id = u2.uid;
				def_team_id = u1.uid;
				dis_squad_kick_off_count(u2.uid);
		}
	}

	void dis_squad_kick_off_count(int team_id){
		if(u1.uid == team_id){
			u1._kick_off_count--;
		}else{
			u2._kick_off_count--;
		}
	}

	int get_squad_kick_off_count(int team_id){
		if(u1.uid == team_id){
			return u1._kick_off_count;
		}else{
			return u2._kick_off_count;
		}
	}

};

enum {
	EVENT_MATCH_INFO_QUERY = 1,
	EVENT_MATCH_INFO_RESULT,
	EVENT_MOVE_OPERATOR_QUERY,
	EVENT_MOVE_OPERATOR_RESULT,
	EVENT_ROUND_SAVE,
	EVENT_UPDATE_SCORE,
	EVENT_INSERT_E_FIXTURE,
	EVENT_INSERT_ROUNT,
	EVENT_UPDATE_NPC_OP,
	EVENT_CHANGE_MOVE_CARD,
	EVENT_CHANGE_ACTION_CARD,
	EVENT_CHANGE_EVENT_CARD
};
/*

 struct MatchInfoQueryEvent : public edog::EventBase<MatchInfoQueryEvent, EVENT_MATCH_INFO_QUERY>
 {
 MatchInfoQueryEvent(match_id_t mid
 , int match_typ
 , int studium_id
 , edog::EventSink *sink
 , uint32_t channel)
 {
 biz_sink 	 = sink;
 sink_channel = channel;
 match_id 	 = mid;
 _studium_id  = studium_id;mg::EventType::USER
 _match_typ   = match_typ;
 }

 edog::EventSink *biz_sink;
 uint32_t 		sink_channel;
 match_id_t 		match_id;
 int 			_studium_id;
 int 			_match_typ;
 };

 struct MatchInfoResultEvent : public edog::EventBase<MatchInfoResultEvent, EVENT_MATCH_INFO_RESULT>
 {
 match_id_t 	match_id;
 int        	_stadium_id;
 int			_match_typ;
 FixtureInfo *match_info;
 };

 struct MoveOperatorQueryEvent : public edog::EventBase<MoveOperatorQueryEvent, EVENT_MOVE_OPERATOR_QUERY>
 {
 MoveOperatorQueryEvent(match_id_t mid
 , edog::EventSink *sink
 , uint32_t channel
 , int rid)
 {
 biz_sink 	 	= sink;
 sink_channel 	= channel;
 match_id 		= mid;
 this->round_id 	= rid;
 }

 match_id_t 		match_id;
 edog::EventSink *biz_sink;
 uint32_t 		sink_channel;
 int 			round_id;
 };

 struct RoundSaveEvent : public edog::EventBase<RoundSaveEvent, EVENT_ROUND_SAVE>
 {
 match_id_t 		match_id;
 int 			u1;
 int 			u2;

 RoundSaveEvent(void)
 {
 match_id 	= 0;
 u1 			= 0;
 u2 			= 0;
 }

 ~RoundSaveEvent(void)
 {

 }
 };
 */

struct PlayerScore {
	int p_pid;
	double p_score; // 球员得分
	int p_goal_count; // 进球
	int p_assist_count; // 助攻
	int p_foul_count; // 犯规
	int p_shot_count; // 射正
	int p_no_shot_count; // 射偏
	int p_steals_count; // 抢断

	int cond; // 体力
	int red_card; // 红牌 > 0
	int yellow_card; // 黄牌 > 2
	int inj; // 受伤 > 0
};

struct TeamScore {
	int score; // 最终比分
	int score_info; // 当前比分
	int possession;
	int shoot_count; // 射正
	int break_count;
	int pass_count;
	int cross_count;

	int ms_assists_count; // team助攻
	int ms_foul_count; // team犯规
	int ms_shot_count; // team射门
	int ms_steals_count; // team抢断

	int ms_red_card; // 红牌 > 0
	int ms_yellow_card; // 黄牌 > 2
	int ms_inj; // 受伤 > 0

	int score_penalty;

	std::vector<PlayerScore> player_score;
};
#endif
