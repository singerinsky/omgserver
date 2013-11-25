#include "../common/head.h"

#include "soccer_team.h"
#include "soccer_player_state.h"
#include "soccer_team_state.h"
#include "entity_manager.h"
#include "soccer_match.h"
#include "soccer_pitch.h"

bool cmp_shooter_sort(SoccerPlayer* player_rst,SoccerPlayer* player_src){
	double attr_rst = player_rst->get_attr(PENALTY) * 3 + player_rst->get_attr(ATT_SHOOT) * 7;
	double attr_src = player_src->get_attr(PENALTY) * 3 + player_src->get_attr(ATT_SHOOT) * 7;
	return attr_rst > attr_src;
}

SoccerTeam::SoccerTeam(int id, SoccerMatch *match) :
	GameEntityBase<SoccerTeam> (id) {
	_match = match;

	_match->enregister(this);

	_players_on_pitch.reserve(PLAYER_COUNT);

	for (int i = 0; i < PLAYER_COUNT; ++i) {
		int player_id = (id == HOME_TEAM_ID) ? i + 1 : i + 12;
		SoccerPlayer *player = new SoccerPlayer(player_id, get_id() + i + 1,
				this);
		player->set_global_state(GlobalPlayerState::alloc());
		_players_on_pitch.push_back(player);
		_match->enregister(player);
	}

	//init gk player
	if (id == HOME_TEAM_ID) {
		this->_gk_player = new SoccerPlayer(0, get_id() + 11, this);
		this->_gk_player->set_state(StopState::alloc());
		this->_gk_player->set_global_state(GlobalPlayerState::alloc());
		_match->enregister(_gk_player);
	} else {
		this->_gk_player = new SoccerPlayer(11, get_id() + 11, this);
		this->_gk_player->set_state(StopState::alloc());
		this->_gk_player->set_global_state(GlobalPlayerState::alloc());
		_match->enregister(_gk_player);
	}
	_closest_player = NULL;
	_supporting_player = NULL;
	_receiving_player = NULL;

	_marking_player = NULL;
	_minding_player = NULL;
	_breaking_player = NULL;
	_air_defend_player = NULL;
	_has_offside = false;
	_use_skill_goal = 0;

	_action_list.reserve(20);

	player_mark_flag = new int[10];
	for (int i = 0; i < 10; ++i) {
		player_mark_flag[i] = 0;
		this->_line_number[i] = 0;
	}

	goal_attr.clear();

	_kick_off_player = 0;
	_kick_support_player = 0;

	_free = 0; // 任意球
	_cornor = 0; // 角球
	_penalty = 0; // 点球
	srand(time(NULL));
	_cornor_tactical = rand() % 3 + 1; // 角球战术
	_card_can_avoid_offside = false;
	_current_formation_id = 0;
	_att_pid = 0;
	_score = 0;
	_cornor_map.clear();
	_auto_change_count = 0;
	_total_attack_count = 0;
	_who_kick_off = false;
	_team_mode = DS_MODE;
	_move_complex = 0;
	//技能
	_tactic_used_id = 0;
	_last_round_tactic_used = 0;
	current_move_id = -1;
	_back_line = 0;
	_is_all_attack = false;
	_inj_count = 0;
	_alias_tactic_plus = 0.;
	_fitness_coach = 0;

	//喊话,默认喊话的类型是
	for (int i = 0; i < SPEAK_END; i++) {
		_speak_effects[i] = false;
	}

	_deposit_use_skill = false;
	_deposit_change_player = false;
	_skill_rp_pr = 0;
}

SoccerTeam::~SoccerTeam(void) {
	for (int i = 0; i < get_players_on_pitch_count(); ++i) {
		delete _players_on_pitch[i];
		_players_on_pitch[i] = NULL;
	}

	delete _gk_player;
	_gk_player = NULL;

	delete[] player_mark_flag;
}

//reset some state of this soccer team.
void SoccerTeam::re_set(void) {
	this->_has_offside = false;
	this->_offside_player = NULL;

	_closest_player = NULL;
	_supporting_player = NULL;
	_receiving_player = NULL;

	_marking_player = NULL;
	_minding_player = NULL;
	_breaking_player = NULL;
	_air_defend_player = NULL;
	_has_offside = false;

	_action_list.clear();

	player_mark_flag = new int[10];
	for (int i = 0; i < 10; ++i) {
		player_mark_flag[i] = 0;
		this->_line_number[i] = 0;
	}

	for(int player_index =0 ;player_index < _players_on_pitch.size();player_index++){
		_players_on_pitch[player_index]->set_behavior(0);
	}

	//goal_attr.clear();

	_kick_off_player = 0;
	_kick_support_player = 0;

	/*
	 _free = 0; // 任意球
	 _cornor = 0; // 角球
	 _penalty = 0; // 点球
	 */
	//srand(time(NULL));
	//_cornor_tactical = rand() % 3 + 1; // 角球战术
	/*	_card_can_avoid_offside = false;

	 _att_pid = 0;

	 _cornor_map.clear();
	 _auto_change_count = 0;

	 _who_kick_off = false;
	 _team_mode = DS_MODE;
	 _move_complex = 0;*/
}

void SoccerTeam::update_formation(void) {
	if (this->is_att_side()) {
		_formation.update_attack_formation(this);
	} else {
		_formation.update_defend_formation(this);
	}
}

void SoccerTeam::update_players(void) {
	//SoccerPlayer* pPlayer = this->_match->get_def_team_closest_to_offline();
	_gk_player->update();
	for (int i = 0; i < 10; i++) {
		if (_match->get_status() != END_GOAL) {
			SoccerPlayer* player = this->get_player_on_pitch(i);
			//if (player->is_soccer_player_injs() == 0) /* 没有受伤 */
		//	{
				//	调整越位球员
				player->update();
		//	}

			/* 更新守门员的位置 */
		}
	}
	//update_gk_pos();

	//update_gk_pos();
}

/* 1:前锋,2:中场,3:后卫,4:守门员 */
int SoccerTeam::check_position(int position) {
	int ret = 0;
	if (position >= 2 && position <= 10) {
		ret = 1; // 前锋
	} else if ((position >= 11 && position <= 20) || (position >= 22
			&& position <= 24)) {
		ret = 2; // 中场
	} else if ((position == 21) || (position >= 25 && position <= 34)) {
		ret = 3; // 后卫
	} else if (position == 38) {
		ret = 4; // 门将
	}

	return ret;
}

void SoccerTeam::def_penalty_kick_off(int position[]) {
	for (int i = 0; i < 10; i++) {
		Vector2D vecPos;
		if (check_position(position[i]) == 1) {
			vecPos.x = PITCH_WIDTH - (15 - kick_off_player_pos_x[i])
					* LATTICE_SIZE_X + LATTICE_SIZE_X;
			vecPos.y = PITCH_HEIGHT - (kick_off_player_pos_y[i])
					* LATTICE_SIZE_Y;
		} else {
			vecPos.x = B_FORBIDDEN_AREA_X - 1.8 * METER_TO_POINT;
			if (i % 2 == 0) {
				vecPos.y = B_PENALTY_LOCATION_Y + (i + 5 + rand() % (i + 2))
						* METER_TO_POINT;
			} else {
				vecPos.y = B_PENALTY_LOCATION_Y - (i + 5 + rand() % (i + 2))
						* METER_TO_POINT;
			}
		}

		vecPos.y += _players_on_pitch[i]->get_middle_modifer();
		_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
		_players_on_pitch[i]->set_state(StopState::alloc());
		vecPos.x = vecPos.x - 5;
		_players_on_pitch[i]->heading_to(vecPos);
	}

	this->_gk_player->set_pos(B_GOAL_WIDTH - 10, B_GOAL_HEIGHT);
}

void SoccerTeam::def_corner_kick_off(int position[], int flags) {
	int tmp = 1;
	for (int i = 0; i < 10; i++) {
		Vector2D vecPos;
		/*if (check_position(position[i]) == 1) {
			vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X
					+ LATTICE_SIZE_X * 4;
			vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			this->fix_formation_by_move_order(
					this->_move_define->get_move_typ(), _players_on_pitch[i],
					true);
			_players_on_pitch[i]->set_state(GoHomeState::alloc());
			Vector2D tmpVector = _players_on_pitch[i]->get_pos();
			tmpVector.x = tmpVector.x + 5;
			_players_on_pitch[i]->heading_to(tmpVector);
		} else if (check_position(position[i]) == 2) {
			vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X
					+ LATTICE_SIZE_X * 4;
			vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			this->fix_formation_by_move_order(
					this->_move_define->get_move_typ(), _players_on_pitch[i],
					true);
			_players_on_pitch[i]->set_state(StopState::alloc());
			Vector2D tmpVector = _players_on_pitch[i]->get_pos();
			tmpVector.x = tmpVector.x + 5;
			_players_on_pitch[i]->heading_to(tmpVector);
		} else*/ {
			if (flags == CORNER_KICK_UP_OFF) {
				if (tmp == 1) {
					vecPos.x = B_GOAL_WIDTH_X_1;
					vecPos.y = B_GOAL_WIDTH_Y_1;
					tmp++;
					_players_on_pitch[i]->set_state(StopState::alloc());
				} else if (tmp == 2) {
					vecPos.x = B_GOAL_AREA_X + METER_TO_POINT;
					vecPos.y = B_GOAL_AREA_Y;
					tmp++;
					_players_on_pitch[i]->set_state(AreaDefendState::alloc());
				} else if (tmp == 3) {
					vecPos.x = B_GOAL_AREA_X - 2 * METER_TO_POINT;
					vecPos.y = B_GOAL_AREA_Y + GOAL_WIDTH;
					tmp++;
					_players_on_pitch[i]->set_state(AreaDefendState::alloc());
				} else if (tmp == 4) {
					vecPos.x = B_GOAL_AREA_X - 2 * METER_TO_POINT;
					vecPos.y = B_GOAL_AREA_Y + GOAL_WIDTH * 2;
					tmp++;
					_players_on_pitch[i]->set_state(StopState::alloc());
				} else if (tmp == 5) {
					vecPos.x = B_GOAL_WIDTH_X_2;
					vecPos.y = B_GOAL_WIDTH_Y_2;
					tmp++;
					_players_on_pitch[i]->set_state(AreaDefendState::alloc());
				}  else{
					double x = (16 - pos_x_array[position[i] - 1])
							* LATTICE_SIZE_X + LATTICE_SIZE_X * 5;
					if (x >= PITCH_WIDTH - OUTSIDE_WIDTH) {
						x = (16 - pos_x_array[position[i] - 1])
								* LATTICE_SIZE_X + LATTICE_SIZE_X * 4;
					}
					_players_on_pitch[i]->set_state(StopState::alloc());
					vecPos.x = x;
					vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
				}
			} else if (flags == CORNER_KICK_DOWN_OFF) {
				if (tmp == 1) {
					vecPos.x = B_GOAL_WIDTH_X_2;
					vecPos.y = B_GOAL_WIDTH_Y_2;
					tmp++;
					_players_on_pitch[i]->set_state(AreaDefendState::alloc());
				} else if (tmp == 2) {
					vecPos.x = B_GOAL_AREA_X + METER_TO_POINT;
					vecPos.y = B_GOAL_AREA_Y + GOAL_AREA_HEIGHT;
					tmp++;
					_players_on_pitch[i]->set_state(StopState::alloc());
				} else if (tmp == 3) {
					vecPos.x = B_GOAL_AREA_X - 2 * METER_TO_POINT;
					vecPos.y = B_GOAL_AREA_Y - GOAL_WIDTH;
					tmp++;
					_players_on_pitch[i]->set_state(AreaDefendState::alloc());
				} else if (tmp == 4) {
					vecPos.x = B_GOAL_AREA_X - 2 * METER_TO_POINT;
					vecPos.y = B_GOAL_AREA_Y - GOAL_WIDTH * 2;
					tmp++;
					_players_on_pitch[i]->set_state(StopState::alloc());
				} else if (tmp == 5) {
					vecPos.x = B_GOAL_WIDTH_X_1;
					vecPos.y = B_GOAL_WIDTH_Y_1;
					tmp++;
					_players_on_pitch[i]->set_state(AreaDefendState::alloc());
				} else if(tmp == 6){
					vecPos.x = B_GOAL_WIDTH_X_1 - 2*METER_TO_POINT;
					vecPos.y = B_GOAL_WIDTH_Y_1 + 2*METER_TO_POINT;
					tmp++;
					_players_on_pitch[i]->set_state(StopState::alloc());
				} else if(tmp == 7){
					vecPos.x = B_GOAL_WIDTH_X_1 + 2*METER_TO_POINT;
					vecPos.y = B_GOAL_WIDTH_Y_1 - 2*METER_TO_POINT;
					tmp++;
					_players_on_pitch[i]->set_state(StopState::alloc());
				} else {
					double x = (16 - pos_x_array[position[i] - 1])
							* LATTICE_SIZE_X + LATTICE_SIZE_X * 5;
					if (x >= PITCH_WIDTH - OUTSIDE_WIDTH) {
						x = (16 - pos_x_array[position[i] - 1])
								* LATTICE_SIZE_X + LATTICE_SIZE_X * 4;
					}
					vecPos.x = x;
					vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
					_players_on_pitch[i]->set_state(AreaDefendState::alloc());
				}
			}

			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
/*			this->fix_formation_by_move_order(
					this->_move_define->get_move_typ(), _players_on_pitch[i],
					true);*/
			Vector2D tmpVector = _players_on_pitch[i]->get_pos();
			tmpVector.x = tmpVector.x + 5;
			_players_on_pitch[i]->heading_to(tmpVector);
		}
	}

	this->_gk_player->set_pos(B_GOAL_WIDTH - OUTSIDE_WIDTH, B_GOAL_HEIGHT);
	this->_gk_player->set_state(StopState::alloc());
}

