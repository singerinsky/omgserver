#include "../common/head.h"

#include "match.h"
#include "../common/rand_generator.h"
#include "../soccer_ai/soccer_player.h"
#include "../soccer_ai/soccer_match.h"
#include "../soccer_ai/enum.h"

using namespace std;
using namespace omg;

extern std::map<int, ActionDefine *> g_action_define_table;
extern std::map<int, EventDefine *> g_event_define_table;
extern int g_move_id;

ActionDefine *pickup_random_action_by_quality(int quality) {
	std::vector<ActionDefine *> action_vec;
	std::map<int, ActionDefine *>::iterator itr = g_action_define_table.begin();
	while (itr != g_action_define_table.end()) {
		if (itr->second->card_quality == quality) {
			action_vec.push_back(itr->second);
		}
		itr++;
	}

	int number = action_vec.size();
	if (number == 0) {
		return NULL;
	}
	int index_pickup = RAND_INT % number;

	return action_vec[index_pickup];
}

EventDefine *pickup_random_event_by_quality(int quality) {
	std::vector<EventDefine *> event_vec;
	std::map<int, EventDefine *>::iterator itr = g_event_define_table.begin();
	while (itr != g_event_define_table.end()) {
		if (itr->second->card_quality == quality) {
			event_vec.push_back(itr->second);
		}
		itr++;
	}

	int number = event_vec.size();
	if (number == 0) {
		return NULL;
	}
	int index_pickup = RAND_INT % number;

	return event_vec[index_pickup];
}

Match::Match(){

}

Match::Match(FixtureInfo *fixture_info, match_id_t match_id, int match_typ,
		user_id_t uid1, user_id_t uid2) {
	Init(fixture_info,match_id,match_typ,uid1,uid2);
}

Match::~Match(void) {
	if (_soccer_match) {
		delete _soccer_match;
		_soccer_match = NULL;
	}
	_match_id = -1;
	_uid1 = -1;
	_uid2 = -1;
	/*
	 delete _watcher_set;
	 _watcher_set = NULL;*/

	delete _fixture_info;
	_fixture_info = NULL;
}

void Match::Init(FixtureInfo *fixture_info, match_id_t match_id, int match_typ,
		user_id_t uid1, user_id_t uid2){
		_fixture_info = fixture_info;
		_match_id = match_id;
		_match_typ = match_typ;
		_total_time_scale = fixture_info->total_time_scale;
		_uid1 = uid1;
		_uid2 = uid2;
		home_player_id = uid1;
		away_player_id = uid2;
		_round_info.home_uid = uid1;
		_round_info.away_uid = uid2;
		_round_info._round_split_log_info = &_round_split_log_info;

		_time_scale = 0;
		_round_id = 0;
		_first_half = true;
		_soccer_match = NULL;

		prcyci.clear();
		_penalty_count = 0;
		_pid_info.clear();

		_count_corent = 0;
		_count_penalty = 0;
		_count_free = 0;
		_quick_terminal = false;
		_match_init_zeit = ::time(NULL);
		_need_win = fixture_info->need_pently_shoot;
		_is_fast_match = false;
}


void Match::update_player_info(FixtureInfo *fixture_info, bool reverse,
		int time_interval) {
	SoccerTeam* t1 = _soccer_match->get_team(1);
	t1->set_newbie_state(fixture_info->newbie_stat);
	if (fixture_info->newbie_stat == 0) {
		t1->setTeamMode(GOD_MODE);
	}
	t1->set_formation_level(fixture_info->u1.formation_level);
	t1->set_team_cid(fixture_info->u1.uid);
	t1->set_team_level(fixture_info->u1.club_level);
	t1->set_team_all_attack(fixture_info->u1.is_all_attack);
	t1->coach_speak_effect(fixture_info->u1._next_op._speak_id);
	t1->set_alias_tactic_plus(fixture_info->u1.alias_tactic_plus);
	t1->set_fitness_coach(fixture_info->u1.fitness_coach);
	SoccerTeam* t2 = _soccer_match->get_team(2);
	t2->set_team_cid(fixture_info->u2.uid);
	t2->set_formation_level(fixture_info->u2.formation_level);
	t2->set_team_level(fixture_info->u2.club_level);
	t2->set_team_all_attack(fixture_info->u2.is_all_attack);
	t2->set_alias_tactic_plus(fixture_info->u2.alias_tactic_plus);
	t2->set_fitness_coach(fixture_info->u2.fitness_coach);
	t2->coach_speak_effect(fixture_info->u2._next_op._speak_id);

	if (fixture_info->newbie_stat == 0) {
		t2->setTeamMode(LOSER_MODE);
	}

	for (int i = 1; i <= 11; ++i) // 主场
	{
		SoccerPlayer *player = NULL;
		if (i == 1) {
			player = t1->get_gk_player();
		} else {
			player = t1->get_player_on_pitch(i - 2);
		}

		PlayerInfo& player_info = _fixture_info->u1.get_player_by_position(i);
		load_player(player, player_info);
	}
	FormationDefine* define =
			CGameConfigManager::GetInstance()->GetFormationById(
					fixture_info->u1.formation_id);
	if (define == NULL) {
		LOG(ERROR) << "error of formation..." << fixture_info->u1.mid;
	} else {
		int att_value = fixture_info->u1.att_value
				* (1. + (double) (define->att_buff
						* fixture_info->u1.formation_level) / 1000.);
		int def_value = fixture_info->u1.def_value
				* (1. + (double) (define->def_buff
						* fixture_info->u1.formation_level) / 1000.);
		t1->setAtt_value(att_value);
		t1->setDef_value(def_value);
		t1->set_team_attack_mp(fixture_info->u1.default_att_value);
		t1->set_team_def_mp(fixture_info->u1.default_def_value);
	}

	for (int i = 1; i <= 11; ++i) { //客场
		SoccerPlayer *player = NULL;
		if (i == 1) {
			player = t2->get_gk_player();
		} else {
			player = t2->get_player_on_pitch(i - 2);
		}
		PlayerInfo& player_info = _fixture_info->u2.get_player_by_position(i);
		load_player(player, player_info);
	}

	define = CGameConfigManager::GetInstance()->GetFormationById(
			fixture_info->u2.formation_id);
	if (define == NULL) {
		LOG(ERROR) << "error of formation..." << fixture_info->u1.mid;
	} else {
		int att_value = fixture_info->u2.att_value
				* (1. + (double) (define->att_buff
						* fixture_info->u2.formation_level) / 1000.);
		int def_value = fixture_info->u2.def_value
				* (1. + (double) (define->def_buff
						* fixture_info->u2.formation_level) / 1000.);
		t2->setAtt_value(att_value);
		t2->setDef_value(def_value);
		t2->set_team_attack_mp(fixture_info->u2.default_att_value);
		t2->set_team_def_mp(fixture_info->u2.default_def_value);
	}
	_round_split_log_info.home_att = t1->getAtt_value() + t1->getDef_value();
	_round_split_log_info.away_att = t2->getAtt_value() + t2->getDef_value();
}

void Match::set_pid_info(int pid, int player_id, bool reverse, int inj,
		int red_card, int yellow_card) {
	struct PlayerRedYellowInj p;
	p.pid = pid;
	p.inj = inj;
	p.red_card = red_card;
	p.yellow_card = yellow_card;

	int tmp_player_id = player_id + 1;
	if (reverse) {
		if (tmp_player_id <= 11) {
			tmp_player_id += 11;
		} else {
			tmp_player_id -= 11;
		}
	}

	this->_pid_info.insert(std::map<int, PlayerRedYellowInj>::value_type(
			tmp_player_id, p));
}
/*
 void Match::update_player_info_end(FixtureInfo *fixture_info, bool reverse) {
 SoccerTeam *t1 = NULL;
 SoccerTeam *t2 = NULL;

 if (reverse) {
 t1 = _soccer_match->get_team(2);
 t2 = _soccer_match->get_team(1);
 } else {
 t1 = _soccer_match->get_team(1);
 t2 = _soccer_match->get_team(2);
 }

 for (std::vector<SoccerPlayer *>::iterator it = t1->get_players().begin(); it
 != t1->get_players().end(); ++it) // 挑战者
 {
 std::map<int, PlayerInfo>::iterator player_info =
 _fixture_info->u1.players.find((*it)->get_union_pid());
 if (player_info != _fixture_info->u1.players.end()) {
 SoccerPlayer *player = *it;
 player_info->second.attr[ATTR_STATE] = player->get_attr(ATTR_STATE);
 player_info->second.red_card = player->get_red_card();
 player_info->second.yellow_card = player->get_yellow_card();
 player_info->second.inj = player->get_inj();

 this->set_prcyci(player_info->second.red_card,
 player_info->second.inj, player_info->second.pid);
 }
 }

 for (std::vector<SoccerPlayer *>::iterator it = t2->get_players().begin(); it
 != t2->get_players().end(); ++it) {
 std::map<int, PlayerInfo>::iterator player_info =
 _fixture_info->u2.players.find((*it)->get_union_pid());
 if (player_info != _fixture_info->u2.players.end()) {
 SoccerPlayer *player = *it;
 player_info->second.attr[ATTR_STATE] = player->get_attr(ATTR_STATE);
 player_info->second.red_card = player->get_red_card();
 player_info->second.yellow_card = player->get_yellow_card();
 player_info->second.inj = player->get_inj();

 this->set_prcyci(player_info->second.red_card,
 player_info->second.inj, player_info->second.pid);
 }
 }
 }*/