/* 设置角球接球人 */
void SoccerTeam::set_cornor_kick_support_player(int flags, int i, double x,
		double y) {
	cornor_player p(i, x, y);
	_cornor_map.insert(std::map<int, cornor_player>::value_type(flags, p));
}

double SoccerTeam::get_team_skill_success_rate(int skill_id,int speak_type) {
	switch (skill_id) {
	case 1:
		if (speak_type == SPEAK_MORE_SPACE)
			return 1.3;
		if (speak_type == SPEAK_LESS_SPACE)
			return 0.7;
		break;
	case 2:
		if (speak_type == SPEAK_MORE_SPACE)
			return 0.7;
		if (speak_type == SPEAK_LESS_SPACE)
			return 1.3;
		break;
	case 3:
		if (speak_type == SPEAK_MORE_SPACE)
			return 0.7;
		if (speak_type == SPEAK_LESS_SPACE)
			return 1.3;
		break;
	case 4:
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 0.7;
		break;
	case 5:
		if (speak_type == SPEAK_MORE_FOOT_PASS)
			return 1.3;
		if (speak_type == SPEAK_MORE_EMPTY_PASS)
			return 0.7;
		break;
	case 6:
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 0.7;
		break;
	case 7:
		if (speak_type == SPEAK_MORE_FOOT_PASS)
			return 1.3;
		if (speak_type == SPEAK_MORE_EMPTY_PASS)
			return 0.7;
		break;
	case 8:
		if (speak_type == SPEAK_MORE_CORSS)
			return 1.3;
		if (speak_type == SPEAK_MORE_PASS)
			return 0.7;
		break;
	case 9:
		if (speak_type == SPEAK_MORE_CORSS)
			return 1.3;
		if (speak_type == SPEAK_MORE_PASS)
			return 0.7;
		break;
	case 10:
		if (speak_type == SPEAK_MORE_EMPTY_PASS)
			return 1.3;
		if (speak_type == SPEAK_MORE_FOOT_PASS)
			return 0.7;
		break;
	case 11:
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 0.7;
		break;
	case 12:
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 0.7;
		break;
	case 13:
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_LESS_SPACE)
			return 1.3;
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 0.7;
		if (speak_type == SPEAK_MORE_SPACE)
			return 0.7;
		break;
	case 14:
		if (speak_type == SPEAK_ATTACK_ATTACK)
			return 1.3;
		if (speak_type == SPEAK_MORE_SPACE)
			return 1.3;
		if (speak_type == SPEAK_DEFEND_ATTACK)
			return 0.7;
		if (speak_type == SPEAK_LESS_SPACE)
			return 0.7;
		break;
	case 15:
		if (speak_type == SPEAK_MORE_PASS)
			return 1.3;
		if (speak_type == SPEAK_MORE_CORSS)
			return 0.7;
		break;
	default:
		return 1.;
	}
	return 1.;
}


void SoccerTeam::att_corner_kick_off(int position[], int flags) {
	SoccerPlayer* corner_player = pick_corner_ball_player();
	_controlling_player = corner_player;

	int tmp = 1;
	int tmp2 = 4;
	for (int i = 0; i < 10; i++)
	{
		Vector2D vecPos;
		if (_players_on_pitch[i]->get_union_pid() == corner_player->get_union_pid())
		{
			vecPos.x = PITCH_WIDTH;
			vecPos.y = 0.;
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(GoHomeState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
		}else{
			if (check_position(position[i]) == 3) // 后卫
			{
				vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X + LATTICE_SIZE_X * 5;
				vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
				_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
				_players_on_pitch[i]->set_state(GoHomeState::alloc());
				Vector2D tmpVector = _players_on_pitch[i]->get_pos();
				tmpVector.x = tmpVector.x + 5;
				_players_on_pitch[i]->heading_to(tmpVector);
			}
			else if (check_position(position[i]) == 2) // 中卫
			{
				vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X + LATTICE_SIZE_X * 6 + 10*METER_TO_POINT;
				vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
				_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
				_players_on_pitch[i]->set_state(StopState::alloc());
				Vector2D tmpVector = _players_on_pitch[i]->get_pos();
				tmpVector.x = tmpVector.x + 5;
				_players_on_pitch[i]->heading_to(tmpVector);
				if(vecPos.x <0||vecPos.x >PITCH_WIDTH || vecPos.y >PITCH_HEIGHT || vecPos.x < 0){
					LOG(ERROR)<<"supporting error...";
				}
				set_cornor_kick_support_player(tmp2, i, vecPos.x, vecPos.y);
				tmp2++;
			}
			else// if (check_position(position[i] - 1) == 1) 前锋
			{
				if (tmp == 1) // 前点头球
				{
					vecPos.x = B_GOAL_AREA_X;
					vecPos.y = B_GOAL_AREA_Y;
				}
				else if (tmp == 2) // 后点头球
				{
					vecPos.x = B_GOAL_AREA_X;
					vecPos.y = B_GOAL_AREA_Y + GOAL_WIDTH;
				}
				else if (tmp == 3) // 大禁区
				{
					vecPos.x = B_FORBIDDEN_AREA_X;
					vecPos.y = B_FORBIDDEN_AREA_Y;
				}
				else if (tmp == 4){
					vecPos.x = B_FORBIDDEN_AREA_X+METER_TO_POINT*2;
					vecPos.y = B_FORBIDDEN_AREA_Y+METER_TO_POINT*2;
				}
				else if(tmp == 5){
					vecPos.x = B_FORBIDDEN_AREA_X+METER_TO_POINT*4;
					vecPos.y = B_FORBIDDEN_AREA_Y+METER_TO_POINT*4;
				}
				else if(tmp ==6){
					vecPos.x = B_FORBIDDEN_AREA_X-METER_TO_POINT*4;
					vecPos.y = B_FORBIDDEN_AREA_Y+METER_TO_POINT*4;
				}
				else // 其他
				{
					double x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X + LATTICE_SIZE_X * 5;
					if (x >= PITCH_WIDTH - OUTSIDE_WIDTH)
					{
						x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X + LATTICE_SIZE_X * 4;
					}
					vecPos.x = x;
					vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
				}

				set_cornor_kick_support_player(tmp, i, vecPos.x, vecPos.y);
				tmp++;

				_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
				_players_on_pitch[i]->set_state(GoHomeState::alloc());
				Vector2D tmpVector = _players_on_pitch[i]->get_pos();
				tmpVector.x = tmpVector.x + 5;
				_players_on_pitch[i]->heading_to(tmpVector);
			}
		}
	}
	//	else if (flags == CORNER_KICK_DOWN_OFF)
	//	{
	//		int tmp = 1;
	//		int tmp2 = 4;
	//		for (int i = 0; i < 10; i++)
	//		{
	//			Vector2D vecPos;
	//			if (_players[i]->_union_pid == _cornor)
	//			{
	//				_kick_off_player = i;
	//				vecPos.x = 0.;
	//				vecPos.y = PITCH_HEIGHT;
	//				_players[i]->set_pos(vecPos.x, vecPos.y);
	//				_players[i]->set_state(GoHomeState::alloc());
	//				_players[i]->heading_to(vecPos);
	//			}
	//			else if (check_position(position[i]) == 3)
	//			{
	//				vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X + LATTICE_SIZE_X * 5;
	//				vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
	//				_players[i]->set_pos(vecPos.x, vecPos.y);
	//				this->fix_formation_by_move_order(this->_move_define->get_move_typ(), _players[i], true);
	//				_players[i]->set_state(GoHomeState::alloc());
	//				Vector2D tmpVector = _players[i]->get_pos();
	//				tmpVector.x = tmpVector.x + 5;
	//				_players[i]->heading_to(tmpVector);
	//			}
	//			else if (check_position(position[i]) == 2)
	//			{
	//				vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X + LATTICE_SIZE_X * 6;
	//				vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
	//				_players[i]->set_pos(vecPos.x, vecPos.y);
	//				this->fix_formation_by_move_order(this->_move_define->get_move_typ(), _players[i], true);
	//				_players[i]->set_state(GoHomeState::alloc());
	//				Vector2D tmpVector = _players[i]->get_pos();
	//				tmpVector.x = tmpVector.x + 5;
	//				_players[i]->heading_to(tmpVector);
	//
	//				set_cornor_kick_support_player(tmp2, i, vecPos.x, vecPos.y);
	//				tmp2++;
	//			}
	//			else// if (check_position(position[i] - 1) == 1)
	//			{
	//				if (tmp == 1) // 前小禁区角
	//				{
	//					vecPos.x = B_GOAL_AREA_X;
	//					vecPos.y = B_GOAL_AREA_Y + GOAL_AREA_HEIGHT;
	//				}
	//				else if (tmp == 2) // 后小禁区角
	//				{
	//					vecPos.x = B_GOAL_AREA_X;
	//					vecPos.y = B_GOAL_AREA_Y + GOAL_WIDTH;
	//					VLOG(3) << "vecPos:" << vecPos.x << "," << vecPos.y;
	//				}
	//				else if (tmp == 3) // 大禁区
	//				{
	//					vecPos.x = B_FORBIDDEN_AREA_X;
	//					vecPos.y = B_FORBIDDEN_AREA_Y;
	//				}
	//				else
	//				{
	//					double x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X + LATTICE_SIZE_X * 5;
	//					if (x >= PITCH_WIDTH - OUTSIDE_WIDTH)
	//					{
	//						x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X + LATTICE_SIZE_X * 4;
	//					}
	//					vecPos.x = x;
	//					vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
	//				}
	//
	//				set_cornor_kick_support_player(tmp, i, vecPos.x, vecPos.y);
	//				tmp++;
	//
	//				_players[i]->set_pos(vecPos.x, vecPos.y);
	//				this->fix_formation_by_move_order(this->_move_define->get_move_typ(), _players[i], true);
	//				_players[i]->set_state(GoHomeState::alloc());
	//				Vector2D tmpVector = _players[i]->get_pos();
	//				tmpVector.x = tmpVector.x + 5;
	//				_players[i]->heading_to(tmpVector);
	//			}
	//		}
	//	}

	this->_gk_player->set_pos(A_FORBIDDEN_AREA_X + LATTICE_SIZE_X, A_GOAL_HEIGHT);
	this->_gk_player->set_state(StopState::alloc());
}

void SoccerTeam::att_penalty_kick_off(int position[]) {
	int tmp = 0;
	int temp = 0;
	for (int i = 0; i < 10; i++)
	{
		Vector2D vecPos;
		if (_players_on_pitch[i]->_union_pid == _penalty) // 开球人
		{
			tmp = 1;
			_kick_off_player = i;
			double y = B_PENALTY_LOCATION_Y - 0.5 * METER_TO_POINT;
			if (_players_on_pitch[i]->get_footedness() == 1
					|| _players_on_pitch[i]->get_footedness() == 2)
			{
				y = B_PENALTY_LOCATION_Y + 2.5 * METER_TO_POINT;
			}
			else if (_players_on_pitch[i]->get_footedness() == 5)
			{
				int i_rand = rand() % 100;
				if (i_rand > 50)
				{
					y = B_PENALTY_LOCATION_Y + 2.5 * METER_TO_POINT;
				}
			}
			vecPos.x = B_PENALTY_LOCATION_X - 4 * METER_TO_POINT;
			vecPos.y = y;
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(Penalty::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
		}
		else if (i == 9 && tmp == 0) // 如果数据库开球人没有找到
		{
			tmp = 1;
			_kick_off_player = i;
			double y = B_PENALTY_LOCATION_Y - 0.5 * METER_TO_POINT;
			if (_players_on_pitch[i]->get_footedness() == 1
					|| _players_on_pitch[i]->get_footedness() == 2)
			{
				y = B_PENALTY_LOCATION_Y + 0.5 * METER_TO_POINT;
			}
			else if (_players_on_pitch[i]->get_footedness() == 5)
			{
				int i_rand = rand() % 100;
				if (i_rand > 50)
				{
					y = B_PENALTY_LOCATION_Y + 0.5 * METER_TO_POINT;
				}
			}
			vecPos.x = B_PENALTY_LOCATION_X - 2.5 * METER_TO_POINT;
			vecPos.y = y;
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(Penalty::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
		}
		else // 其他人站位
		{
			Vector2D vecPos;
			if (check_position(position[i]) == 3)
			{
				if (temp == 0)
				{
					vecPos.x = PITCH_WIDTH / 2 + METER_TO_POINT * 3;
					vecPos.y = PITCH_HEIGHT / 2 + METER_TO_POINT * 6;
					temp = 1;
				}
				else if (temp == 1)
				{
					vecPos.x = PITCH_WIDTH / 2 + METER_TO_POINT * 3;
					vecPos.y = PITCH_HEIGHT / 2 - METER_TO_POINT * 6;
					temp = 2;
				}
				else
				{
					if (i % 2 == 0)
					{
						vecPos.y = PITCH_HEIGHT / 2 + (i + 11 + rand() % (i + 2)) * METER_TO_POINT;
					}
					else
					{
						vecPos.y = PITCH_HEIGHT / 2 - (i + 11 + rand() % (i + 2)) * METER_TO_POINT;
					}
					vecPos.x = PITCH_WIDTH / 2 + METER_TO_POINT * 12;
				}
			}
			else
			{
				vecPos.x = B_FORBIDDEN_AREA_X - 2 * METER_TO_POINT;
				if (i % 2 == 0)
				{
					vecPos.y = B_PENALTY_LOCATION_Y + (i + 4 + rand() % (i + 2)) * METER_TO_POINT;
				}
				else
				{
					vecPos.y = B_PENALTY_LOCATION_Y - (i + 4 + rand() % (i + 2)) * METER_TO_POINT;
				}
			}

			vecPos.y -= _players_on_pitch[i]->get_middle_modifer();
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			this->fix_formation_by_move_order(this->_move_define->get_move_typ(), _players_on_pitch[i], true);
			_players_on_pitch[i]->set_state(StopState::alloc());
			vecPos.x = vecPos.x + 5;
			_players_on_pitch[i]->heading_to(vecPos);
		}
	}

	this->_gk_player->set_pos(A_FORBIDDEN_AREA_X - OUTSIDE_WIDTH, A_GOAL_HEIGHT);
}

void SoccerTeam::def_shootout_penalty(int position[]) {
	int t_size = 1;
	for (int i = 0; i < 10; i++) {
		Vector2D vecPos;
		vecPos.x = STADIUM_CENTER_WIDTH;
		vecPos.y = STADIUM_CENTER_HEIGHT + (t_size + 4) * METER_TO_POINT;

		_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
		_players_on_pitch[i]->set_state(GoHomeState::alloc());
		_players_on_pitch[i]->heading_to(vecPos);

		t_size++;
	}

	this->_gk_player->set_pos(B_GOAL_WIDTH - OUTSIDE_WIDTH, B_GOAL_HEIGHT);
}

Vector2D SoccerTeam::get_free_kick_off_wall_x_y(Vector2D &v, double d) {
	Vector2D goal;
	goal.x = B_GOAL_WIDTH;
	goal.y = B_GOAL_HEIGHT;

	Vector2D ret;

	int tmp = (int) (v.y - goal.y);
	if (v.y == goal.y) {
		tmp = 0;
	}

	double o;

	if (v.x > STADIUM_CENTER_WIDTH) {
		int t_atan = (int) atan((v.x - goal.x) / tmp);
		if (t_atan < 0) {
			o = 1.5 * M_PI + (atan((v.x - goal.x) / tmp) * -1);
		} else {
			o = 0.5 * M_PI - atan((v.x - goal.x) / tmp);
		}
	} else {
		int t_atan = (int) atan((v.x - goal.x) / tmp);
		if (t_atan < 0) {
			o = 0.5 * M_PI + (atan((v.x - goal.x) / tmp) * -1);
		} else {
			o = 1.5 * M_PI - atan((v.x - goal.x) / tmp);
		}
	}

	ret.x = 9.15 * METER_TO_POINT * cos(o + d / 9.15) + v.x;
	ret.y = 9.15 * METER_TO_POINT * sin(o + d / 9.15) + v.y;

	return ret;
}

void SoccerTeam::def_free_kick_off(int position[]) // 防守任意球
{
	int tmp1 = 1; // 前锋 1 个
	int tmp2 = 1; // 人墙 4 个
	_player_pos = _match->get_player_pos();
	for (int i = 0; i < 10; i++) {
		Vector2D vecPos;
		if (tmp1 <= 2 && check_position(position[i]) == 1) // 前锋 1 个
		{
			vecPos.x = PITCH_WIDTH - (15 - kick_off_player_pos_x[i])
					* LATTICE_SIZE_X + LATTICE_SIZE_X;
			vecPos.y = PITCH_HEIGHT - (kick_off_player_pos_y[i])
					* LATTICE_SIZE_Y;
			vecPos.y += _players_on_pitch[i]->get_middle_modifer();
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			Vector2D tmpVector = _players_on_pitch[i]->get_pos();
			tmpVector.x = tmpVector.x - 5;
			_players_on_pitch[i]->heading_to(tmpVector);

			tmp1++;
			continue;
		}

		if (tmp2 <= 1) {
			vecPos = get_free_kick_off_wall_x_y(_player_pos, 1.5);

			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);

			tmp2++;
		} else if (tmp2 <= 2) {
			vecPos = get_free_kick_off_wall_x_y(_player_pos, -1.5);

			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);

			tmp2++;
		} else if (tmp2 <= 3) {
			vecPos = get_free_kick_off_wall_x_y(_player_pos, 1);

			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);

			tmp2++;
		} else if (tmp2 <= 4) {
			vecPos = get_free_kick_off_wall_x_y(_player_pos, -1);

			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);

			tmp2++;
		} else // 其他人
		{
			vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X;
			if (vecPos.x >= get_free_kick_off_wall_x_y(_player_pos, 1.5).x
					&& vecPos.x <= _player_pos.x) {
				vecPos.x = get_free_kick_off_wall_x_y(_player_pos, 1.5).x;
			}
			vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_X;

			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
		}

	}

	this->_gk_player->set_pos(B_GOAL_WIDTH - OUTSIDE_WIDTH, B_GOAL_HEIGHT);
	this->_gk_player->set_state(StopState::alloc());
}

void SoccerTeam::kick_off_player(int pid, int position_id, int position[]) {
	for (int i = 0; i < 10; i++) {
		if (_players_on_pitch[i]->is_soccer_player_injs() == 0) {
			if (_players_on_pitch[i]->_union_pid == pid) {
				_kick_off_player = i;
				break;
			} else if (check_position(position[i]) == position_id) {
				_kick_off_player = i;
				break;
			} else if (i == 9) {
				_kick_off_player = i;
				break;
			}
		}
	}
}

void SoccerTeam::att_free_kick_off(int position[]) // 进攻任意球
{
	kick_off_player(_free, 1, position); // 找出开球人

	int tmp1 = 1; // 后卫
	int tmp2 = 1; // 开任意球旁边的两个人
	//int tmp3 = 1; // 人墙的两个人
	_player_pos = _match->get_player_pos();
	for (int i = 0; i < 10; i++)
	{
		Vector2D vecPos;
		if (_kick_off_player == i) // 开球人
		{
			vecPos.y = _match->get_player_pos().y - 1 * METER_TO_POINT;
			vecPos.x = _match->get_player_pos().x - 7 * METER_TO_POINT;
			_players_on_pitch[i]->set_pos(vecPos);
			_players_on_pitch[i]->set_state(Free::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
			this->get_match()->get_ball()->set_speed(0);
			this->get_match()->get_ball()->set_pos(_player_pos);
			_match->get_ball()->set_owner(_players_on_pitch[i]);
			LOG(INFO)<<"开球咯。。。。。。"<<_player_pos.x<<":"<<_player_pos.y;
			continue;
		}

		// 不开任意球的人
		if (tmp1 <= 3 && check_position(position[i]) == 3) // 后卫站的位置 2 个
		{
			tmp1++;
			vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X + LATTICE_SIZE_X + LATTICE_SIZE_X;
			vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
			vecPos.y -= _players_on_pitch[i]->get_middle_modifer();
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			this->fix_formation_by_move_order(this->_move_define->get_move_typ(), _players_on_pitch[i], true);
			_players_on_pitch[i]->set_state(StopState::alloc());
			Vector2D tmpVector = _players_on_pitch[i]->get_pos();
			tmpVector.x = tmpVector.x + 5;
			_players_on_pitch[i]->heading_to(tmpVector);

			continue;
		}

		if (tmp2 == 1)
		{
			tmp2 = 2;
			vecPos = get_free_kick_off_wall_x_y(_player_pos, -3.5);
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
		}
		else if (tmp2 == 2)
		{
			tmp2 = 3;
			vecPos = get_free_kick_off_wall_x_y(_player_pos, 3.5);
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
		}else // 其他人
		{
			vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X;
			if (vecPos.x >= get_free_kick_off_wall_x_y(_player_pos, 1.5).x
					&& vecPos.x <= _player_pos.x)
			{
				vecPos.x = get_free_kick_off_wall_x_y(_player_pos, -1.5).x;
			}
			vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_X;

			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
		}
	}

	this->_gk_player->set_pos(A_GOAL_WIDTH + OUTSIDE_WIDTH, A_GOAL_HEIGHT);
	this->_gk_player->set_state(StopState::alloc());
}

void SoccerTeam::att_shootout_penalty(int position[]) {
	int t_size = 1;
	int tmp = 0;
	for (int i = 0; i < 10; i++) {
		Vector2D vecPos;
		if (_players_on_pitch[i]->_union_pid == _att_pid) // 开球人
		{
			tmp = 1;
			_kick_off_player = i;
			double y = B_PENALTY_LOCATION_Y - 0.5 * METER_TO_POINT;
			if (_players_on_pitch[i]->get_footedness() == 1
					|| _players_on_pitch[i]->get_footedness() == 2) {
				y = B_PENALTY_LOCATION_Y + 0.5 * METER_TO_POINT;
			} else if (_players_on_pitch[i]->get_footedness() == 5) {
				int i_rand = rand() % 100;
				if (i_rand > 50) {
					y = B_PENALTY_LOCATION_Y + 0.5 * METER_TO_POINT;
				}
			}
			vecPos.x = B_PENALTY_LOCATION_X - 2.5 * METER_TO_POINT;
			vecPos.y = y;
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(Penalty::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
		} else if (i == 9 && tmp == 0) {
			_kick_off_player = i;
			double y = B_PENALTY_LOCATION_Y - 0.5 * METER_TO_POINT;
			int i_rand = rand() % 100;
			if (i_rand > 50) {
				y = B_PENALTY_LOCATION_Y + 0.5 * METER_TO_POINT;
			}
			vecPos.x = B_PENALTY_LOCATION_X - 2.5 * METER_TO_POINT;
			vecPos.y = y;
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(Penalty::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
		} else {
			vecPos.x = STADIUM_CENTER_WIDTH;
			vecPos.y = STADIUM_CENTER_HEIGHT - (t_size + 1) * METER_TO_POINT;

			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->heading_to(vecPos);
			t_size++;
		}
	}

	this->_gk_player->set_pos(B_GOAL_WIDTH - METER_TO_POINT, B_GOAL_HEIGHT
			+ FORBIDDEN_AREA_HEIGHT / 2 + METER_TO_POINT);
}

void SoccerTeam::att_goal_kick_off(int position[]) {
	int index[10];
	int count = 0;
	for (int i = 0; i < 10; i++) //第一次循环找出两个开球人
	{
		if (_players_on_pitch[i]->is_soccer_player_injs() == 0) {
			if (check_position(position[i]) != 3)// && check_position(position[i]) != 2) // 不是后卫
			{
				index[count] = i;
				count++;
			}
		}
	}

	if (count < 2) {
		LOG(ERROR)<< "error";
		return;
	}

	int r = rand() % count;
	int j = index[r];
	_kick_off_player = j; //选取开球人后，如果r=0,j=0,但是特殊处理不用第一个人
	if (r == 0)
	{
		if (j == 0)
		{
			_kick_off_player = index[1];
			_kick_support_player = index[2];
		}
		else
		{
			_kick_support_player = index[r + 1];
		}
	}
	else
	{
		_kick_support_player = index[r - 1];
	}

	//	_kick_off_player = index[0];
	//	_kick_support_player = index[1];

	for (int i = 0; i < 10; i++)
	{
		Vector2D vecPos;
		if (i == _kick_off_player)
		{
			vecPos.x = STADIUM_CENTER_WIDTH;
			vecPos.y = STADIUM_CENTER_HEIGHT;
		}
		else if (i == _kick_support_player)
		{
			vecPos.x = STADIUM_CENTER_WIDTH;
			vecPos.y = STADIUM_CENTER_HEIGHT + STADIUM_CENTER_CIRCLE / 2;
		}
		else
		{
			vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X / 1.5; // 收缩到半场开球
			if (check_position(position[i]) == 3)
			{
				vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X;
			}
			else if (check_position(position[i]) == 2)
			{
				vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X / 1.2;
			}

			if (vecPos.x > STADIUM_CENTER_WIDTH - METER_TO_POINT * 10)
			{
				vecPos.x = STADIUM_CENTER_WIDTH - METER_TO_POINT * 10;
			}
			vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
			vecPos.y -= _players_on_pitch[i]->get_middle_modifer();
		}

		_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
		_players_on_pitch[i]->set_state(GoHomeState::alloc());
		vecPos.x += 5;
		_players_on_pitch[i]->heading_to(vecPos);
	}
	this->_gk_player->set_state(StopState::alloc());
	this->_gk_player->set_pos(A_GOAL_WIDTH + OUTSIDE_WIDTH, A_GOAL_HEIGHT);
}

void SoccerTeam::def_normal_kick_off(int position[]) {
	int round_typ = this->_match->get_round_typ();

	int backline = (position[0] - 1) / 5;
	int
			line_number[41] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0 };
	Player_Formation_Cell cell;
	for (int i = 0; i < 10; i++) {
		cell.x_cell = (position[i] - 1) / 5;
		cell.y_cell = (position[i] - 1) % 5;
		if (backline <= cell.x_cell) {
			backline = cell.x_cell;
		}
		this->_line_number[cell.x_cell] = this->_line_number[cell.x_cell] + 1;
		line_number[position[i]] = position[i];
		_players_on_pitch[i]->_row_index = cell.x_cell;
	}
	this->_back_line = backline;
	//計算在y方向的順序
	for (int i = 0; i < 10; i++) {
		int index = 0;
		int pos = _players_on_pitch[i]->get_formation_pos();
		for (int j = (pos - pos % 5 + 1); j < (pos - pos % 5 + 5 + 1); j++) {
			if (line_number[j] != 0) {
				if (line_number[j] > pos) {
					index++;
				}
			}
		}
		_players_on_pitch[i]->_column_index = index;
	}

	double dis_between_players = 13;
/*	if (this->check_coach_speak(SPEAK_MORE_SPACE)) {
		dis_between_players += 7 / (this->_line_number[(position[i] - 1)
				/ 5] - 1);
	} else if (this->check_coach_speak(SPEAK_LESS_SPACE)) {
		dis_between_players += 8 / (this->_line_number[(position[i] - 1)
				/ 5] - 1);
	}*/

	//站在中圈弧的球员的数量
	int player_number = 0;
	for (int i = 0; i < 10; i++) {
		Vector2D vecPos;
		vecPos.x = (DEFEND_LINE - ((backline - (position[i] - 1) / 5) * 10
				* METER_TO_POINT));

		vecPos.y = (PITCH_HEIGHT - (this->_line_number[(position[i] - 1) / 5]
				- 1) * dis_between_players * METER_TO_POINT) / 2
				+ _players_on_pitch[i]->_column_index * dis_between_players
						* METER_TO_POINT;
		if (position[i] % 5 == 1 || position[i] % 5 == 0) {
			vecPos.x = vecPos.x - 5 * METER_TO_POINT;
		}
		_players_on_pitch[i]->set_state(AreaDefendState::alloc());
		if (round_typ == KICK_OFF || // 上半场开场
				round_typ == MIDDLE_INJURY_KICK || // 中场补时
				round_typ == MIDDLE_KICK_OFF || // 下半场开球
				round_typ == END_INJURY_KICK || // 下半场补时
				round_typ == GOAL_KICK_OFF) {
			if (_players_on_pitch[i]->get_formation_pos() <= 10) {
				player_number++;
				Vector2D tempVec;
				if (player_number == 1) {
					tempVec.x = PITCH_WIDTH / 2 + RAND_INT % 10;
					tempVec.y = PITCH_HEIGHT / 2 - 10 * METER_TO_POINT;
				} else if (player_number == 2) {
					tempVec.x = PITCH_WIDTH / 2 + 10 * METER_TO_POINT;
					tempVec.y = PITCH_HEIGHT / 2 + RAND_INT % 10;
				} else if (player_number == 3) {
					tempVec.x = PITCH_WIDTH / 2 + RAND_INT % 10;
					tempVec.y = PITCH_HEIGHT / 2 + 10 * METER_TO_POINT;
				}
				_players_on_pitch[i]->set_pos(tempVec);
			} else {
				if ((vecPos.y > PITCH_HEIGHT / 2 - 10 * METER_TO_POINT
						&& vecPos.y < PITCH_HEIGHT / 2 + 10 * METER_TO_POINT)
						&& vecPos.x < PITCH_WIDTH / 2 + 10 * METER_TO_POINT) {
					vecPos.x = PITCH_WIDTH / 2 + 13 * METER_TO_POINT;
				} else if (vecPos.x < PITCH_WIDTH / 2) {
					vecPos.x = PITCH_WIDTH / 2;
				}
				_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			}
		} else {
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
		}

		//赋值初始化站位
		_players_on_pitch[i]->_init_pos = vecPos;
		Vector2D tmpVector = _players_on_pitch[i]->get_pos();
		tmpVector.x = tmpVector.x - 5;
		_players_on_pitch[i]->heading_to(tmpVector);
	}

	if (round_typ == KICK_OFF || // 上半场开场
			round_typ == MIDDLE_INJURY_KICK || // 中场补时
			round_typ == MIDDLE_KICK_OFF || // 下半场开球
			round_typ == END_INJURY_KICK || // 下半场补时
			round_typ == GOAL_KICK_OFF) {
		if (player_number < 3)//找离这个点最近的人补齐
		{
			Vector2D tmpVec1;
			tmpVec1.x = PITCH_WIDTH / 2 + RAND_INT % 10;
			tmpVec1.y = PITCH_HEIGHT / 2 + 10 * METER_TO_POINT;
			double distance_to_point = PITCH_WIDTH / 2;
			int index = 0;
			int j;
			for (j = 0; j < 10; j++) {
				if (_players_on_pitch[j]->get_formation_pos() > 10) {
					if (distance_to_point
							> _players_on_pitch[j]->get_pos().distance(tmpVec1)) {
						distance_to_point
								= _players_on_pitch[j]->get_pos().distance(
										tmpVec1);
						index = j;
					}
				}
			}

			_players_on_pitch[index]->set_pos(tmpVec1);
		}
	}

	this->_gk_player->set_pos(B_GOAL_WIDTH - OUTSIDE_WIDTH, B_GOAL_HEIGHT);
	this->_gk_player->set_state(StopState::alloc());
}

//半場開球,防守站位
void SoccerTeam::def_middle_kick_off(int position[]) {
	for (int i = 0; i < 10; i++) {
		Vector2D vecPos;
		vecPos.x = PITCH_WIDTH - (15 - kick_off_player_pos_x[i])
				* LATTICE_SIZE_X;
		vecPos.y = PITCH_HEIGHT - (kick_off_player_pos_y[i]) * LATTICE_SIZE_Y;
		vecPos.y += _players_on_pitch[i]->get_middle_modifer();
		if (check_position(position[i]) == 3) {
			vecPos.x = PITCH_WIDTH - (15 - kick_off_player_pos_x[i]) *LATTICE_SIZE_X * 3;
		}
			else if (check_position(position[i]) == 2)
			{
				vecPos.x = PITCH_WIDTH - (15 - kick_off_player_pos_x[i]) * LATTICE_SIZE_X * 1.3;
			}

			if (vecPos.x < STADIUM_CENTER_WIDTH)
			{
				vecPos.x = STADIUM_CENTER_WIDTH;
			}
			_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);
			_players_on_pitch[i]->_init_pos = vecPos;
			_players_on_pitch[i]->set_state(AreaDefendState::alloc());
			Vector2D tmpVector = _players_on_pitch[i]->get_pos();
			tmpVector.x = tmpVector.x - 5;
			_players_on_pitch[i]->heading_to(tmpVector);
		}

		this->_gk_player->set_pos(B_GOAL_WIDTH - OUTSIDE_WIDTH, B_GOAL_HEIGHT);
		this->_gk_player->set_state(StopState::alloc());
	}

void SoccerTeam::att_defend_att_kick_off() {
	for (int i = 0; i < 10; i++) {
		_players_on_pitch[i]->set_state(GoHomeState::alloc());
		//变换位置
		Vector2D new_pos(PITCH_WIDTH - _players_on_pitch[i]->get_pos().x,PITCH_HEIGHT - _players_on_pitch[i]->get_pos().y);
		_players_on_pitch[i]->set_pos(new_pos);
	}
	_gk_player->set_pos(A_GOAL_WIDTH + OUTSIDE_WIDTH, A_GOAL_HEIGHT);
	this->_gk_player->set_state(StopState::alloc());
	_formation.update_attack_formation(this);
}

void SoccerTeam::def_defend_att_kick_off(int position[]) {
	init_def_formation_before(position);
	for (int i = 0; i < 10; i++) {
		_players_on_pitch[i]->set_state(AreaDefendState::alloc());
		Vector2D new_pos(PITCH_WIDTH - _players_on_pitch[i]->get_pos().x,PITCH_HEIGHT - _players_on_pitch[i]->get_pos().y);
		_players_on_pitch[i]->set_pos(new_pos);
	}
	_gk_player->set_pos(B_GOAL_WIDTH - OUTSIDE_WIDTH, A_GOAL_HEIGHT);
	this->_gk_player->set_state(StopState::alloc());
	_formation.update_defend_formation(this);
}

//普通開球，比如被搶斷
void SoccerTeam::att_normal_kick_off(int position[]) {
	for (int i = 0; i < 10; i++) {
		Vector2D vecPos;
		vecPos.x = (16 - pos_x_array[position[i] - 1]) * LATTICE_SIZE_X;
		vecPos.y = (pos_y_array[position[i] - 1]) * LATTICE_SIZE_Y;
		vecPos.y -= _players_on_pitch[i]->get_middle_modifer();
		_players_on_pitch[i]->set_pos(vecPos.x, vecPos.y);

		this->fix_formation_by_move_order(this->_move_define->get_move_typ(),
				_players_on_pitch[i], true);
		_players_on_pitch[i]->set_state(GoHomeState::alloc());
		vecPos.x = vecPos.x + 5;
		_players_on_pitch[i]->heading_to(vecPos);
	}
	//this->_gk_player->set_state(GKKickOffState::alloc());
	this->_gk_player->set_pos(7*METER_TO_POINT, A_GOAL_HEIGHT);
	_match->get_ball()->set_pos(7*METER_TO_POINT, A_GOAL_HEIGHT);
	_controlling_player = NULL;
//	GKKickOffState* state = GKKickOffState::alloc();
//	Vector2D vec(10*METER_TO_POINT,PITCH_HEIGHT/2);
//	state->_targetVec = vec;
//	this->_gk_player->set_state(state);
}

// 初始站位
void SoccerTeam::init_formation(int position[]) {
	for (int i = 0; i < 10; i++) {
		_players_on_pitch[i]->set_formation_pos(position[i]);
	}

	_formation.set_attack(this->is_att_side());
	_formation.set_position(position);
	_formation.fix_formation_middle_empty(this);

	int round_typ = this->_match->get_round_typ();
	// 初始化位置的信息
	if (is_att_side()) // 进攻
	{
		_formation.set_move_typ(this->_move_define->get_move_typ());
		//round_typ = KICK_OFF;
		switch (round_typ) {
		case KICK_OFF: // 上半场开场
		case MIDDLE_INJURY_KICK: // 中场补时
		case MIDDLE_KICK_OFF: // 下半场开球
		case END_INJURY_KICK: // 下半场补时
		case GOAL_KICK_OFF: // 进球
		{
			att_goal_kick_off(position);
		}
			break;
		/*case PENALTY_KICK_OFF: // 点球
		{
			att_penalty_kick_off(position);
		}
			break;
			*/
		case CORNER_KICK_UP_OFF: // 角球
		case CORNER_KICK_DOWN_OFF: // 角球
		{
			att_corner_kick_off(position, round_typ);
		}
			break;

		case FREE_KICK_OFF: // 任意球
		{
			att_free_kick_off(position);
		}
		break;
		/*
			break;
		case SHOOTOUT_PENALTY: // 点球大战
		{
			att_penalty_kick_off(position);
			//				att_shootout_penalty(position);
		}
			break;*/
		case DEFEND_AND_ATTCK://防守反击
		{
			att_defend_att_kick_off();
		}
			break;
		default: {
			_formation.update_attack_formation(this);
			att_normal_kick_off(position);
		}
			break;
		}
	} else // -----------------------------防守----------------------------------
	{
		switch (round_typ) {
		/*case PENALTY_KICK_OFF: // 点球
		{
			def_penalty_kick_off(position);
		}
			break;
			*/
		case CORNER_KICK_UP_OFF: // 角球
		case CORNER_KICK_DOWN_OFF: // 角球
		{
			def_corner_kick_off(position, round_typ);
		}
			break;

		case FREE_KICK_OFF: // 任意球
		{
			def_free_kick_off(position);
		}
			break;
			/*
		case SHOOTOUT_PENALTY: // 点球大战
		{
			def_penalty_kick_off(position);
			//				def_shootout_penalty(position);
		}
			break;*/

/*
		case KICK_OFF: 				// 上半场开场
		case MIDDLE_INJURY_KICK: 	// 中场补时
		case MIDDLE_KICK_OFF: 		// 下半场开球
		case END_INJURY_KICK: 		// 下半场补时
*/

/*		case GOAL_KICK_OFF: 		// 进球
			 {
			 _formation.update_defend_formation(this);
			 def_middle_kick_off(position);
			 }
			 break;*/
		case DEFEND_AND_ATTCK://防守反击
		{
			def_defend_att_kick_off(position);
		}
			break;
		default: {
			def_normal_kick_off(position);
			_formation.update_defend_formation(this);
		}
			break;
		}
	}
}

void SoccerTeam::prepare_for_kick_off(void) {
	int kick_typ = this->_match->get_round_typ();

	switch (kick_typ) {
	case KICK_OFF: // 上半场开场
	case MIDDLE_INJURY_KICK: // 中场补时
	case MIDDLE_KICK_OFF: // 下半场开球
	case END_INJURY_KICK: // 下半场补时
	case GOAL_KICK_OFF: // 进球
	{
		_move_define->remove_first();
		add_fake_order();
	}
		break;
	case SHOOTOUT_PENALTY: // 点球大战
	case PENALTY_KICK_OFF: // 点球
	{
		_move_define->remove_first();
		add_penalty_order();
	}
		break;
	case CORNER_KICK_UP_OFF: // 角球
	case CORNER_KICK_DOWN_OFF: // 角球
	{
		_move_define->remove_first();
		add_corner_order(kick_typ);
	}
		break;
	case FREE_KICK_OFF: // 任意球
	{
		_move_define->remove_first();
		add_free_order();
	}
		break;
	case GK_KICK_OFF: // 门将开球
	{

	}
		break;
	case NORMAL_KICK: // 普通
	{
		/*if(false){
			_move_define->remove_first();
			add_normal_order();
		}else{
			_move_define->remove_first();
			add_gk_kick_order();
		}*/
		modifer_move_order_by_gk_skill();
	}
		break;
	case DEFEND_AND_ATTCK://防守反击
	{
		prepare_for_defend_and_attack();
	}
		break;
	default: {
		VLOG(3)<< "prepare_for_kick_off";
	}
	break;
}

this->set_state(AttackingState::alloc());

next_order();
}

void SoccerTeam::next_order(void) {
	if (_move_define == NULL) {
		return;
	}
	_order = _move_define->pop();
	if(_order == NULL){
		return;
	}
	int typ = this->_match->get_round_typ();
	/* 假的move已经结束，开始实际的比赛 */
	if (typ == KICK_OFF // 上半场开场
			|| typ == MIDDLE_INJURY_KICK // 中场补时
			|| typ == MIDDLE_KICK_OFF // 下半场开球
			|| typ == END_INJURY_KICK // 下半场补时
			|| typ == GOAL_KICK_OFF) // 进球
	{
		this->_match->start_real_match();
	}
	VLOG(1)<< "_move_define not error current order is " << _order->behavior;
	VLOG(1) << "!!!!!!!!!!!!!!! current order is " << _order->behavior;

	switch (_order->behavior)
	{
		case ORDER_FORCE_SHOOT: // 强制射门
		{
			PlayerTelegram *tele = new PlayerTelegram(get_id(), _controlling_player->get_id(), TELE_FORCE_SHOOT);
			_match->notify(tele);
		}
		break;
		case ORDER_CORNER:
		{
			//    	PlayerTelegram *tele = new PlayerTelegram(get_id(), _controlling_player->get_id(), TELE_PLAYER_CORNOR);
			//    	_match->notify(tele);
		}
		break;
		case ORDER_FREE:
		{

		}
		break;
		case ORDER_PENALTY:
		{
			PlayerTelegram *tele = new PlayerTelegram(get_id(), _controlling_player->get_id(), TELE_PLAYER_PENALTY);
			_match->notify(tele);
		}
		break;
		case ORDER_SHOOT:
		{
			PlayerTelegram *tele = new PlayerTelegram(get_id(), _controlling_player->get_id(), TELE_PLAYER_SHOOT);
			_match->notify(tele);
		}
		break;
		case ORDER_DRIBBLE:
		{
			PlayerTelegram *tele = new PlayerTelegram(get_id(), _controlling_player->get_id(), TELE_PLAYER_DRIBBLE);
			tele->target_regions = _order->target_regions;
			_match->notify(tele);
		}
		break;
		case ORDER_MOVE:
		{
			//			_supporting_player = get_by_player_id(_order->target_player_id);
			//			PlayerTelegram *tele = new PlayerTelegram(get_id(), _supporting_player->get_id(), TELE_PLAYER_MOVE);
			//			tele->target_regions = _order->target_regions;
			//			_match->notify(tele);
			SoccerPlayer *t_pPlayer = NULL;

			int tar_player_id = -1;

			if (_order->src_player_id != -1)//指定了某个球员插入
			{
				tar_player_id = get_player_pos_by_formation_pos(_order->src_player_id);
				if(tar_player_id != -1) {
					t_pPlayer = get_by_player_id_on_pitch(tar_player_id);
					if (t_pPlayer != NULL && t_pPlayer->is_soccer_player_injs() > 0)
					{
						t_pPlayer = NULL;
					}
				}
			}

			if (t_pPlayer == NULL)
			{
				t_pPlayer = this->select_src_player_by_formation_pos(*_order);
			}
			if (t_pPlayer == NULL)
			{
				Vector2D target_pt = _order->target_regions.center();
				SoccerPlayer *closest_player = NULL;
				int closest_distance = 1000000;
				for (int i = 0; i < get_players_on_pitch_count(); ++i)
				{
					SoccerPlayer *player = get_player_on_pitch(i);
					int distance = (int)player->get_pos().distance(target_pt);
					if ((distance < closest_distance)
							&& (player->get_id() != _controlling_player->get_id())
							&& player->is_soccer_player_injs() == 0)
					{
						closest_distance = distance;
						closest_player = player;
					}
				}
				t_pPlayer = closest_player;
			}
			PlayerTelegram *tele = new PlayerTelegram(get_id(), t_pPlayer->get_id(), TELE_PLAYER_RUN);
			tele->target_regions = _order->target_regions;
			tele->target_id = _order->target_player_id;
			_match->notify(tele);

		}
		break;
		case ORDER_FGK_KICKOFF://门将开球
			{
				Vector2D vec(15*METER_TO_POINT, PITCH_HEIGHT / 2);
				GKKickOffState* state = GKKickOffState::alloc();
				state->_targetVec = vec;
				this->_gk_player->set_state(state);
				_controlling_player = this->_gk_player;
				LOG(INFO)<<"goal keeper kick off";
			}
		break;
		case ORDER_FORCE_CROSS: // 强制长传
		case ORDER_CROSS:
		case ORDER_PASS:
		{
			PlayerTelegram * message = NULL;
			if (_order->behavior == ORDER_PASS)
			{
				message = new PlayerTelegram(get_id(), _controlling_player->get_id(), TELE_PLAYER_PASS);
			}
			else if (_order->behavior == ORDER_FORCE_CROSS)
			{
				message = new PlayerTelegram(get_id(), _controlling_player->get_id(), TELE_FORCE_CROSS);
			}
			else
			{
				message = new PlayerTelegram(get_id(), _controlling_player->get_id(), TELE_PLAYER_CROSS);
			}
			message->target_id = _order->target_player_id;
			message->target_regions = _order->target_regions;

			if (_supporting_player == NULL)
			{
				int tmp_flag = 0;
				if (_order->target_player_id != -1)
				{
					int tar_player_id = get_player_pos_by_formation_pos(_order->target_player_id);
					if (tar_player_id == -1)
					{
						tmp_flag = 1;
					}
					else
					{
						_supporting_player = get_by_player_id_on_pitch(tar_player_id);
						if ((_supporting_player->is_soccer_player_injs() > 0) || (_supporting_player->get_id() == _controlling_player->get_id()))
						{
							_supporting_player = NULL;
							tmp_flag = 1;
						}
						else
						{
							PlayerTelegram *tele = new PlayerTelegram(get_id(), _supporting_player->get_id(), TELE_PLAYER_SUPPORT);
							tele->target_regions = _order->target_regions;
							_match->notify(tele);
						}
					}
				}
				else
				{
					tmp_flag = 1;
				}

				if (tmp_flag == 1)
				{
					Vector2D target_pt = _order->target_regions.center();
					SoccerPlayer *closest_player = NULL;
					//select the one who's formation pos is behind
					closest_player = this->select_player_by_formation_pos(*_order);
					if (closest_player == NULL)
					{
						int closest_distance = 100000;
						for (int i = 0; i < get_players_on_pitch_count(); ++i)
						{
							SoccerPlayer *player = get_player_on_pitch(i);
							int distance = (int)player->get_pos().distance(target_pt);
							if ((distance < closest_distance)
									&& (player->get_id() != _controlling_player->get_id())
									&& player->is_soccer_player_injs() == 0)
							{
								closest_distance = distance;
								closest_player = player;
							}
						}
					}
					_supporting_player = closest_player;
					PlayerTelegram *tele = new PlayerTelegram(get_id(), _supporting_player->get_id(), TELE_PLAYER_SUPPORT);
					tele->target_regions = _order->target_regions;
					_match->notify(tele);
				}
			}
			int speak_type = this->get_coach_speak_type();
			if(speak_type == SPEAK_MORE_CORSS){//十米外的球，全部改为高球
				if(_controlling_player->get_pos().distance(_supporting_player->get_pos()) > 10*METER_TO_POINT){
					message->message = TELE_FORCE_CROSS;
				}
			}else if(speak_type == SPEAK_MORE_PASS){//高球全部改为低球
				LOG(INFO)<<"必须给我传地面球";
				message->message = TELE_PLAYER_PASS;
			}

			_match->notify(message);
			//如果目标已经在目标区域,有20%的几率快速传球
			if(message->target_regions.in(_supporting_player->get_pos())) {
				int rand = RAND_INT%100;
				if(rand < 20) {
					PlayerTelegram * tele_pass = new PlayerTelegram(get_id(), _controlling_player->get_id(), TELE_FORCE_PASS);
					_match->notify(tele_pass);
				}
			}
		}
		break;
		default:
		{

		}
		break;
	}
}

void SoccerTeam::adjust_order(void) {
	switch (_order->behavior) {
	case ORDER_FORCE_SHOOT: // 强制射门
	{

	}
		break;
	case ORDER_CORNER: {

	}
		break;
	case ORDER_FREE: {

	}
		break;
	case ORDER_PENALTY: {

	}
		break;
	case ORDER_FORCE_CROSS: // 强制长传
	case ORDER_CROSS:
	case ORDER_PASS: {
		if (_controlling_player && (!_controlling_player->get_state())) {
			next_order();
		}
	}
		break;
	case ORDER_FGK_KICKOFF:{
		//if (_controlling_player && (!_controlling_player->get_state())) {
			next_order();
		//}
	}
    break;
	case ORDER_DRIBBLE: {
		if (_controlling_player && (!_controlling_player->get_state())) {
			next_order();
		}
	}
		break;
	case ORDER_MOVE: {
		next_order();
	}
		break;
	case ORDER_SHOOT: {

	}
		break;
	default: {

	}
		break;
	}

	//没有事情状态，则回到该状态
	for (int i = 0; i < get_players_on_pitch_count(); ++i) {
		if (_players_on_pitch[i]->get_state() == NULL) {
			_players_on_pitch[i]->set_state(GoHomeState::alloc());
		}
	}
}

void SoccerTeam::awake_frezon_player(void) {
	for (int i = 0; i < get_players_on_pitch_count(); ++i) {
		if (_players_on_pitch[i]->get_state() == NULL) {
			//        	_players[i]->set_state(AreaDefendState::alloc());

			//        	_players[i]->set_state(StopState::alloc());
			_players_on_pitch[i]->set_state(PositionDefendState::alloc());
		}
	}
}

/*
 * fix the whoe team player position by the move their use
 * 1：左路进攻；2：右路进攻；3：中路进攻；4：两翼齐飞；5：混合进攻
 */
void SoccerTeam::fix_formation_by_move_order(int move_typ,
		SoccerPlayer *pPlayer, bool resverse) {
	int modifer = (pPlayer->get_formation_pos() - 1) % 5;
	int distance = g_game_config.get_player_config("modifer_dis");
	int plus_param = 1;
	if (!resverse) {
		plus_param = -1;
	}

	Vector2D tmpVec = pPlayer->get_pos();
	if (move_typ == 1) {
		if (modifer < 4) {
			int distance_to_center = abs(modifer - 4);
			tmpVec.y = tmpVec.y - plus_param * distance * distance_to_center;
		}
	} else if (move_typ == 2) {
		if (modifer > 0) {
			int distance_to_center = modifer;
			tmpVec.y = tmpVec.y + plus_param * distance * distance_to_center;
		}
	} else if (move_typ == 3) {
		if (modifer != 2) {
			int distance_to_center = modifer - 2;
			tmpVec.y = tmpVec.y - plus_param * distance * distance_to_center;
		}
	} else if (move_typ == 4) {
		if (modifer == 1 || modifer == 3) {
			int distance_to_center = modifer - 2;
			tmpVec.y = tmpVec.y + plus_param * distance * distance_to_center;
		}
	}
	//tmpVec.y = tmpVec.y + g_game_config->
	if (tmpVec.y < OUTSIDE_HEIGHT) {
		tmpVec.y = OUTSIDE_HEIGHT;
	}

	if (tmpVec.y > PITCH_HEIGHT - OUTSIDE_HEIGHT) {
		tmpVec.y = PITCH_HEIGHT - OUTSIDE_HEIGHT;
	}

	if (tmpVec.y < g_game_config.get_player_config("modifer_all_pox_y")) {
		tmpVec.y += g_game_config.get_player_config("modifer_all_pox_y");
	}

	pPlayer->set_pos(tmpVec);
}

void SoccerTeam::add_penalty_order(void) {
	_controlling_player = _players_on_pitch[_kick_off_player];
	_controlling_player->set_behavior(ORDER_PENALTY);
	_match->get_ball()->set_pos(B_PENALTY_LOCATION_X, B_PENALTY_LOCATION_Y);
	_match->get_ball()->set_speed(0);
	_match->get_ball()->set_owner(_controlling_player);

	AttackOrder *tmp_order_one = new AttackOrder(ORDER_PENALTY);
	_move_define->add_order_in_front(tmp_order_one);
}

void SoccerTeam::add_free_order(void) {
	_controlling_player = _players_on_pitch[_kick_off_player];
	_controlling_player->set_behavior(ORDER_FREE);
	_match->get_ball()->set_boll_start_pos(_player_pos);
	_match->get_ball()->set_pos(_player_pos);
	_match->get_ball()->set_speed(0);
	_match->get_ball()->set_owner(_controlling_player);

/*	AttackOrder *tmp_order_one = new AttackOrder(ORDER_FORCE_SHOOT);
	_move_define->add_order_in_front(tmp_order_one);*/
	AttackOrder *tmp_order_two = new AttackOrder(ORDER_FREE);
	_move_define->add_order_in_front(tmp_order_two);
}

void SoccerTeam::add_corner_order(int flags) {
	_controlling_player->set_behavior(ORDER_CORNER);
	Vector2D tmp(PITCH_WIDTH - OUTSIDE_HEIGHT - 1, OUTSIDE_WIDTH + 1);

	_match->get_ball()->set_boll_start_pos(tmp);
	double y;
	if (_controlling_player->get_pos().y == 0)
	{
		y = OUTSIDE_HEIGHT + 15;
	}
	else
	{
		y = PITCH_HEIGHT;
	}

	_match->get_ball()->set_pos(PITCH_WIDTH - OUTSIDE_WIDTH, OUTSIDE_HEIGHT);
	_match->get_ball()->set_speed(0);
	_match->get_ball()->set_owner(_controlling_player);

	std::map<int, cornor_player>::const_iterator cit = _cornor_map.find(_cornor_tactical + 3);
	if (cit == _cornor_map.end())
	{
		int tmp = 4;
		cit = _cornor_map.find(tmp);
	}

	if (cit == _cornor_map.end())
	{
		return;
	}

	AttackOrder *tmp_order_one = new AttackOrder(ORDER_FORCE_CROSS);
	tmp_order_one->target_player_id = cit->second.kick_support_player;
	SoccerRegion sr_kick_off_region_1;
	// 左上角 x1，右下角 x2
	sr_kick_off_region_1.x1 = cit->second.x - 0.5 * METER_TO_POINT;
	sr_kick_off_region_1.y1 = cit->second.y - 0.5 * METER_TO_POINT;
	sr_kick_off_region_1.x2 = cit->second.x + 0.5 * METER_TO_POINT;
	sr_kick_off_region_1.y2 = cit->second.y + 0.5 * METER_TO_POINT;

	tmp_order_one->target_regions.push_back(sr_kick_off_region_1);

	AttackOrder *tmp_order_two = new AttackOrder(ORDER_FORCE_SHOOT);
//	AttackOrder *tmp_order_two = new AttackOrder(ORDER_CORNER);
	_move_define->add_order_in_front(tmp_order_two);
	_move_define->add_order_in_front(tmp_order_one);

	_controlling_player->get_match()->set_ball_owner(_controlling_player->get_uid(),_controlling_player->_union_pid
			, _players_on_pitch[cit->second.kick_support_player]->_union_pid
			, 59);
}

void SoccerTeam::add_normal_order(void) {
	_order = _move_define->get_pop();
	if (_order->target_player_id > 22)
	{
		_order->target_player_id = 20;
	}
	//	int const_tmp = 0;
	int temp_flag = -1; /* 哪一个球员不再场 */

	_controlling_player = NULL;
	if (_order->target_player_id != -1)
	{
		_controlling_player = this->get_player_by_formation_pos(_order->target_player_id);
	}

	if(_controlling_player == NULL) {
		std::vector<SoccerPlayer*> tmp;
		for (int i = 0; i < 10; ++i)
		{
			if (_players_on_pitch[i]->is_soccer_player_injs() > 0)
			{
				temp_flag = i;
				continue;
			}
			SoccerPlayer *player = _players_on_pitch[i];
			if (_order->is_target_in_by_formation_pos(player->get_formation_pos()))
			{
				tmp.push_back(player);
			}

		}

		if(tmp.size() != 0) {
			int index_rand = tmp.size();
			_controlling_player = tmp[RAND_INT%index_rand];
		} else {
			int index = 0;
			while(index <10) {
				if(_players_on_pitch[index]->is_soccer_player_injs() == 0) {
					_controlling_player = _players_on_pitch[index];
					break;
				}
				index++;
			}

		}
	}

	_match->get_ball()->set_pos(_controlling_player->get_pos());
	_match->get_ball()->set_speed(0);
	_match->get_ball()->set_owner(_controlling_player);

	_controlling_player->get_match()->set_ball_owner(_controlling_player->get_uid(),_controlling_player->_union_pid, 0, 59);
	AttackOrder *tmp_order_one = new AttackOrder(ORDER_DRIBBLE);
	SoccerRegion sr_kick_off_region_1;
	// 左上角 x1，右下角 x2
	sr_kick_off_region_1.x1 = _controlling_player->get_pos().x + 2 * METER_TO_POINT;
	sr_kick_off_region_1.y1 = _controlling_player->get_pos().y - METER_TO_POINT;
	sr_kick_off_region_1.x2 = _controlling_player->get_pos().x + 6 * METER_TO_POINT;
	sr_kick_off_region_1.y2 = _controlling_player->get_pos().y - 3*METER_TO_POINT;
	tmp_order_one->target_regions.push_back(sr_kick_off_region_1);
	_move_define->add_order_in_front(tmp_order_one);

}

void SoccerTeam::add_gk_kick_order(){
	modifer_move_order_by_gk_skill();
	_order = _move_define->get_pop();
	//_controlling_player = this->_gk_player;

	_match->get_ball()->set_speed(0);
	//_match->get_ball()->set_owner(_controlling_player);

	//_controlling_player->get_match()->set_ball_owner(_controlling_player->get_uid(),_controlling_player->_union_pid, 0, 59);
}

void SoccerTeam::add_fake_order(void) {
	_controlling_player = _players_on_pitch[_kick_off_player];
	_match->get_ball()->set_pos(_controlling_player->get_pos());
	_match->get_ball()->set_speed(0);
	_match->get_ball()->set_owner(_controlling_player);

	_controlling_player->get_match()->set_ball_owner(_controlling_player->get_uid(),_controlling_player->_union_pid, 0, 59);

	AttackOrder *tmp_order_one = new AttackOrder(ORDER_FORCE_CROSS);
	tmp_order_one->target_player_id = _kick_support_player;
	SoccerRegion sr_kick_off_region_1;
	SoccerPlayer *_support_player = _players_on_pitch[_kick_support_player];
	sr_kick_off_region_1.x1 = _support_player->get_pos().x - 0.5 * METER_TO_POINT;
	sr_kick_off_region_1.y1 = _support_player->get_pos().y - 0.5 * METER_TO_POINT;
	sr_kick_off_region_1.x2 = _support_player->get_pos().x + 0.5 * METER_TO_POINT;
	sr_kick_off_region_1.y2 = _support_player->get_pos().y + 0.5 * METER_TO_POINT;

	tmp_order_one->target_regions.push_back(sr_kick_off_region_1);

	AttackOrder *tmp_order_two = new AttackOrder(ORDER_PASS);
	sr_kick_off_region_1.x1 = kick_off_region_2[0] * LATTICE_SIZE_X;
	sr_kick_off_region_1.y1 = kick_off_region_2[1] * LATTICE_SIZE_Y;
	sr_kick_off_region_1.x2 = kick_off_region_2[2] * LATTICE_SIZE_X;
	sr_kick_off_region_1.y2 = kick_off_region_2[3] * LATTICE_SIZE_Y;

	tmp_order_two->target_regions.push_back(sr_kick_off_region_1);

	AttackOrder *tmp_order_three = new AttackOrder(ORDER_PASS);
	sr_kick_off_region_1.x1 = kick_off_region_3[0] * LATTICE_SIZE_X;
	sr_kick_off_region_1.y1 = kick_off_region_3[1] * LATTICE_SIZE_Y;
	sr_kick_off_region_1.x2 = kick_off_region_3[2] * LATTICE_SIZE_X;
	sr_kick_off_region_1.y2 = kick_off_region_3[3] * LATTICE_SIZE_Y;
	tmp_order_three->target_regions.push_back(sr_kick_off_region_1);

	_move_define->add_order_in_front(tmp_order_three);
	_move_define->add_order_in_front(tmp_order_two);
	_move_define->add_order_in_front(tmp_order_one);
}

/* 根据位置选择球员 1:前场,2:中场,3:后场 */
void SoccerTeam::pick_player_by_pos(int player_typ, int *player_ids,
		int &player_count) {
	player_count = 0;
	for (int i = 0; i < PLAYER_COUNT; i++) {
		int pos = this->_players_on_pitch[i]->get_formation_pos();
		if ((player_typ == 1) && (pos <= 10) && (pos >= 2)) {
			player_ids[player_count] = i + 1;
			player_count++;
		} else if ((player_typ == 2) && (pos > 10 && pos <= 25)) {
			player_ids[player_count] = i + 1;
			player_count++;
		} else if ((player_typ == 3) && (pos > 25 && pos <= 34)) {
			player_ids[player_count] = i + 1;
			player_count++;
		}
	}
}

void SoccerTeam::add_player_to_ball(SoccerPlayer *player,
		double distance_to_ball) {
	this->_players_distance_to_ball_map.insert(PAIR_PLAYER_DIS(
			distance_to_ball, player));
}

void SoccerTeam::clear_player_to_ball(void) {
	this->_players_distance_to_ball_map.clear();
}

SoccerPlayer *SoccerTeam::select_player_by_formation_pos(AttackOrder &order) {
	//check anyone formation pos in this area?
	int index[10];
	int count = 0;
	for (int i = 0; i < PLAYER_COUNT; i++) {
		if ((order.is_target_in_by_formation_pos(
				_players_on_pitch[i]->get_formation_pos()))
				&& (_players_on_pitch[i]->get_id()
						!= _controlling_player->get_id())
				&& (_players_on_pitch[i]->is_soccer_player_injs() == 0)) {
			index[count] = i;
			count++;
		}
	}

	if (count == 0) {
		return NULL;
	}

	int r = rand() % count;
	int j = index[r];
	//	VLOG(3) << "_players[j]:" << _players[j]->get_union_pid();
	return _players_on_pitch[j];
}

SoccerPlayer *SoccerTeam::select_src_player_by_formation_pos(AttackOrder &order) {
	//check anyone formation pos in this area?
	int index[10];
	int count = 0;
	for (int i = 0; i < PLAYER_COUNT; i++) {
		if ((order.is_src_in_by_formation_pos(
				_players_on_pitch[i]->get_formation_pos()))
				&& (_players_on_pitch[i]->get_id()
						!= _controlling_player->get_id())
				&& (_players_on_pitch[i]->is_soccer_player_injs() == 0)) {
			index[count] = i;
			count++;
		}
	}

	if (count == 0) {
		return NULL;
	}

	int r = rand() % count;
	int j = index[r];
	//	VLOG(3) << "_players[j]:" << _players[j]->get_union_pid();
	return _players_on_pitch[j];
}

SoccerPlayer *SoccerTeam::get_player_by_formation_pos(int pos) {
	for (int i = 0; i < 10; i++) {
		if (_players_on_pitch[i]->get_formation_pos() == pos) {
			return _players_on_pitch[i];
		}
	}

	return NULL;
}

int SoccerTeam::get_player_pos_by_formation_pos(int pos) {
	for (int i = 0; i < 10; i++) {
		if (_players_on_pitch[i]->get_formation_pos() == pos) {
			return i + 1;
		}
	}

	return -1;
}

SoccerPlayer* SoccerTeam::get_player_by_pos_index(int pos_index){
	if(_gk_player->get_pos_index() == pos_index){
		return _gk_player;
	}

	for (int i = 0; i < 10; i++) {
		if(_players_on_pitch[i] == NULL){
			return NULL;
		}

		if (_players_on_pitch[i]->get_pos_index() == pos_index) {
			return _players_on_pitch[i];
		}
	}
	return NULL;
}

/* 专门用来计算守门员的分值 */
double SoccerTeam::calc_gk_pre(int count, ...) {
	va_list ap; // 初始化指向可变参数列表的指针
	double score = 0;
	va_start(ap, count); // 将第一个可变参数的地址付给ap，即ap指向可变参数列表的开始
	for (int i = 0; i < count; ++i) {
		int attr = va_arg(ap, int);
		double modify = (double) (va_arg(ap, int) / 100);
		score += (_gk_attr[attr] / modify);
	}
	va_end(ap); // ap付值为0，没什么实际用处，主要是为程序健壮性
	//goal_attr
	return score + 50;
}

void SoccerTeam::update_gk_pos(void) {
	switch (this->_match->get_round_typ()) {
	case SHOOTOUT_PENALTY: // 点球大战
	case PENALTY_KICK_OFF: // 点球
	case FREE_KICK_OFF: // 任意球
	{
		return;
	}
		break;
	default: {

	}
		break;
	}

	Vector2D runway;
	if (is_att_side()) {
		runway.x = FORBIDDEN_AREA_WIDTH;
		runway.y = PITCH_HEIGHT / 2;
	} else {
		/* 防守的球员和球对应的场上位置，移动 */
		Vector2D v_Ball = this->get_match()->get_ball()->get_pos();
		if (v_Ball.x > B_FORBIDDEN_AREA_X) /* 进入大禁区 守门员直接出击 */
		{
			runway.x = v_Ball.x + 6;
			runway.y = v_Ball.y;
		} else {
			double x = v_Ball.x / PITCH_WIDTH;
			double y = v_Ball.y / PITCH_HEIGHT;
			double pos_x = B_GOAL_AREA_X + GOAL_AREA_WIDTH * x;
			double pos_y = B_GOAL_AREA_Y + GOAL_AREA_HEIGHT * y;
			runway.x = pos_x;
			runway.y = pos_y;
		}

		if (v_Ball.x >= PITCH_WIDTH - OUTSIDE_WIDTH) {
			runway.x = _gk_player->get_pos().x;
			runway.y = _gk_player->get_pos().y;
		}
	}
	if(is_att_side()){
		if(_gk_player->get_pos().x > FORBIDDEN_AREA_WIDTH){
			return;
		}
	}else{
		if(_gk_player->get_pos().x < A_FORBIDDEN_AREA_X){
			return;
		}
	}

	this->_gk_player->run_to(runway, 0.6);
}

void SoccerTeam::set_cons_effect(int effect_typ, double effect_value) {
	this->_cons_effect_map[effect_typ] = effect_value;
}

double SoccerTeam::get_cons_effect(int effect_typ) {
	if (_cons_effect_map.find(effect_typ) == _cons_effect_map.end()) {
		return 0;
	}

	return _cons_effect_map.find(effect_typ)->second;
}

/* force op player off side */
bool SoccerTeam::can_force_offside(void) {
	return this->_card_can_force_offside;
}

void SoccerTeam::set_can_force_offside(bool b) {
	this->_card_can_force_offside = b;
}

/* avoid self player off side */
bool SoccerTeam::can_avoid_offside(void) {
	return this->_card_can_avoid_offside;
}

void SoccerTeam::set_can_avoid_offside(bool b) {
	this->_card_can_avoid_offside = b;
}
/*
 GK_INT_DEF 				= 100,
 GK_TEC_LONL 			= 101,
 GK_TEC_DISTR 			= 102,
 GK_PHY_STA 				= 103,
 GK_PHY_STR 				= 104,
 GK_SAVE_HAND 			= 105,
 GK_SAVE_STOP 			= 106,
 GK_TEMP_ECCENT 			= 107,
 GK_TEC_CROSS 			= 108,
 GK_TEC_MOVE 			= 109,
 */

/* 计算守门员的进攻属性 */
//TODO 守门员的攻防指数
double SoccerTeam::calc_gk_att_value(void) {
	//TODO 左右脚，cond打折
	double att_value = 60;
	this->_gk_att_value = att_value;
	return att_value;
}

/* 计算守门员的防守属性 */
double SoccerTeam::calc_gk_def_value(void) {
	double def_value = 60;
	this->_gk_def_value = def_value;
	return def_value;
}

double SoccerTeam::calc_team_att_value(int formation_modifer) {
	double att_value = 0;
	for (int i = 0; i < get_players_on_pitch_count(); ++i) {
		att_value += _players_on_pitch[i]->calc_player_att_value();
	}
	att_value += this->calc_gk_att_value();
	this->_att_value = att_value * (1. + _formation_level * formation_modifer
			/ 1000);

	return this->_att_value;
}

double SoccerTeam::calc_team_def_value(int formation_modifer) {
	double def_value = 0;
	for (int i = 0; i < get_players_on_pitch_count(); ++i) {
		def_value += _players_on_pitch[i]->calc_player_def_value();
	}
	def_value += this->calc_gk_def_value();
	this->_def_value = def_value * (1. + _formation_level * formation_modifer
			/ 1000);

	return this->_def_value;
}

SoccerPlayer *SoccerTeam::choose_air_defend_player(const Vector2D& ball_point) {
	if (this->_air_defend_player != NULL) {
		return _air_defend_player;
	}

	SoccerPlayer* rev_player =
			_match->get_attack_team()->get_receveing_player();
	int rev_id = 0;
	if (rev_player != NULL) {
		rev_id = rev_player->get_id();
	}

	std::vector<SoccerPlayer *> player_list;
	std::vector<SoccerPlayer *> player_not_in_dangrou;
	//设定的危险区域
	RegionSet &dangrou = SoccerPitch::forbidden_area_r;
	//获取所有的在防守状态的球员,选择一个离落球点10米最近的球员
	for (int i = 0; i < 10; i++) {
		SoccerPlayer *player = this->get_player_on_pitch(i);
		State<SoccerPlayer> *state = player->get_state();
		if (state->get_type() == TYPE_DefendingState || state->get_type()
				== TYPE_AreaDefendState) {
			//if(player->get_pos().distance(ball_point) < 10 *METER_TO_POINT){
				player_list.push_back(player);
			//}
		}

		if (!dangrou.in(player->get_pos())) {
			player_not_in_dangrou.push_back(player);
		}

	}

	SoccerPlayer *def_player = NULL;
	double distance = 100000;
	std::vector<SoccerPlayer *>::iterator itr = player_list.begin();
	if (player_list.size() != 0) {
		while (itr != player_list.end()) {
			double distance_player = ((*itr)->get_pos()).distance(ball_point);
			if (distance_player <= distance) {
				distance = distance_player;
				def_player = *itr;
			}
			itr++;
		}
	} else {
		itr = player_not_in_dangrou.begin();
		while (itr != player_not_in_dangrou.end()) {
			double distance_player = ((*itr)->get_pos()).distance(ball_point);
			if (distance_player <= distance) {
				distance = distance_player;
				def_player = *itr;
			}
			itr++;
		}
	}

	this->set_air_defend_player(def_player);
	return def_player;
}

		//防守队，选择球员去拦球
void SoccerTeam::make_player_to_defend_air(const Vector2D& target) {
	SoccerPlayer* player = choose_air_defend_player(target);
	if (player != NULL) {
		AirDefendState *state = AirDefendState::alloc();
		state->_targetVec = target;
		player->set_state(state);
		_match->set_event_frames(this->get_team_cid(),player->get_union_pid(), 0, 47);
	}
}

void SoccerTeam::make_player_to_defend_pass(const Vector2D& target) {
	SoccerPlayer* player = choose_air_defend_player(target);
	if (player != NULL) {
		PassDefendState *state = PassDefendState::alloc();
		state->_targetVec = target;
		player->set_state(state);
		_match->set_event_frames(this->get_team_cid(),player->get_union_pid(), 0, 47);
	}
}

void SoccerTeam::coach_speak_effect(int speak_type) {
	if (speak_type >= SPEAK_END) {
		return;
	}
	for(int i=0;i<SPEAK_END;i++){
		this->_speak_effects[speak_type] = false;
	}
	this->_speak_effects[speak_type] = true;
}

void SoccerTeam::modifer_pass_point_coach_speak(Vector2D& vec) {

}


int SoccerTeam::team_ai_auto_use_skill(){
	TacticInfo* info =  pick_skill_to_use_rand();
	if(info == NULL){
		return 0;
	}
	bool rst = use_team_skill(info);
	if(rst){
		return info->tactic_id;
	}else{
		return 0;
	}
}

bool SoccerTeam::use_team_skill(TacticInfo* info){
	int def_energy = info->coast_def_energy;
	int att_energy = info->coast_att_energy;
	//能量值是够的
	if((_team_attack_mp >= att_energy)&&(_team_def_mp >= def_energy)){
		_team_attack_mp -= att_energy;
		_team_def_mp	-= def_energy;
		_last_round_tactic_used = _tactic_used_id;
		_tactic_used_id = info->tactic_id;
		update_team_skill_last_use(info->tactic_id);
		return true;
	}
	return false;
}

//选取发角球的球员
SoccerPlayer* SoccerTeam::pick_corner_ball_player(){
	SoccerPlayer* player = NULL;
	std::vector<SoccerPlayer*>::iterator itr = this->_players_on_pitch.begin();
	double max_free = 0.;
	while(itr != _players_on_pitch.end()){
		if((*itr)->get_attr(FREE_KICK) >= max_free){
			player = *itr;
			max_free = (*itr)->get_attr(FREE_KICK);
		}
		itr++;
	}
	return player;
}


int SoccerTeam::select_move_by_tactic_id(int tactic_id){
	int move_id = CGameConfigManager::GetInstance()->GetMoveRandomByTactic(tactic_id);
	if (move_id <= 0) {
		move_id = 3;
	}

	this->setTeamMode(GOD_MODE);
	VLOG(1)<<"使用技能！！！！！进入上帝模式。。";
	this->set_current_move_card_id(move_id);
	return move_id;
}
int SoccerTeam::use_team_skill() {
	LOG(INFO)<<"__________________________________";
	double value = 0.;
	double skill_value = RAND_DBL;
	int tactic_id = 0;
	_tactic_used_id = 0;
	std::map<int, TeamSkill>::iterator itr = this->_team_skills.begin();
	double temp = 0.;
	while (itr != _team_skills.end()) {
		temp = itr->second.chance;
		value += temp / 100.;
		if (value > skill_value) {
			//使用这个技能
			tactic_id = itr->second.tactic_id;
			_tactic_used_id = tactic_id;
		}
		itr++;
	}

	if (tactic_id == 0) {
		return -1;
	}

	int move_id = CGameConfigManager::GetInstance()->GetMoveRandomByTactic(tactic_id);
	if (move_id <= 0) {
		return -1;
	}

	switch (tactic_id) {
	case TACTIC_MIDDLE_PUSH: //中路推进
	case TACTIC_LEFT_ATTACK: //左边路强攻
	case TACTIC_RIGHT_ATTACK: //右边路强攻
	case TACTIC_BOTH_ATTACK: //两翼齐飞
	case TACTIC_ALL_ATTACK: //全线进攻
	case TACTIC_ALL_DEFEND: //龟缩防守
	case TACTIC_FRONT_TACLE: //前场逼抢
	case TACTIC_BACK_INSERT: //后排插上
	case TACTIC_QUICK_STRIKE_BACK: //快速反击
	case TACTIC_MIDDLE_CTRL: //中场控球
	case TACTIC_FAKE_OUT: //声东击西
	case TACTIC_STONE_STRIKE_BACK: //混凝土防反
	case TACTIC_UNIVERSE_CTRL: //宇宙队式控球
	case TACTIC_GALAXY_QUICK_ATTACK: //银河队式快攻
	case TACTIC_ATT_DEF: //全攻全守
	{
		VLOG(1)<<"使用技能！！！！！进入上帝模式。。";
		this->setTeamMode(GOD_MODE);
		this->set_current_move_card_id(move_id);
		return move_id;
	}
	break;
	default:
		VLOG(2)<<"Nice body!!";
}
return -1;

}

void SoccerTeam::prepare_for_defend_and_attack() {
	SoccerPlayer* player = get_player_on_pitch_by_union_id(get_match()->get_union_pid());
	//如果选不到人，就随便指定一个中场
	if(player == NULL){
		//取得中场球员
		player = rand_pick_middle_player();
	}
	pick_suitable_order(player);
}

void SoccerTeam::pick_suitable_order(SoccerPlayer* ctrl_player) {
	//获取控球的队员是前锋还是后卫还是中场
	int ctrl_player_pos =	check_position(ctrl_player->get_formation_pos());
	//分段取比较合适的进攻的order

	std::list<AttackOrder*> &list = _move_define->get_all_order_list();
	int total_order_count = list.size();
	int	order_pick_index = total_order_count * (3-ctrl_player_pos)/5;

	for (int cout = 0; cout < total_order_count; cout++) {
		AttackOrder* order = _move_define->pop();
		if (order->behavior == 4) {//跑位不管，继续跑

		} else {
			if (cout >= order_pick_index) {//
				this->_order = order;

				SoccerBall *ball = this->get_match()->get_ball();
				ball->set_z(0);
				ball->set_owner(ctrl_player);
				ctrl_player->set_state(NULL);
				_receiving_player = NULL;
				_controlling_player = ctrl_player;
				return;
			}
		}
	}

/*
	if (check_order_suitable(ctrl_player)) {
		for (int cout = 0; cout < total_order_count; cout++) {
			AttackOrder* order = _move_define->pop();
			if (order->behavior == 4) {//跑位不管，继续跑

			} else {
				if (order->target_regions.in(ctrl_player->get_pos())) {//
					this->_order = order;
				}
			}
		}
	} else {
		int index = get_order_cloest(ctrl_player);
		for (int cout = 0; cout < total_order_count; cout++) {
			AttackOrder* order = _move_define->pop();
			if (index == cout) {
				this->_order = order;
			}
		}
	}*/
}

int SoccerTeam::get_order_cloest(SoccerPlayer* ctrl_player){
	std::list<AttackOrder*> &list = _move_define->get_all_order_list();
	std::list<AttackOrder*>::iterator itr = list.begin();
	int total_order_count = list.size();
	int index = 0;
	double distance = 100000.;
	for(int cout=0;cout<total_order_count;cout++){
		if((*itr)->behavior != 4){
			double temp = (*itr)->target_regions.center().distance(ctrl_player->get_pos());
			if(distance > temp){
				index = cout;
				distance = temp;
			}
		}
		itr++;
	}
	return index;
}


bool SoccerTeam::check_order_suitable(SoccerPlayer* ctrl_player){
	std::list<AttackOrder*> &list = _move_define->get_all_order_list();
	std::list<AttackOrder*>::iterator itr = list.begin();
	int total_order_count = list.size();
	for(int cout=0;cout<total_order_count;cout++){
		if((*itr)->target_regions.in(ctrl_player->get_pos())){
			return true;
		}
		itr++;
	}
	return false;
}

void SoccerTeam::init_def_formation_before(int position[]){
	int backline = (position[0] - 1) / 5;
		static int
				line_number[41] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
						0, 0, 0, 0 };
		Player_Formation_Cell cell;
		for (int i = 0; i < 10; i++) {
			cell.x_cell = (position[i] - 1) / 5;
			cell.y_cell = (position[i] - 1) % 5;
			if (backline <= cell.x_cell) {
				backline = cell.x_cell;
			}
			this->_line_number[cell.x_cell] = this->_line_number[cell.x_cell] + 1;
			line_number[position[i]] = position[i];
			_players_on_pitch[i]->_row_index = cell.x_cell;
		}
		this->_back_line = backline;
		//計算在y方向的順序
		for (int i = 0; i < 10; i++) {
			int index = 0;
			int pos = _players_on_pitch[i]->get_formation_pos();
			for (int j = (pos - pos % 5 + 1); j < (pos - pos % 5 + 5 + 1); j++) {
				if (line_number[j] != 0) {
					if (line_number[j] > pos) {
						index++;
					}
				}
			}
			_players_on_pitch[i]->_column_index = index;
		}

		double dis_between_players = 13;

		//站在中圈弧的球员的数量
		int player_number = 0;
		for (int i = 0; i < 10; i++) {
			Vector2D vecPos;
			vecPos.x = (DEFEND_LINE - ((backline - (position[i] - 1) / 5) * 10
					* METER_TO_POINT));

			vecPos.y = (PITCH_HEIGHT - (this->_line_number[(position[i] - 1) / 5]
					- 1) * dis_between_players * METER_TO_POINT) / 2
					+ _players_on_pitch[i]->_column_index * dis_between_players
							* METER_TO_POINT;
			if (position[i] % 5 == 1 || position[i] % 5 == 0) {
				vecPos.x = vecPos.x - 5 * METER_TO_POINT;
			}
			_players_on_pitch[i]->set_state(AreaDefendState::alloc());

			//赋值初始化站位
			_players_on_pitch[i]->_init_pos = vecPos;
			Vector2D tmpVector = _players_on_pitch[i]->get_pos();
			tmpVector.x = tmpVector.x - 5;
			_players_on_pitch[i]->heading_to(tmpVector);
		}
}