void Match::set_prcyci(int red_card, int inj, int pid) {
	if (red_card > 0 || inj > 0) {
		std::vector<PlayerRedYellowInj>::iterator it = prcyci.begin();
		for (; it != prcyci.end(); ++it) {
			if (pid == it->pid) {
				break;
			}
		}

		if (it == prcyci.end()) {
			PlayerRedYellowInj p;
			p.pid = pid;
			p.red_card = red_card;
			p.inj = inj;
			prcyci.push_back(p);
		}
	}
}

extern std::map<int, MoveDefine *> g_move_define_table;
/*
 void Match::add_match_buff(std::vector<MatchBuff>::const_iterator cite // BUFF的一条记录
 , SquadInfo &u // Team
 , MatchRecorder *recorder) // Data
 {
 PlayerInfo &pi = u.players[cite->pid];

 if (cite->buff_typ == ATTR_ROUND_ADD) // 加round
 {
 RoundDetail *pRoundDetail = get_current_detail();
 for (int i = 1; i <= cite->buff_value; ++i) {
 fix_next_round(pRoundDetail, N_CARD_ADD_ROUND_KICK, cite->uid);
 }
 } else if (cite->buff_typ == BUFF_CUER) // 取消受伤
 {
 pi.inj = 0;

 std::vector<PlayerRedYellowInj>::iterator it = prcyci.begin();
 for (; it != prcyci.end(); ++it) {
 if (it->pid == pi.pid) {
 prcyci.erase(it);
 break;
 }
 }

 recorder->set_buff_frames(cite);
 } else if (cite->buff_typ == REFEREE_BIAS)// 裁判偏向性
 { // 增加对方的防守犯规概率
 for (std::map<int, PlayerInfo>::iterator it = u.players.begin(); it
 != u.players.end(); ++it) {
 it->second.foul_probability = it->second.foul_probability * (1
 - cite->buff_value / 100);
 }
 } else if (cite->buff_typ == ADD_OFFSIDE_CANCEL)// 给越位
 { // 对方进球后触发
 u.can_force_offside = true;
 if (u.score > 0) {
 u.score -= 1;
 }
 } else if (cite->buff_typ == RE_OFFSIDE_CANCEL)// 取消越位
 { // 对方进球后触发
 u.can_avoid_offside = true;
 u.score += 1;
 } else if (cite->buff_typ == ADD_THE_PENALTY)// 给点球
 { // 对方禁区内抢断成功
 RoundDetail *pRoundDetail = get_previous_detail();
 add_current_round(pRoundDetail, ADD_THE_PENALTY, cite->uid);
 } else if (cite->buff_typ == RE_THE_PENALTY)// 取消点球
 {
 RoundDetail *pRoundDetail = get_current_detail();
 del_round_list(pRoundDetail->index);
 } else if (cite->buff_typ == ADD_YELLOW_CARD)// 给黄牌
 { // 当得黄牌的时候
 pi.yellow_card += 1;
 if (pi.yellow_card >= 2) {
 pi.yellow_card = 0;
 pi.red_card = 1;
 }

 if (_player_pos.x > 0) {
 RoundDetail *pRoundDetail = get_previous_detail();
 add_current_round(pRoundDetail, ADD_YELLOW_CARD, cite->uid);
 }
 } else if (cite->buff_typ == RE_YELLOW_CARD)// 取消黄牌
 { // 犯规并且没有给牌
 if (pi.yellow_card > 0) {
 pi.yellow_card -= 1;
 }

 if (_player_pos.x > 0) {
 RoundDetail *pRoundDetail = get_current_detail();
 del_round_list(pRoundDetail->index);
 }
 } else if (cite->buff_typ == ADD_RED_CARD)// 给红牌
 { // 当得黄牌的时候
 pi.red_card = 1;
 } else if (cite->buff_typ == RE_RED_CARD)// 取消红牌
 { // 当得黄牌的时候
 if (pi.red_card > 0) {
 pi.red_card = 0;
 }
 } else if (cite->buff_typ == GLOBAL_SPEED_ADD) { // 全局加成属性
 u.add_all_player_attr<PlayerAttribueIndex, double> (SPEED_PACE,
 cite->buff_value);
 u.add_all_player_attr<PlayerAttribueIndex, double> (SPEED_ACC,
 cite->buff_value);
 } else if (cite->buff_typ == GLOBAL_PHY_ADD) {
 u.add_all_player_attr<PlayerAttribueIndex, double> (PHY_STR,
 cite->buff_value);
 u.add_all_player_attr<PlayerAttribueIndex, double> (PHY_STA,
 cite->buff_value);
 } else if (cite->buff_typ == GLOBAL_DEF_ADD) {
 u.add_all_player_attr<PlayerAttribueIndex, double> (DEF_MARK,
 cite->buff_value);
 u.add_all_player_attr<PlayerAttribueIndex, double> (DEF_TACK,
 cite->buff_value);
 u.add_all_player_attr<PlayerAttribueIndex, double> (DEF_POSIT,
 cite->buff_value);
 u.add_all_player_attr<PlayerAttribueIndex, double> (DEF_AGGR,
 cite->buff_value);
 } else if (cite->buff_typ == GLOBAL_MENTAL_ADD) {
 u.add_all_player_attr<PlayerAttribueIndex, double> (MENTAL_WORK,
 cite->buff_value);
 u.add_all_player_attr<PlayerAttribueIndex, double> (MENTAL_CONS,
 cite->buff_value);
 } else if (cite->buff_typ == GLOBAL_TEC_ADD) {
 u.add_all_player_attr<PlayerAttribueIndex, double> (TEC_FIRST_TOUCH,
 cite->buff_value);
 u.add_all_player_attr<PlayerAttribueIndex, double> (TEC_CROSS,
 cite->buff_value);
 u.add_all_player_attr<PlayerAttribueIndex, double> (TEC_PASS,
 cite->buff_value);
 u.add_all_player_attr<PlayerAttribueIndex, double> (TEC_MOVE,
 cite->buff_value);
 } else if (cite->buff_typ == GLOBAL_GK_ADD) {
 u.add_gk_player_all_attr(cite->buff_value);
 } else if (cite->buff_typ == GK_SAVE_HAND) {
 u.add_gk_player_all_attr_save_hand(cite->buff_value);
 } else // 球员属性
 {
 PlayerInfo &pi = u.players[cite->pid];
 std::map<int, double>::iterator ite = pi.attr.find(cite->buff_typ);
 VLOG(3)<< "cite->buff_typ:" << cite->buff_typ;
 if (ite != pi.attr.end())
 {
 VLOG(3) << "cite->buff_typ:" << cite->buff_typ;
 ite->second = (double)cite->buff_value;
 recorder->set_buff_frames(cite);
 }
 }
 }*/

void Match::who_kick_off(int t_sub_card_typ, RoundDetail *pRoundDetail) {
	int t_rand = (int) (rand() % 100);
	if (t_sub_card_typ * 10 + 50 < t_rand) {
		pRoundDetail->att_uid = this->home_player_id;
		pRoundDetail->def_uid = this->away_player_id;
	}
}