void SoccerTeam::get_top_shooter(std::vector<SoccerPlayer*>& player_list,int top_number){
	std::vector<SoccerPlayer*> all_player;
	all_player.assign(_players_on_pitch.begin(),_players_on_pitch.end());
	std::sort(all_player.begin(),all_player.end(),cmp_shooter_sort);
	player_list.assign(all_player.begin(),all_player.begin()+top_number);
	vector<SoccerPlayer*>::iterator itr = player_list.begin();
	while(itr != player_list.end()){
		VLOG(0)<<"前5名射门能力的人"<<(*itr)->get_union_pid()<<":"<<(*itr)->get_attr(ATT_SHOOT) * 7  + (*itr)->get_attr(PENALTY)*3;
		itr++;
	}
}


void SoccerTeam::modifer_move_order_to_front(){
	//找到射门的Order
	while(_move_define->get_pop()->behavior != ORDER_SHOOT){
		_move_define->pop();
	}
	AttackOrder *order = new AttackOrder(ORDER_CROSS);
	order->behavior = ORDER_CROSS;
	order->src_player_id = -1;
	order->src_region_lt = 0;
	order->src_region_rb = 0;
	order->target_player_id = 3;
	order->target_region_lt = 2;
	order->target_region_rb = 14;
	this->_move_define->add_order_in_front(order);
	AttackOrder *order_gk = new AttackOrder(ORDER_FGK_KICKOFF);
	this->_move_define->add_order_in_front(order_gk);
}