int Match::match_new_move(MatchRecorder *recorder, int& run_time_scale) {
	VLOG(1)<<"Starting new move ......";
	RoundDetail& roundDetail = get_current_round_info();
	if (roundDetail.att_uid != _fixture_info->u1.uid) {
		_soccer_match->set_attack_and_defend_team(
				_soccer_match->get_away_team(), _soccer_match->get_home_team());
	} else {
		_soccer_match->set_attack_and_defend_team(
				_soccer_match->get_home_team(), _soccer_match->get_away_team());
	}

	_soccer_match->get_away_team()->setTeamMode(DS_MODE);
	_soccer_match->get_home_team()->setTeamMode(DS_MODE);

	int ret = 1;

	/* 选取进攻方和防守方的卡牌 */
	SoccerTeam* attack_team = _soccer_match->get_attack_team();
	SoccerTeam* defend_team = _soccer_match->get_defend_team();

	int skill_id = 0;
	skill_id = check_team_skill_use(attack_team,_match_typ);
	int move_id = -1;//_soccer_match->get_attack_team()->get_current_move_card_id();
	if (skill_id != 0) {
		move_id = attack_team->select_move_by_tactic_id(skill_id);
		if(move_id == -1){
			LOG(ERROR)<<"with no suitable move"<<skill_id;	
		}
	}
	roundDetail.att_team_skill_id = skill_id;

	/*g_game_config.reload();
	  move_id = g_game_config.get_player_config("force_move_id");
	  VLOG(0)<<"Debug move "<<move_id;
	 */
	MoveDefine* move_define_tmp = NULL;
	if (move_id == -1) {//try use team skill ,not success
		move_define_tmp = CGameConfigManager::GetInstance()->GetMoveRandom();
	} else {
		move_define_tmp = CGameConfigManager::GetInstance()->GetMoveCardById(move_id);
	}

	if (move_define_tmp == NULL) {
		LOG(ERROR)<<"move id "<<move_id<<"not found";
		move_id = 3;
		move_define_tmp = CGameConfigManager::GetInstance()->GetMoveCardById(move_id);
	}
	MoveDefine *move_define = new MoveDefine(*move_define_tmp);

	/* 得到进攻卡类型 */
	int add_move_typ = move_define->get_move_typ();

	_soccer_match->set_status(0);
	_soccer_match->reset_timer();
	_soccer_match->set_team_player_pos(_player_pos.x, _player_pos.y);

	int team_attck_formation_id = attack_team->get_current_formation_card_id();
	int team_defend_formation_id = defend_team->get_current_formation_card_id();

	int *attack_fr = CGameConfigManager::GetInstance()->GetFormationById(team_attck_formation_id)->formation;
	int *defend_fr = CGameConfigManager::GetInstance()->GetFormationById(team_defend_formation_id)->formation;
	_soccer_match->init_match(roundDetail.typ, move_define, attack_fr, defend_fr);

	attack_team->get_action_list().clear();
	defend_team->get_action_list().clear();
	_soccer_match->reset_timer();
	int flag_add_move_typ = 2;
	/* 进攻防守 */
	recorder->set_who_att_move_typ(flag_add_move_typ, _soccer_match->get_attack_team()->get_team_cid(),
			add_move_typ);

	recorder->update();
	_soccer_match->set_fake_shoot_ending(0);

	int end_type;
	run_time_scale = do_match_loop(*recorder,end_type);

	/* 比赛中的事件 */
	std::vector<MatchEvent>::iterator it = _soccer_match->get_event_frames()->begin();
	while(it!= _soccer_match->get_event_frames()->end())
	{
		recorder->set_event_frames(it->timescale,it->cid, it->type, it->pid, it->op_pid);
		it++;
	}
	_soccer_match->get_event_frames()->clear();

	//比赛中的技能使用

	for (std::vector<MatchSkillEvent>::iterator it = _soccer_match->get_skill_frames()->begin();
			it != _soccer_match->get_skill_frames()->end(); ++it)
	{
		recorder->add_skill_frames(it->timescale,it->skill_id,it->pid);
	}
	std::copy(_soccer_match->get_skill_frames()->begin(),_soccer_match->get_skill_frames()->end(),std::back_inserter(_all_player_skill_used));
	_soccer_match->get_skill_frames()->clear();

	//比赛中的点球
	recorder->set_pently_event(_soccer_match->get_pently_frames());

	_soccer_match->get_pently_frames()->clear();

	calc_assist_or_goal_score(attack_team,defend_team, true);
	calc_assist_or_goal_score(defend_team,attack_team, true);
	return ret;
}

void Match::export_all_skill_player_used(std::ostringstream& str) {
	std::list<MatchSkillEvent>::iterator itr = _all_player_skill_used.begin();
	while (itr != _all_player_skill_used.end()) {
		str << itr->timescale;
		str << ":";
		str << itr->skill_id;
		str << ":";
		str << itr->pid;
		itr++;
		if (itr != _all_player_skill_used.end()) {
			str << "#";
		}
	}
}

void Match::export_all_team_cmp_info(std::ostringstream& str) {
	SoccerTeam* team_1 = _soccer_match->get_team(1);
	team_1->dump_team_cmp_info(str);
}

void Match::export_team_round_split(std::ostringstream &str) {
	str << _round_split_log_info.home_att;
	str << ":";
	str << _round_split_log_info.home_round_count;
	str << "#";
	str << _round_split_log_info.away_att;
	str << ":";
	str << _round_split_log_info.away_round_count;
}

void Match::export_team_skill_info(std::ostringstream& str) {
	str << _soccer_match->get_home_team()->get_team_skill_used_count();
	str << ":";
	str << _soccer_match->get_home_team()->get_skill_used_goal();
	str << "#";
	str << _soccer_match->get_away_team()->get_team_skill_used_count();
	str << ":";
	str << _soccer_match->get_away_team()->get_skill_used_goal();

}

int Match::export_match_statis_info(std::string& data_buffer) {
	std::ostringstream strbuff;
	export_all_skill_player_used(strbuff);
	strbuff << "|";
	export_all_team_cmp_info(strbuff);
	strbuff << "|";
	export_team_round_split(strbuff);
	strbuff << "|";
	export_team_skill_info(strbuff);
	data_buffer = strbuff.str();
}

void Match::calc_assist_or_goal_score(SoccerTeam *team, SoccerTeam* op_team,
		bool reverse) {
	SquadInfo& team_squad_info = *(_fixture_info->get_SquadInfo(
			team->get_team_cid()));
	SquadInfo& op_team_squad_info = *(_fixture_info->get_SquadInfo(
			op_team->get_team_cid()));

	vector<ActionItem>::reverse_iterator it;
	vector<ActionItem>::reverse_iterator it_end =
			team->get_action_list().rend();
	it = team->get_action_list().rbegin();
	if (it == it_end) {
		return;
	}

	//统计点球
	vector<ActionItem>::iterator itr_pently = team->get_action_list().begin();
	while (itr_pently != team->get_action_list().end()) {
		if (itr_pently->type == ActionItem::GOAL_PENALTY) {
			++team_squad_info.shoot_count;
			++team_squad_info.score_penalty;
		}
		itr_pently++;
	}

	/* 进球 或者 任意球 比分+1 */
	if (it->type == ActionItem::GOAL || it->type == ActionItem::GOAL_FREE) {
		team_squad_info.add_p_goal_count(it->union_pid);
		team_squad_info.add_p_shot_count(it->union_pid);
		++team_squad_info.shoot_count;
		++team_squad_info.score; // 球队得分
		op_team_squad_info.get_player_by_position(1).p_score -= 0.2; // 守门员得分
	}

	if (it->type == ActionItem::BEBREAK) {
		++op_team_squad_info.break_count;
		op_team_squad_info.add_p_steals_count(it->union_pid);
		//op_team_squad_info.add_p_score(it->union_pid);
	} else if (it->type == ActionItem::SHOOT_OUTSIDE) {
		++team_squad_info.ms_shoot_count;
		team_squad_info.add_p_no_shot_count(it->union_pid);
		op_team_squad_info.del_p_score(it->union_pid);
	} else if (it->type == ActionItem::SHOOT) {
		++team_squad_info.shoot_count;
		team_squad_info.add_p_shot_count(it->union_pid);
	}

	++it;
	if (it == it_end) {
		return;
	}

	if (team->get_action_list().rbegin()->type == ActionItem::GOAL) {
		if (it->type == ActionItem::PASS || it->type == ActionItem::CROSS) {
			if (it->type == ActionItem::PASS) {
				++team_squad_info.pass_count;
				team_squad_info.add_p_assist_count(it->union_pid);
			} else {
				++team_squad_info.cross_count;
			}
		}
	}
	++it;
	if (it == it_end) {
		return;
	}

	for (; it != it_end; ++it) {
		if (it->type == ActionItem::PASS) {
			++team_squad_info.pass_count;
		} else {
			++team_squad_info.cross_count;
		}
	}

	/* 一轮结束统计所有球员的得分 */
	SquadInfo* team_info = _fixture_info->get_SquadInfo(team->get_team_cid());
	for (int i = 0; i < team->get_players_on_pitch_count(); i++) {
		SoccerPlayer *player = NULL;
		player = team->get_player_on_pitch(i);
		if (player != NULL) {

			PlayerInfo* player_info = (team_info->get_player_by_pid(
					player->get_union_pid()));
			if (player_info != NULL) {
				player_info->p_score = player->get_player_score();
			}
		}
	}
	SoccerPlayer* player = team->get_gk_player();
	PlayerInfo* gk_player_info = team_info->get_player_by_pid(
			player->get_union_pid());
	if (gk_player_info != NULL) {
		gk_player_info->p_score = player->get_player_score();
	}

	//如果比赛结束了，没有被对方进球，则所有的后卫加分+1
	if (is_match_end()) {
		if (team_squad_info.score == 0) {
			//op_team_squad_info.get_player_by_pid.get_player_by_pid()
			std::vector<int> all_back_player;
			op_team->get_all_player_back(all_back_player);
			std::vector<int>::iterator itr = all_back_player.begin();
			while (itr != all_back_player.end()) {
				op_team_squad_info.add_p_score(*itr, 1);
				itr++;
			}
		}
	}

}

/* 做出电脑的NPC选择 */
void Match::make_ai_choose(SoccerTeam *team, SquadInfo *squad_info,
		SquadInfo *op_squad_info) {
	int is_win = 0;
	if (squad_info->score > op_squad_info->score) {
		is_win = 1;
	} else if (squad_info->score < op_squad_info->score) {
		is_win = -1;
	}

	//换人操作
	int tmp_time_scale = _time_scale * 90 / _total_time_scale;
	bool rst1 = false;
	bool rst2 = false;
	int change_count = team->get_auto_change_count();
	if (tmp_time_scale < 70 && tmp_time_scale > 60) {
		// 超过60分钟，考虑换人
		if (change_count == 0) {
			if (is_win == 1) { // 比分领先，从中场和后卫球员中选择(低于5分，若无则状态最低)的2人换下
				rst1 = this->change_team_back_one_player(team, squad_info);
				rst2 = this->change_team_middle_one_player(team, squad_info);
			} else if (is_win == -1) { // 比分落后的话
				rst1 = this->change_team_front_one_player(team, squad_info);
				rst2 = this->change_team_middle_one_player(team, squad_info);
			} else { // 平局的话
				rst1 = this->change_team_middle_one_player(team, squad_info);
			}
		} else if (change_count == 1) {
			if (is_win == 1) {
				rst1 = this->change_team_back_one_player(team, squad_info);
			} else if (is_win == -1) {
				rst1 = this->change_team_middle_one_player(team, squad_info);
			} else {
				rst1 = this->change_team_front_one_player(team, squad_info);
			}
		}
	} else if (tmp_time_scale >= 70 && tmp_time_scale < 90) {
		if (change_count == 1 || change_count == 2) {
			if (is_win == 1) { // 比分领先*/
				rst1 = this->change_team_back_one_player(team, squad_info);
			} else if (is_win == -1) {
				rst1 = this->change_team_front_one_player(team, squad_info);
			} else {
				rst1 = this->change_team_front_one_player(team, squad_info);
			}
		}
	}
	if (rst1 == true) {
		team->add_auto_change_count();
		team->update_att_mp(500);
		team->update_def_mp(500);
	}
	if (rst2 == true) {
		team->add_auto_change_count();
		team->update_att_mp(500);
		team->update_def_mp(500);
	}
}

void Match::change_player(SoccerTeam *team, SquadInfo *squad_info, int r_pos,
		int i_pos) {
}

bool Match::change_team_middle_one_player(SoccerTeam *team,
		SquadInfo *squad_info) {
	std::vector<int> players;
	//取得中场球员
	team->get_all_player_middle(players);
	int player_bereplaced = 0;
	if (players.size() > 0) {
		player_bereplaced = squad_info->get_score_lower_than_value_in_list(
				players, 5);
		//如果没有的话，就选择体力最低的。
		if (player_bereplaced == 0) {
			player_bereplaced = team->get_lowest_cond_player(players);
		}
		SoccerPlayer* player = team->get_player_on_pitch_by_union_id(
				player_bereplaced);
		if (player != NULL) {
			PlayerInfo* player_replaced =
					squad_info->get_def_max_player_in_back();
			if (player_replaced == NULL) {
				return false;
			}

			PlayerInfo* player_be_replaced = squad_info->get_player_by_pid(
					player_bereplaced);

			//如果上一轮是防守反击，正好换下的人是持球人的话,就设置换上的人为持球人
			if (_round_info.round_typ == N_STRIKE_BACK) {
				/*							if (team->get_team_cid() == _round_info.att_uid) {
				 if (_soccer_match->get_union_pid()
				 == player->get_union_pid()) {
				 _soccer_match->set_union_pid(pid);
				 }
				 }*/
				return true;
			}

			//已经在场上的，要把该玩家的状态设置为未在场上
			if (player_be_replaced == NULL) {
				LOG(ERROR) << "can't find player after change"
						<< player->get_union_pid();
			} else {
				player_be_replaced->is_on_pitch = false;
			}
			int player_pos = player->get_pos_index();
			load_player(player, *player_replaced);
			//player->set_Suitable(info->_next_op.pos.suitable[i]);
			player->set_pos_index(player_pos);
			player_be_replaced->is_on_pitch = false;
			return true;
		}
		return false;
	}

	return false;
}

bool Match::change_team_back_one_player(SoccerTeam *team, SquadInfo *squad_info) {
	std::vector<int> players;
	//取得后场球员
	team->get_all_player_back(players);
	int player_bereplaced = 0;
	//int change_index = 0;
	if (players.size() > 0) {
		player_bereplaced = squad_info->get_score_lower_than_value_in_list(
				players, 5);
		//如果没有的话，就选择体力最低的。
		if (player_bereplaced == 0) {
			player_bereplaced = team->get_lowest_cond_player(players);
		}

		SoccerPlayer* player = team->get_player_on_pitch_by_union_id(
				player_bereplaced);
		if (player != NULL) {
			PlayerInfo* player_replaced =
					squad_info->get_def_max_player_in_back();
			if (player_replaced == NULL) {
				return false;
			}

			PlayerInfo* player_be_replaced = squad_info->get_player_by_pid(
					player_bereplaced);

			//如果上一轮是防守反击，正好换下的人是持球人的话,就设置换上的人为持球人
			if (_round_info.round_typ == N_STRIKE_BACK) {
				/*							if (team->get_team_cid() == _round_info.att_uid) {
				 if (_soccer_match->get_union_pid()
				 == player->get_union_pid()) {
				 _soccer_match->set_union_pid(pid);
				 }
				 }*/
				return true;
			}

			//已经在场上的，要把该玩家的状态设置为未在场上
			if (player_be_replaced == NULL) {
				LOG(ERROR) << "can't find player after change"
						<< player->get_union_pid();
			} else {
				player_be_replaced->is_on_pitch = false;
			}
			int player_pos = player->get_pos_index();
			load_player(player, *player_replaced);
			//player->set_Suitable(info->_next_op.pos.suitable[i]);
			player->set_pos_index(player_pos);
			player_be_replaced->is_on_pitch = false;
			return true;
		}
		return false;
	}
	return false;
}

bool Match::change_team_front_one_player(SoccerTeam *team,
		SquadInfo *squad_info) {
	std::vector<int> players;
	//取得中场球员
	team->get_all_player_front(players);
	int player_bereplaced = 0;
	//int change_index = 0;
	if (players.size() > 0) {
		player_bereplaced = squad_info->get_score_lower_than_value_in_list(
				players, 5);
		//如果没有的话，就选择体力最低的。
		if (player_bereplaced == 0) {
			player_bereplaced = team->get_lowest_cond_player(players);
		}
		SoccerPlayer* player = team->get_player_on_pitch_by_union_id(
				player_bereplaced);
		if (player != NULL) {
			PlayerInfo* player_replaced =
					squad_info->get_attack_max_player_in_back();
			PlayerInfo* player_be_replaced = squad_info->get_player_by_pid(
					player_bereplaced);
			if (player_replaced == NULL) {
				return false;
			}

			//如果上一轮是防守反击，正好换下的人是持球人的话,就设置换上的人为持球人
			if (_round_info.round_typ == N_STRIKE_BACK) {
				/*							if (team->get_team_cid() == _round_info.att_uid) {
				 if (_soccer_match->get_union_pid()
				 == player->get_union_pid()) {
				 _soccer_match->set_union_pid(pid);
				 }
				 }*/
				return true;
			}

			//已经在场上的，要把该玩家的状态设置为未在场上
			if (player_be_replaced == NULL) {
				LOG(ERROR) << "can't find player after change"
						<< player->get_union_pid();
			} else {
				player_be_replaced->is_on_pitch = false;
			}
			int player_pos = player->get_pos_index();
			load_player(player, *player_replaced);
			//player->set_Suitable(info->_next_op.pos.suitable[i]);
			player->set_pos_index(player_pos);
			player_be_replaced->is_on_pitch = false;
			return true;
		}
		return false;
	}
	return false;
}