void SoccerTeam::modifer_move_order_to_back(){

	//(position == 21) || (position >= 25 && position <= 34)
	AttackOrder *order = new AttackOrder(ORDER_PASS);
	_order = _move_define->get_pop();

	if (_order->src_player_id != -1)
	{
		order->target_player_id = _order->src_player_id;
	}else{
		if(order->target_player_id != -1){
			int target_player_id = 0;
			while(target_player_id == 0){
				target_player_id = RAND_ARRAY(11,21,25,26,27,28,29,30,31,32,33,34);
				if(target_player_id == order->target_player_id){
					target_player_id = 0;
				}else{
					SoccerPlayer* target_player = this->get_player_by_formation_pos(target_player_id);
					if(target_player == NULL){
						target_player_id = 0;
					}
				}

			}
			order->target_player_id = target_player_id;
		}else{
			int target_player_id = 0;
			while(target_player_id == 0){
				target_player_id = RAND_ARRAY(11,21,25,26,27,28,29,30,31,32,33,34);
				SoccerPlayer* target_player = this->get_player_by_formation_pos(target_player_id);
				if(target_player == NULL){
					target_player_id = 0;
				}
			}
			order->target_player_id = target_player_id;
		}
	}


	order->behavior = ORDER_PASS;
	order->src_player_id = -1;
	order->src_region_lt = 0;
	order->src_region_rb = 0;
	this->_move_define->add_order_in_front(order);
	AttackOrder *order_gk = new AttackOrder(ORDER_FGK_KICKOFF);
	this->_move_define->add_order_in_front(order_gk);
}