void Match::npc_choose_move_card(SoccerTeam *team, SquadInfo *squad_info,
		SquadInfo *op_squad_info) {
	return;
	int match_typ = this->_match_typ;
	if (true || match_typ == 3) { //如果是阶梯赛的话
		int rating_lev = squad_info->club_level;
		int tier_lev = config_tier_rating[rating_lev];
		MoveDefine* define = NULL;
		if (tier_lev == 1 || tier_lev == 2) {
			define = pickup_random_move_by_quality(1,
					team->get_current_formation_card_id());
		} else if (tier_lev == 3 || tier_lev == 4) {
			int quality = 1 + RAND_INT % 2;
			define = pickup_random_move_by_quality(quality,
					team->get_current_formation_card_id());
		} else if (tier_lev == 5 || tier_lev == 6) {
			int quality = 1 + RAND_INT % 3;
			define = pickup_random_move_by_quality(quality,
					team->get_current_formation_card_id());
		} else if (tier_lev == 7 || tier_lev == 8) {
			int quality = 1 + RAND_INT % 4;
			define = pickup_random_move_by_quality(quality,
					team->get_current_formation_card_id());
		} else if (tier_lev == 9 || tier_lev == 10) {
			int quality = 1 + RAND_INT % 5;
			define = pickup_random_move_by_quality(quality,
					team->get_current_formation_card_id());
		}

		if (define == NULL) {
			return;
		}
		squad_info->_next_op._next_move_card_id = define->get_move_id();
	}
}

void Match::npc_choose_action_card(SoccerTeam *team, SquadInfo *squad_info,
		SquadInfo *op_squad_info) {
	return;
	int rating_lev = squad_info->club_level;
	std::vector<PlayerInfo*> playerInfo;
	squad_info->get_player_withOUt_buff_next_round(playerInfo);
	if (playerInfo.size() < 1) {
		return;
	}

	int highest_player = squad_info->get_highest_player_from_list(playerInfo);
	ActionDefine *define = NULL;
	int match_typ = this->_match_typ;
	if (true || match_typ == 3) { //如果是阶梯赛得话
		int tier_lev = config_tier_rating[rating_lev];
		int index = 0;
		index = (int) (tier_lev / 2) + 1;
		define = pickup_random_action_by_quality(index);
	}

	if (define != NULL) {
		squad_info->_next_op._round_index = this->_round_id + 1;
		squad_info->_next_op._next_action_card_id = define->card_id;
		squad_info->_next_op._next_action_player_id = highest_player;
	}
}

void Match::npc_choose_event_card(SoccerTeam *team, SquadInfo *squad_info,
		SquadInfo *op_squad_info) {
	int rating_lev = squad_info->club_level;
	EventDefine* define = NULL;

	int tier_lev = config_tier_rating[rating_lev];
	int quality = (int) (tier_lev / 2) + 1;
	define = pickup_random_event_by_quality(quality);
	if (define != NULL) {
		squad_info->_next_op._next_event_id = define->card_id;
	}
}

//TODO 修改检查round为检查time_scale是否到点
bool Match::is_match_end() {
	if (is_quick_terminal() == true) {
		return true;
	}
	if (this->_time_scale >= _total_time_scale) {
		return true;
	}
	return false;
}

bool Match::is_quick_terminal() {
	return _quick_terminal;
}

void Match::set_quick_terminal(bool value) {
	this->_quick_terminal = value;
}

/*

 void Match::gen_team_possession(bool reverse, RoundDetail *pRoundDetail,
 MoveOperatorResultEvent &more) {
 if (reverse) {
 if (pRoundDetail->index == 0) {
 _fixture_info->u2.possession = 52;
 _fixture_info->u1.possession = 48;
 } else {
 int
 op2_sub =
 _fixture_info->card_formation[more.op2.card_id].sub_card_typ;
 int
 op1_sub =
 _fixture_info->card_formation[more.op1.card_id].sub_card_typ;
 double att_op2 = _soccer_match->get_team(1)->calc_team_att_value(
 op2_sub);
 double def_op1 = _soccer_match->get_defend_team()->calc_team_def_value(
 op1_sub);

 double tmp = 100 * att_op2 / (att_op2 + def_op1);
 VLOG(3)<< "----------------tmp1:" << tmp << "att_op2:" <<att_op2 << "def_op1:" << def_op1;
 _fixture_info->u2.possession = (_fixture_info->u2.possession * pRoundDetail->index + tmp) / (pRoundDetail->index + 1);
 _fixture_info->u1.possession = 100 - _fixture_info->u2.possession;
 }
 }
 else
 {
 if (pRoundDetail->index == 0)
 {
 _fixture_info->u1.possession = 52;
 _fixture_info->u2.possession = 48;
 }
 else
 {
 int op2_sub = _fixture_info->card_formation[more.op2.card_id].sub_card_typ;
 int op1_sub = _fixture_info->card_formation[more.op1.card_id].sub_card_typ;
 double att_op1 = _soccer_match->get_team(1)->calc_team_att_value(op1_sub);
 double def_op2 = _soccer_match->get_get_defend_team()->calc_team_def_value(op2_sub);
 double tmp = 100 * att_op1 / (att_op1 + def_op2);
 VLOG(3) << "----------------tmp2:" << tmp << "att_op1:" << att_op1 << "def_op2:" << def_op2;
 _fixture_info->u1.possession = (_fixture_info->u1.possession * pRoundDetail->index + tmp) / (pRoundDetail->index + 1);
 _fixture_info->u2.possession = 100 - _fixture_info->u1.possession;
 }
 }
 }

 void Match::map_team_club_info(bool reverse, RoundDetail *pRoundDetail,
 MoveOperatorResultEvent &more, int &rst_attack_uid) {
 if (reverse) {
 rst_attack_uid = _fixture_info->u2.uid;
 this->_soccer_match->get_attack_team()->set_team_cid(rst_attack_uid);
 this->_soccer_match->get_defend_team()->set_team_cid(_fixture_info->u1.uid);

 VLOG(3)<< rst_attack_uid << "," << _fixture_info->u2.score <<"," << _fixture_info->u1.score;

 this->_soccer_match->get_get_defend_team()->set_newbie_state(_fixture_info->newbie_stat);
 this->_soccer_match->get_attack_team()->set_newbie_state(0);
 }
 else
 {
 rst_attack_uid = _fixture_info->u1.uid;
 this->_soccer_match->get_attack_team()->set_team_cid(rst_attack_uid);
 this->_soccer_match->get_get_defend_team())->set_team_cid(_fixture_info->u2.uid);

 //    	VLOG(3) << rst_attack_uid << "," << _fixture_info->u1.score << "," << _fixture_info->u2.score;

 this->_soccer_match->get_attack_team()->set_newbie_state(_fixture_info->newbie_stat);
 this->_soccer_match->get_get_defend_team()->set_newbie_state(0);
 }

 this->_soccer_match->get_attack_team()->set_team_score(_fixture_info->u2.score + _fixture_info->u1.score);
 this->_soccer_match->get_get_defend_team()->set_team_score(_fixture_info->u2.score + _fixture_info->u1.score);

 this->_soccer_match->get_attack_team()->set_is_round_add(pRoundDetail->is_round_add);
 this->_soccer_match->get_get_defend_team()->set_is_round_add(pRoundDetail->is_round_add);
 }
 */

void Match::full_back_team_energy(SoccerTeam* team, int time_scale) {
	if (time_scale <= 0)
		return;
	int back = time_scale * (1 + 0.06 * (double) team->get_team_level())
			* (2000. / (double) (this->_total_time_scale));
	team->update_att_mp(back);
	team->update_def_mp(back);
}