//根据球员的技能决定对move的修改,和对方的门将进行比较。如果成功传到前场，失败或者在某一定的区域则到后场3
//根据守门员开球的技能，修改整场的进攻战术，前场接球，直接射门.
void SoccerTeam::modifer_move_order_by_gk_skill(){
	int rand_index = RAND_INT%3;
	SoccerPlayer* player = this->_gk_player;
	if(rand_index == 0){
		int rst = player->check_will_use_gk_skill();
		if(rst != -1){//直接前场
			modifer_move_order_to_front();
		}else{//后场
			modifer_move_order_to_back();
		}
	}else{
		modifer_move_order_to_back();
	}
	_match->get_ball()->set_owner(player);
	//player->dump_player_skill_info();
	//	LOG(INFO)<<
}

bool SoccerTeam::check_will_unit_defend(){
	std::vector<SoccerPlayer*> player_vec;
	SoccerPlayer* ball_owner = this->_match->get_ball()->get_owner();
	if(ball_owner == NULL){
		return false;
	}
	//查看是否有2个人在10M范围，查看是否进入联防
	std::vector<SoccerPlayer*> vec;
	for(int count=0;count < _players_on_pitch.size();count++){
		SoccerPlayer* player = _players_on_pitch[count];
		if(player->get_pos().distance(ball_owner->get_pos()) < 10 * METER_TO_POINT){
			vec.push_back(player);
		}
		//如果已经有人进入了联防，就false
		if((player->get_state() != NULL)&&(player->get_state_type() == TYPE_UnitDefendState)){
			return false;
		}
	}

	//数量小于2个人，不发动
	if(vec.size() < 2){
		return false;
	}

	//如果球员技能有联防技能,判断触发
	std::vector<SoccerPlayer*>::iterator itr = vec.begin();
	SoccerPlayer* player_skill_user = NULL;
	while(itr != vec.end()){
		if(player_skill_user == NULL){
			int skill_id = (*itr)->check_skill_can_use(30);
			if(skill_id != -1){
				LOG(INFO)<<"player "<<(*itr)->get_union_pid()<<"使用联防技能";
				player_skill_user = *itr;
			}
		}
		itr++;
	}

	if(player_skill_user == NULL){
		return false;
	}

	//选取两个人来包夹，其中一个包括使用技能的人.
	player_vec.push_back(player_skill_user);
	itr = vec.begin();
	while(itr != vec.end()){
		if((*itr)->get_union_pid() != player_skill_user->get_union_pid()){
			player_vec.push_back(*itr);
			break;
		}
		itr++;
	}

	//选取出来的人，进入unitdefendstate
	UnitDefendState* state_1 = UnitDefendState::alloc();
	state_1->_target_player = ball_owner;
	Vector2D cmp_vec;
	cmp_vec.x = 5;
	cmp_vec.y = 5;
	state_1->_cmp_target_vec = cmp_vec;
	player_vec[0]->set_state(state_1);

	cmp_vec.y = -5;
	UnitDefendState* state_2 = UnitDefendState::alloc();
	state_2->_cmp_target_vec = cmp_vec;
	player_vec[1]->set_state(state_2);
	return true;
}