int Match::match_continue_move(MatchRecorder *recorder, int &run_time_scale) {
	RoundDetail& roundDetail = get_current_round_info();
	if (roundDetail.att_uid != _fixture_info->u1.uid) {
		_soccer_match->set_attack_and_defend_team(
				_soccer_match->get_away_team(), _soccer_match->get_home_team());
	} else {
		_soccer_match->set_attack_and_defend_team(
				_soccer_match->get_home_team(), _soccer_match->get_away_team());
	}

	_soccer_match->get_attack_team()->get_action_list().clear();
	_soccer_match->get_defend_team()->get_action_list().clear();
	_soccer_match->reset_timer();

	int end_type;
	run_time_scale = do_match_loop(*recorder, end_type);

	/* 比赛中的事件 */
	std::vector<MatchEvent>::iterator it =
			_soccer_match->get_event_frames()->begin();
	while (it != _soccer_match->get_event_frames()->end()) {
		recorder->set_event_frames(it->timescale, it->cid, it->type, it->pid,
				it->op_pid);
		it++;
	}
	_soccer_match->get_event_frames()->clear();

	//比赛中的技能使用
	for (std::vector<MatchSkillEvent>::iterator it =
			_soccer_match->get_skill_frames()->begin(); it
			!= _soccer_match->get_skill_frames()->end(); ++it) {
		recorder->add_skill_frames(it->timescale, it->skill_id, it->pid);
	}
	_soccer_match->get_skill_frames()->clear();

	//比赛中的点球
	recorder->set_pently_event(_soccer_match->get_pently_frames());
	_soccer_match->get_pently_frames()->clear();

	calc_assist_or_goal_score(_soccer_match->get_home_team(),
			_soccer_match->get_away_team(), recorder->get_reverse());
	calc_assist_or_goal_score(_soccer_match->get_away_team(),
			_soccer_match->get_home_team(), recorder->get_reverse());

	return 1;
}

int Match::do_match_loop(MatchRecorder &recorder, int& end_typ) {
	int i = 0;
	MatchEndStatus* endStatus = NULL;
	int show_fail_goal = 0;
	int goal_show_time_scale = 0;

	int round_limit_count = 200;
	while (1) {
		endStatus = _soccer_match->update_match();
		recorder.update();
		if ((i >= round_limit_count)) {// && (endStatus->_current_end_status != END_GOAL)
			if (endStatus->_current_end_status == 0) {
				endStatus->_current_end_sub_typ = OVERTIME;
				endStatus->_current_end_status = END_NORMAL_END;
				endStatus->_next_round_typ = N_NORMAL_KICK;
				endStatus->_injured = 0;
			}
			break;
		}
		//整个比赛的时间片
		i++;
		//半场时间
		this->_time_scale++;
		if (this->_time_scale >= _total_time_scale) {//整个比赛的时间到了。
			endStatus->_current_end_sub_typ = OVERTIME;
			endStatus->_current_end_status = END_NORMAL_END;
			endStatus->_next_round_typ = N_NORMAL_KICK;
			endStatus->_injured = 0;
			break;
		}
		if (this->_time_scale == _total_time_scale / 2) {
			endStatus->_current_end_sub_typ = FIRST_HALF_END;
			endStatus->_current_end_status = END_HALF_TIME;
			endStatus->_next_round_typ = N_NORMAL_KICK;
			endStatus->_injured = 0;
			break;
		}

		//增加球的运行路线END_GOAL_FAIL,		//射门没有进
		if (endStatus->_current_end_status >= END_GOAL
				&& endStatus->_current_end_status <= END_NORMAL_END) {
			if (endStatus->_current_end_status == END_GOAL) {
				if ((i + goal_show_time_scale) > round_limit_count) {
					round_limit_count = i + goal_show_time_scale + 1;
				}

				if ((_time_scale + goal_show_time_scale) > _total_time_scale) {
					_total_time_scale = _time_scale + goal_show_time_scale + 1;
				}

				if (goal_show_time_scale > 15) {
					break;
				} else {
					goal_show_time_scale++;
				}
			} else {
				if (N_STRIKE_BACK == endStatus->_current_end_status) {
					//				break;
				} else if (endStatus->_current_end_status == END_FOULED) {
					break;
				}

				if (show_fail_goal < 10) {
					show_fail_goal++;
					if (i >= 200) {
						break;
					}
				} else {
					break;
				}
			}
		}
	}

	endStatus->_total_time_scale += i;
	if (endStatus->_current_end_sub_typ != OVERTIME || (this->_time_scale
			> _total_time_scale)) {
		_soccer_match->get_attack_team()->clear_move_def_define();
	}

	end_typ = endStatus->_current_end_status;
	if (end_typ == END_GOAL) {
		if (_round_info.att_team_skill_id != 0) {
			LOG(INFO) << "使用技能进球le .....";
			_soccer_match->get_attack_team()->add_use_skill_goal();
		}
	}
	full_back_team_energy(_soccer_match->get_home_team(), i);
	full_back_team_energy(_soccer_match->get_away_team(), i);

	//减低球员的体力
	player_attribute_update(i);

	//如果比赛结束,比赛是杯赛,必须有胜负,如果平局的话就开始点球
	if ((is_match_end() == true) && (this->need_pently_shoot())) {
		if (((_soccer_match->get_home_team()->get_team_scroe())
				== (_soccer_match->get_away_team()->get_team_scroe()))) {
			int home_score = 0;
			int away_score = 0;
			if (_soccer_match->get_attack_team()->is_team_all_attack()
					|| _soccer_match->get_defend_team()->is_team_all_attack()) {
				_soccer_match->general_all_attack_pently();
			} else {
				_soccer_match->calc_pently_match(home_score, away_score);
			}
		}
	}
	return i;
}

void Match::set_team_info(FixtureInfo* info) {
	SoccerTeam* team1 = this->_soccer_match->get_team_by_cid(info->u1.uid);
	team1->set_current_formation_card_id(info->u1._next_op._next_formation_id);

	SoccerTeam* team2 = this->_soccer_match->get_team_by_cid(info->u2.uid);
	team2->set_current_formation_card_id(info->u2._next_op._next_formation_id);
}

void Match::set_team_skill_info(MsgMatchTeamInfo& msg) {
	int cid = msg.op1.uid;
	SoccerTeam* team = this->get_move()->get_team_by_cid(cid);
	for (int count = 0; count < msg.op1.team_skill_count; ++count) {
		team->add_team_skill(msg.op1.team_skills[count].tactic_id,
				msg.op1.team_skills[count].chance);
	}

	cid = msg.op2.uid;
	team = this->get_move()->get_team_by_cid(cid);
	for (int count = 0; count < msg.op2.team_skill_count; ++count) {
		team->add_team_skill(msg.op2.team_skills[count].tactic_id,
				msg.op2.team_skills[count].chance);
	}
}

bool Match::player_team_use_skill(int team_id, int skill_id,
		int& final_success, int& temp_success) {
	VLOG(0)<<"Team "<<team_id<<" use skill "<<skill_id;
	TacticInfo * info = CGameConfigManager::GetInstance()->GetTacticInfoById(skill_id);
	bool rst = false;
	if(info != NULL){
		SoccerTeam* team = _soccer_match->get_team_by_cid(team_id);
		SoccerTeam* op_team = NULL;
		if(_soccer_match->get_team(1)->get_team_cid() == team->get_team_cid()){
			op_team = _soccer_match->get_team(2);
		}else{
			op_team = _soccer_match->get_team(1);
		}

		TeamSkill* skill_info = team->get_team_skill_info(skill_id);
		if(skill_info == NULL){
			return false;
		}
		bool is_same = false;
		if(skill_id == team->get_last_skill_use_list()){
			is_same = true;
		}

		double modifer = team->get_team_skill_success_rate(skill_id,op_team->get_coach_speak_type());
		temp_success = skill_info->chance + 10000.* team->get_alias_tactic_plus();
		final_success = (skill_info->chance+ 10000.* team->get_alias_tactic_plus()) * modifer;
		LOG(INFO)<<skill_info->chance<<":"<<team->get_alias_tactic_plus()<<":"<<modifer;
		if(is_same){
			final_success = final_success/2.;
		}
		rst = team->use_team_skill(info);
	}
	return rst;
}

void Match::load_player(SoccerPlayer* player, PlayerInfo& player_info) {
	//设置
	//是否上过场
	player_info.has_been_to_pitch = true;
	player_info.is_on_pitch = true;
	std::map<int, std::string>::iterator it;
	for (it = g_player_attr_field_map.begin(); it
			!= g_player_attr_field_map.end(); ++it) {
		player->set_attr(it->first, player_info.attr[(it->first) - 1]);
		player->set_attr_bak(it->first, player_info.attr[(it->first) - 1]);
	}
	SoccerPlayerSkill *skill = player->get_skills();
	int skill_count = 0;
	for (; skill_count < player_info.skill_count; skill_count++) {
		if (skill_count >= 10) {
			LOG(ERROR) << "PLAYER ERORR" << player_info.pid;
		}
		skill->add_skill(player_info.skills[skill_count].skill_id,
				player_info.skills[skill_count].skill_level,
				player_info.skills[skill_count].skill_chance);
	}
	player->set_cond(player_info.cond);
	player->set_per_time_scale_cond_dis(player_info.per_cond_dis);
	player->setAtt_value(player_info.att_value);
	player->setDef_value(player_info.def_value);
	player->set_player_name(player_info.player_name);
	player->set_union_pid(player_info.pid); // 球员PID
	player->set_uid(_fixture_info->u1.uid); // team id
	player->set_pos_index(player_info.pos_index);
}

void Match::set_new_formation(int cid, int formation_pos[], int suite_able[]) {
	SquadInfo *info = get_fixture_info()->get_SquadInfo(cid);
	memcpy(info->_next_op.pos.pid, formation_pos, 16 * sizeof(int));
	memcpy(info->_next_op.pos.suitable, suite_able, 16 * sizeof(int));
	info->_next_op.is_change_player = true;
}

//换人。。。
bool Match::change_player_use_pid(int cid) {
	//this->get//_player_on_pitch()
	SoccerTeam* team = this->get_move()->get_team_by_cid(cid);
	if (team == NULL) {
		return false;
	}

	SquadInfo *info = _fixture_info->get_SquadInfo(cid);
	if (info->_next_op.is_change_player == false) {
		return false;
	}
	//一共换人的次数
	int change_count = 0;
	for (int i = 0; i < 11; i++) {
		int pid = info->_next_op.pos.pid[i];
		SoccerPlayer* player = team->get_player_by_pos_index(i + 1);
		if ((player != NULL) && (player->get_union_pid() != pid)) {
			//如果上一轮是防守反击，正好换下的人是持球人的话,就设置换上的人为持球人
			if (_round_info.round_typ == N_STRIKE_BACK) {
				if (team->get_team_cid() == _round_info.att_uid) {
					if (_soccer_match->get_union_pid()
							== player->get_union_pid()) {
						_soccer_match->set_union_pid(pid);
					}
				}
			}

			//已经在场上的，要把该玩家的状态设置为未在场上
			PlayerInfo* player_be_replaced = info->get_player_by_pid(
					player->get_union_pid());
			if (player_be_replaced == NULL) {
				LOG(ERROR) << "can't find player after change"
						<< player->get_union_pid();
			}

			PlayerInfo* player_info = info->get_player_by_pid(pid);
			if (player_info->is_on_pitch == false) {
				change_count++;
				VLOG(0)<<".........................."<<pid;
			}
			load_player(player, *player_info);
			player->set_Suitable(info->_next_op.pos.suitable[i]);
			player->set_pos_index(i + 1);
		}
	}
	if(change_count == 1) {
		team->add_auto_change_count();
	} else if(change_count == 2) {
		team->add_auto_change_count();
		team->add_auto_change_count();
	} else if(change_count == 3) {
		team->add_auto_change_count();
		team->add_auto_change_count();
		team->add_auto_change_count();
	}

	//根据换人的次数提升能力条
	if(change_count > 0) {
		team->update_att_mp(500 * change_count);
		team->update_def_mp(500 * change_count);
	}

	//重置所有的在场上的问题
	for(int i=0;i<16;i++) {
		int pid = info->_next_op.pos.pid[i];
		PlayerInfo* player_info = info->get_player_by_pid(pid);
		if(i < 11) {
			if(player_info != NULL) {
				player_info->is_on_pitch = true;
			}
		} else {
			if( player_info != NULL) {
				player_info->is_on_pitch = false;
			}
		}
	}

	info->_next_op.is_change_player = false;
	return true;

	/*


	 SoccerPlayer* rst_player = team->get_player_on_pitch_by_union_id(rst_player_id);
	 if(rst_player == NULL){
	 if(team->get_gk_player()->get_union_pid() == rst_player_id){
	 rst_player = team->get_gk_player();
	 }
	 }

	 if(rst_player == NULL){
	 VLOG(3)<<"PID为"<<rst_player_id<<" 不在场上!!";
	 return false;
	 }

	 SoccerPlayer* src_player = team->get_player_by_pos_index(src_player_pos_index);
	 if(src_player != NULL)//替换的球员在场上,交换formation_pos，就好了
	 {
	 int	src_player_formation =src_player->get_formation_pos();
	 src_player->set_formation_pos(rst_player->get_formation_pos());
	 rst_player->set_formation_pos(src_player_formation);

	 int src_player_pos_index = src_player->get_pos_index();
	 src_player->set_pos_index(rst_player->get_pos_index());
	 rst_player->set_pos_index(src_player_pos_index);
	 rst_player->set_Suitable(i_suitable);
	 src_player->set_Suitable(r_suitable);
	 }else{
	 PlayerInfo *player_info = _fixture_info->get_SquadInfo(cid)->get_player_by_pid(src_player_pos_index);
	 if(player_info == NULL){
	 return false;
	 }
	 load_player(rst_player,(PlayerInfo&)*player_info);
	 rst_player->set_Suitable(r_suitable);
	 }

	 return false;*/
}

void Match::check_team_op_before_move() {
	SoccerTeam* att_team = this->_soccer_match->get_team(1);
	SoccerTeam* def_team = this->_soccer_match->get_team(2);
	if (att_team != NULL) {
		if (att_team->get_team_cid() > 0) {
			SquadInfo *info = _fixture_info->get_SquadInfo(
					att_team->get_team_cid());
			if (info->_next_op.is_change_player == true) {
				change_player_use_pid(att_team->get_team_cid());
			} else if (att_team->is_change_player_deposit()) {
				make_ai_choose(att_team, _fixture_info->get_SquadInfo(
						att_team->get_team_cid()),
						_fixture_info->get_SquadInfo(def_team->get_team_cid()));
			}
		} else {
			make_ai_choose(att_team, _fixture_info->get_SquadInfo(
					att_team->get_team_cid()), _fixture_info->get_SquadInfo(
					def_team->get_team_cid()));
		}
	}

	if (def_team != NULL) {
		if (def_team->get_team_cid() > 0) {
			SquadInfo *info = _fixture_info->get_SquadInfo(
					def_team->get_team_cid());
			if (info->_next_op.is_change_player == true) {
				change_player_use_pid(def_team->get_team_cid());
			} else if (def_team->is_change_player_deposit()) {
				make_ai_choose(def_team, _fixture_info->get_SquadInfo(
						def_team->get_team_cid()),
						_fixture_info->get_SquadInfo(att_team->get_team_cid()));
			} else {
				change_player_use_pid(def_team->get_team_cid());
			}
		} else {
			make_ai_choose(def_team, _fixture_info->get_SquadInfo(
					def_team->get_team_cid()), _fixture_info->get_SquadInfo(
					att_team->get_team_cid()));
		}
	}

}

void Match::judge_attack_defend(MatchEndStatus* end_status) {
	//如果是开场球的话
	int current_att = _round_info.att_uid;
	int current_def = _round_info.def_uid;
	if (this->get_time_scale() == 1) {
		if (_fixture_info->u1.is_all_attack) {
			_round_info.set_RoundDetail(_fixture_info->u1.uid,
					_fixture_info->u2.uid, 0, MIDDLE_KICK_OFF, 0, 0, 1);
			return;
		} else {
			_fixture_info->get_next_round_kick_off_att_team(current_att,
					current_def);
			_round_info.set_RoundDetail(current_att, current_def, 0,
					MIDDLE_KICK_OFF, 0, 0, 1);
			return;
		}
	}

	//判断是否有球员爆棚
	if (_fixture_info->u1.is_all_attack) {
		_round_info.set_RoundDetail(_fixture_info->u1.uid,
				_fixture_info->u2.uid, 0, NORMAL_KICK, 0, 0,
				_round_info.start_time_scale);
		return;
	}

	switch (end_status->_next_round_typ) {
	/*		case N_MIDDLE_KICK: // 进球
	 {
	 _round_info.set_RoundDetail(current_def // 主场ID
	 , current_att // 客场ID
	 , 0 // 配置文件中配置的本回合类型
	 , GOAL_KICK_OFF // 程序中定义的本回合类型
	 , 0 // 减少体力的时间间隔
	 , 0 // 球员ID
	 , _round_info.start_time_scale // 开始时间
	 );
	 }
	 break;*/
	case N_CORNER_KICK: // 角球上
	{
		_round_info.set_RoundDetail(current_att // 主场ID
				, current_def // 客场ID
				, 0 // 配置文件中配置的本回合类型
				, CORNER_KICK_UP_OFF// 程序中定义的本回合类型
				, 0 // 减少体力的时间间隔
				, 0 // 球员ID
				, _round_info.start_time_scale // 开始时间
		);
		_fixture_info->dis_squad_kick_off_count(current_att);
	}
		break;
	case N_FREE_KICK: // 任意球
	{
		_round_info.set_RoundDetail(current_def// 主场ID
				, current_att // 客场ID
				, 0 // 配置文件中配置的本回合类型
				, FREE_KICK_OFF // 程序中定义的本回合类型
				, 0 // 减少体力的时间间隔
				, 0 // 球员ID
				, _round_info.start_time_scale // 开始时间
		);
		_fixture_info->dis_squad_kick_off_count(current_def);
	}
		break;
	case N_PENALTY_KICK: // 点球
	{
		_round_info.set_RoundDetail(current_att // 主场ID
				, current_def // 客场ID
				, 0 // 配置文件中配置的本回合类型
				, PENALTY_KICK_OFF // 程序中定义的本回合类型
				, 0 // 减少体力的时间间隔
				, 0 // 球员ID
				, _round_info.start_time_scale // 开始时间
		);
		_fixture_info->dis_squad_kick_off_count(current_att);

	}
		break;
	case N_NORMAL_KICK://普通开球
	case N_MIDDLE_KICK: // 进球
	{
		if (_fixture_info->u1.uid > 0) {//如果是玩家，並且使用了技能，優先給round
			int skill_id = this->get_move()->get_team_by_cid(
					_fixture_info->u1.uid)->get_skill_used();
			if (skill_id > 0) {
				if (_fixture_info->get_squad_kick_off_count(
						_fixture_info->u1.uid) > 0) {
					_round_info.set_RoundDetail(_fixture_info->u1.uid // 主场ID
							, _fixture_info->u2.uid // 客场ID
							, 0 // 配置文件中配置的本回合类型
							, NORMAL_KICK // 程序中定义的本回合类型
							, 0 // 减少体力的时间间隔
							, 0 // 球员ID
							, _round_info.start_time_scale// 开始时间
					);
					_fixture_info->dis_squad_kick_off_count(
							_fixture_info->u1.uid);
					LOG(INFO) << "GET ROUND BY USE SKILL";
					break;
				}
			}
		}

		if (_fixture_info->u2.uid > 0) {
			int skill_id = this->get_move()->get_team_by_cid(
					_fixture_info->u2.uid)->get_skill_used();
			if (skill_id > 0) {
				if (_fixture_info->get_squad_kick_off_count(
						_fixture_info->u2.uid) > 0) {
					_round_info.set_RoundDetail(_fixture_info->u2.uid // 主场ID
							, _fixture_info->u1.uid // 客场ID
							, 0 // 配置文件中配置的本回合类型
							, NORMAL_KICK // 程序中定义的本回合类型
							, 0 // 减少体力的时间间隔
							, 0 // 球员ID
							, _round_info.start_time_scale// 开始时间
					);
					_fixture_info->dis_squad_kick_off_count(
							_fixture_info->u2.uid);
					break;
				}
			}

		}

		_fixture_info->get_next_round_kick_off_att_team(current_att,
				current_def);

		_round_info.set_RoundDetail(current_att // 主场ID
				, current_def // 客场ID
				, 0 // 配置文件中配置的本回合类型
				, NORMAL_KICK // 程序中定义的本回合类型
				, 0 // 减少体力的时间间隔
				, 0 // 球员ID
				, _round_info.start_time_scale// 开始时间
		);

	}
		break;
	case N_STRIKE_BACK: {
		if (_fixture_info->get_squad_kick_off_count(current_def) > 0) {
			_fixture_info->dis_squad_kick_off_count(current_def);
			_round_info.set_RoundDetail(current_def// 主场ID
					, current_att// 客场ID
					, 0 // 配置文件中配置的本回合类型
					, DEFEND_AND_ATTCK // 程序中定义的本回合类型
					, 0 // 减少体力的时间间隔
					, 0 // 球员ID
					, _round_info.start_time_scale // 开始时间
			);
			break;
		}

		if (_fixture_info->get_squad_kick_off_count(current_att) > 0) {
			_round_info.set_RoundDetail(current_att// 主场ID
					, current_def// 客场ID
					, 0 // 配置文件中配置的本回合类型
					, NORMAL_KICK // 程序中定义的本回合类型
					, 0 // 减少体力的时间间隔
					, 0 // 球员ID
					, _round_info.start_time_scale // 开始时间
			);
			_fixture_info->dis_squad_kick_off_count(current_att);
			break;
		}
		_fixture_info->get_next_round_kick_off_att_team(current_att,
				current_def);
		_round_info.set_RoundDetail(current_att // 主场ID
				, current_def // 客场ID
				, 0 // 配置文件中配置的本回合类型
				, NORMAL_KICK // 程序中定义的本回合类型
				, 0 // 减少体力的时间间隔
				, 0 // 球员ID
				, _round_info.start_time_scale// 开始时间
		);
	}
		break;
		default:
		{
			_fixture_info->get_next_round_kick_off_att_team(current_att,
					current_def);
			_round_info.set_RoundDetail(current_att // 主场ID
					, current_def // 客场ID
					, 0 // 配置文件中配置的本回合类型
					, NORMAL_KICK // 程序中定义的本回合类型
					, 0 // 减少体力的时间间隔
					, 0 // 球员ID
					, _round_info.start_time_scale// 开始时间
			);
		}
		break;
	}

	}

	void Match::player_attribute_update(int time_scale_passed) {
		SoccerMatch* match = this->get_move();
		SoccerTeam* team = match->get_attack_team();
		SquadInfo* squad_info = _fixture_info->get_SquadInfo(
				team->get_team_cid());
		for (int count = 0; count < team->get_players_on_pitch_count(); count++) {
			SoccerPlayer* player = team->get_player_on_pitch(count);
			player->down_player_cond(time_scale_passed);
			squad_info->get_player_by_pid(player->get_union_pid())->cond
					= player->get_cond();
		}

		team = match->get_defend_team();
		squad_info = _fixture_info->get_SquadInfo(team->get_team_cid());
		for (int count = 0; count < team->get_players_on_pitch_count(); count++) {
			SoccerPlayer* player = team->get_player_on_pitch(count);
			player->down_player_cond(time_scale_passed);
			squad_info->get_player_by_pid(player->get_union_pid())->cond
					= player->get_cond();
		}
	}

	//match_typ //1:豪门之路，2：W，3：实况杯，4：周赛，5：友谊赛，6：球场挑NPC，7：球场挑玩家，8：盟战
	int Match::check_team_skill_use(SoccerTeam* attack_team, int match_typ) {
		int skill_id = 0;
		//如果开球是角球，不要发起球队技能
		if (_round_info.typ == CORNER_KICK_UP_OFF) {
			attack_team->reset_skill_used();
			return skill_id;
		}

		if (match_typ == 1 || match_typ == 3 || match_typ == 4 || match_typ
				== 6 || match_typ == 9) {
			if (attack_team->get_team_cid() < 0) {
				skill_id = attack_team->team_ai_auto_use_skill();
				attack_team->reset_skill_used();
			} else {
				if (attack_team->is_use_skill_deposit()) {
					skill_id = attack_team->team_ai_auto_use_skill();
					attack_team->reset_skill_used();
				} else {
					skill_id = attack_team->get_skill_used();
					attack_team->reset_skill_used();
				}
			}
		} else if (match_typ == 2 || match_typ == 5 || match_typ == 8) {
			if (attack_team->get_team_cid()
					!= this->get_move()->get_home_team()->get_team_cid()) {
				skill_id = attack_team->team_ai_auto_use_skill();
				attack_team->reset_skill_used();
			} else {
				if (attack_team->is_use_skill_deposit()) {
					skill_id = attack_team->team_ai_auto_use_skill();
					attack_team->reset_skill_used();
				} else {
					skill_id = attack_team->get_skill_used();
					attack_team->reset_skill_used();
				}
			}
		} else if (match_typ == 7) {
			if (attack_team->get_team_cid()
					== this->get_move()->get_home_team()->get_team_cid()) {
				skill_id = attack_team->team_ai_auto_use_skill();
				attack_team->reset_skill_used();
			} else {
				if (attack_team->is_use_skill_deposit()) {
					skill_id = attack_team->team_ai_auto_use_skill();
					attack_team->reset_skill_used();
				} else {
					skill_id = attack_team->get_skill_used();
					attack_team->reset_skill_used();
				}
			}
		}
		return skill_id;
	}
