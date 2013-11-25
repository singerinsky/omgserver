#include "../common/head.h"

#include "soccer_config.h"
#include "soccer_formation.h"
#include "soccer_match.h"

SoccerRegion SoccerFormation::_region[PITCH_COUNT];
double SoccerFormation::_ball_limit_up_x = 0.75 * PITCH_WIDTH;
double SoccerFormation::_ball_limit_down_x = 0.2 * PITCH_WIDTH;
double SoccerFormation::_ball_limit_up_y = 0.75 * PITCH_HEIGHT;
double SoccerFormation::_ball_limit_down_y = 0.25 * PITCH_HEIGHT;

double SoccerFormation::_x1_limit_up = PITCH_WIDTH * 0.75;
double SoccerFormation::_x2_limit_up = PITCH_WIDTH;
double SoccerFormation::_x1_limit_down = 0;
double SoccerFormation::_x2_limit_down = 0.25 * PITCH_WIDTH;

double SoccerFormation::_y1_limit_up = 0.8 * PITCH_HEIGHT;
double SoccerFormation::_y2_limit_up = PITCH_HEIGHT;
double SoccerFormation::_y1_limit_down = 0;
double SoccerFormation::_y2_limit_down = 0.2 * PITCH_HEIGHT;

double SoccerFormation::_pitch_width = PITCH_WIDTH;
double SoccerFormation::_pitch_height = PITCH_HEIGHT;

void SoccerFormation::init_pitch_region(void) {
	_region[0] = SoccerRegion(12, 0, 0, 1);
	_region[1] = SoccerRegion(12, 1, 14, 3);
	_region[2] = SoccerRegion(12, 3, 14, 7);
	_region[3] = SoccerRegion(12, 7, 14, 9);
	_region[4] = SoccerRegion(12, 9, 0, 10);

	_region[5] = SoccerRegion(11, 0, 12, 2);
	_region[6] = SoccerRegion(11, 2, 12, 4);
	_region[7] = SoccerRegion(11, 4, 12, 6);
	_region[8] = SoccerRegion(11, 6, 12, 8);
	_region[9] = SoccerRegion(11, 8, 12, 10);

	_region[10] = SoccerRegion(9, 0, 11, 2);
	_region[11] = SoccerRegion(9, 2, 11, 4);
	_region[12] = SoccerRegion(9, 4, 11, 6);
	_region[13] = SoccerRegion(9, 6, 11, 8);
	_region[14] = SoccerRegion(9, 8, 11, 10);

	_region[15] = SoccerRegion(7, 0, 9, 2);
	_region[16] = SoccerRegion(7, 2, 9, 4);
	_region[17] = SoccerRegion(7, 4, 9, 6);
	_region[18] = SoccerRegion(7, 6, 9, 8);
	_region[19] = SoccerRegion(7, 8, 9, 10);

	_region[20] = SoccerRegion(5, 0, 7, 2);
	_region[21] = SoccerRegion(5, 2, 7, 4);
	_region[22] = SoccerRegion(5, 4, 7, 6);
	_region[23] = SoccerRegion(5, 6, 7, 8);
	_region[24] = SoccerRegion(5, 8, 7, 10);

	_region[25] = SoccerRegion(3, 0, 5, 2);
	_region[26] = SoccerRegion(3, 2, 5, 4);
	_region[27] = SoccerRegion(3, 4, 5, 6);
	_region[28] = SoccerRegion(3, 6, 5, 8);
	_region[29] = SoccerRegion(3, 8, 5, 10);

	_region[30] = SoccerRegion(2, 0, 3, 1);
	_region[31] = SoccerRegion(2, 1, 3, 3);
	_region[32] = SoccerRegion(2, 3, 3, 7);
	_region[33] = SoccerRegion(2, 7, 3, 9);
	_region[34] = SoccerRegion(2, 9, 3, 10);

	for (int i = 0; i < PITCH_COUNT; ++i) {
		_region[i].x1 = _region[i].x1 * LATTICE_SIZE_X;
		_region[i].x2 = _region[i].x2 * LATTICE_SIZE_X;
		_region[i].y1 = _region[i].y1 * LATTICE_SIZE_Y;
		_region[i].y2 = _region[i].y2 * LATTICE_SIZE_Y;
	}
}

Vector2D SoccerFormation::get_region_pos(int formation_pos_id) {
	return _region[formation_pos_id - 1].center();
}

void SoccerFormation::update_defend_formation(SoccerTeam *team) {
	SoccerBall *ball = team->get_match()->get_ball();

	int ball_x = (int) ball->get_pos().x;
	int ball_y = (int) ball->get_pos().y;

	/* 后防线的基準座標 */
	double index_x;
	/* 是否已經進入禁區了 */
	int is_hot = 0;
	/* 球在大禁區的之內 */
	if (ball_x <= A_FORBIDDEN_AREA_X) {
		index_x = MIDDLE_CIRCLE_B;
	} else if (ball_x <= (39.5 * 12) && ball_x > A_FORBIDDEN_AREA_X) {
		index_x = DEFEND_LINE_SEC;
	} else if (ball_x > (39.5 * 12) && ball_x <= DEFEND_LINE_SEC) {
		index_x = (((ball_x - 39.5 * 12) / (26 * 12)) * ((B_FORBIDDEN_AREA_X
				- 3 * METER_TO_POINT) - DEFEND_LINE_SEC)) + DEFEND_LINE_SEC;
	} else if (ball_x > DEFEND_LINE_SEC && ball_x <= B_FORBIDDEN_AREA_X) {
		index_x = (((ball_x - DEFEND_LINE_SEC) / (B_FORBIDDEN_AREA_X
				- DEFEND_LINE_SEC)) * (6 * METER_TO_POINT))
				+ B_FORBIDDEN_AREA_X;
		is_hot = 1;
	} else if (ball_x > B_FORBIDDEN_AREA_X && ball_x <= PITCH_WIDTH) {
		index_x = PITCH_WIDTH - (ball_x - B_FORBIDDEN_AREA_X) / (PITCH_WIDTH
				- B_FORBIDDEN_AREA_X) * 11 * METER_TO_POINT;
		is_hot = 1;
	}
	if(index_x > (PITCH_WIDTH - OUTSIDE_WIDTH - 2 * METER_TO_POINT)){
		index_x = PITCH_WIDTH - OUTSIDE_WIDTH - 2 * METER_TO_POINT;
	}

	
	if(index_x < (MIDDLE_CIRCLE_B)){
		index_x = MIDDLE_CIRCLE_B;
	}


	int mod_y = 0;
	mod_y = (((ball_y - PITCH_HEIGHT / 2) * 216) / (PITCH_HEIGHT / 2));

	int ball_left_or_right = 0;
	if (ball_y < A_FORBIDDEN_AREA_Y) {
		ball_left_or_right = 1;
	} else if (ball_y > (A_GOAL_HEIGHT + FORBIDDEN_AREA_HEIGHT / 2)) {
		ball_left_or_right = -1;
	}

	int player_dis = 10;
	//TODO 如果球队喊话中有散开的话,三条线拉开12米(不影响进攻），横向7米
	if(team->check_coach_speak(SPEAK_MORE_SPACE)){
			player_dis = player_dis + 12/3;
	}else if(team->check_coach_speak(SPEAK_LESS_SPACE)){//三条线拉开8米（不影响进攻），横向5米
			player_dis = player_dis + 8/3;
	}

	for (int i = 0; i < team->get_players_on_pitch_count(); ++i) {
		SoccerPlayer *pPlayer = team->get_player_on_pitch(i);

		int region_id = _position[i] - 1;
		SoccerRegion region = _region[region_id];
		int region_width = (int) (region.x2 - region.x1);
		int region_height = (int) (region.y2 - region.y1);

		SoccerRegion tmpRegion;
		Vector2D vecPos;
		vecPos.x = (index_x - ((team->getBackLine()
				- (pPlayer->get_formation_pos() - 1) / 5) * player_dis
				* METER_TO_POINT));
		vecPos.y = pPlayer->_init_pos.y + mod_y;

		if (ball_left_or_right == 0) {
			if (pPlayer->get_formation_pos() == 26
					|| pPlayer->get_formation_pos() == 30) {
				vecPos.x = vecPos.x - 2 * METER_TO_POINT;
			}
		} else if (ball_left_or_right == 1) {
			if (pPlayer->get_formation_pos() % 5 == 1) {
				vecPos.x = vecPos.x - 5 * METER_TO_POINT;
			}
		} else if (ball_left_or_right == -1) {
			if (pPlayer->get_formation_pos() % 5 == 0) {
				vecPos.x = vecPos.x - 5 * METER_TO_POINT;
			}
		}

		/* 假如突入大禁區，像中間收縮 */
		if (is_hot == 1) {
			if (pPlayer->get_formation_pos() == 26) {
				vecPos.y = vecPos.y - 8 * METER_TO_POINT;
			} else if (pPlayer->get_formation_pos() == 27) {
				vecPos.y = vecPos.y - 5 * METER_TO_POINT;
			} else if (pPlayer->get_formation_pos() == 28) {
				vecPos.y = vecPos.y + 0 * METER_TO_POINT;
			} else if (pPlayer->get_formation_pos() == 29) {
				vecPos.y = vecPos.y + 5 * METER_TO_POINT;
			} else if (pPlayer->get_formation_pos() == 30) {
				vecPos.y = vecPos.y + 8 * METER_TO_POINT;
			}
		}

		region.x1 = vecPos.x - region_width / 2;
		region.x2 = vecPos.x + region_width / 2;

		region.x1 = vecPos.x - region_width / 2;
		region.x2 = vecPos.x + region_width / 2;

		region.y1 = vecPos.y - region_height / 2;
		region.y2 = vecPos.y + region_height / 2;
		region.fix_to_pitch();
		pPlayer->set_home(region);

		tmpRegion.x1 = pPlayer->get_pos().x - 80;
		tmpRegion.x2 = pPlayer->get_pos().x + 30;
		tmpRegion.y1 = pPlayer->get_pos().y - 1 * 60;
		tmpRegion.y2 = pPlayer->get_pos().y + 1 * 60;
		tmpRegion.fix_to_pitch();
		team->get_player_on_pitch(i)->set_markArea(tmpRegion);

		tmpRegion.x1 = pPlayer->get_pos().x - 17 * METER_TO_POINT;
		tmpRegion.x2 = pPlayer->get_pos().x + 3 * METER_TO_POINT;
		tmpRegion.y1 = pPlayer->get_pos().y - 7 * METER_TO_POINT;
		tmpRegion.y2 = pPlayer->get_pos().y + 7 * METER_TO_POINT;
		tmpRegion.fix_to_pitch();
		team->get_player_on_pitch(i)->set_mindArea(tmpRegion);
	}
	player_modifer_formation_speak(team);
}

void SoccerFormation::team_modifer_formation_speak(SoccerTeam* team){
	int speak_type = team->get_coach_speak_type();	
	if(speak_type == -1){//没有喊话内容
		return;
	}/*
	switch(speak_type){
		case    SPEAK_MORE_PASS:		
		case	SPEAK_MORE_CORSS:
		case	SPEAK_MORE_EMPTY_PASS:
		case	SPEAK_MORE_FOOT_PASS:
		case	SPEAK_MORE_SPACE:
		case	SPEAK_LESS_SPACE:
		case	SPEAK_ATTACK_ATTACK:
		case	SPEAK_DEFEND_ATTACK:
		case	SPEAK_CRAZY_TACKLE:
		case	SPEAK_HOLD:
		case	SPEAK_KILL_KICK:
		case	SPEAK_GENTLEMEN:
		default:
				


	}
	
*/

}


double SoccerFormation::get_back_x(double tmp, double x)
{
	if (tmp > PITCH_WIDTH / 2)
	{
		if (x < tmp)
		{
			return x - tmp;
		}
	} else {
		if (x > tmp) {
			return x - tmp;
		}
	}

	return 0;
}

void SoccerFormation::update_attack_formation(SoccerTeam *team) {
//	static double x_offset_factor[] = { 0, 0.5, 0.5, 0.5, 0, 0.8, 0.75, 0.75, 0.75,
//			0.8, 1, 0.5, 0.6, 0.5, 1, 1, 1.2, 1.2, 1.2, 1, 1.75, 0.75, 0.75,
//			0.75, 1.75, 1.5, 0.5, 0.5, 0.5, 1.5, 0, 0.5, 0.5, 0.5, 0 };
	static double x_offset_factor[] = { 0, 0.25, 0.25, 0.25, 0,
										0.4, 0.3, 0.3, 0.3, 0.4,
										0.5, 0.25, 0.3, 0.25, 0.5,
										0.5, 0.5, 0.5, 0.5, 0.5,
										1, 0.75, 0.75,0.75, 1,
										1.5, 0.5, 0.5, 0.5, 1.5,
										0, 0.5, 0.5, 0.5, 0 };

	SoccerBall *ball = team->get_match()->get_ball();
	int ball_x = (int) ball->get_pos().x;
	int ball_y = (int) ball->get_pos().y;

	double tmp = PITCH_WIDTH / 2;
	//拿到最后一个后卫线
	for (int i = 0; i < team->get_players_on_pitch_count(); ++i) {
		SoccerPlayer *pPlayer = team->get_player_on_pitch(i);
		if (_position[i] >= 27 && _position[i] <= 29) {
			if (tmp > pPlayer->get_pos().x) {
				tmp = pPlayer->get_pos().x;
			}
		} else if ((_position[i] >= 32 && _position[i] <= 34)) {
			if (tmp > pPlayer->get_pos().x) {
				tmp = pPlayer->get_pos().x;
			}
		}
	}

	double dx = ball_x - tmp;//ball to last defense line
	double dy = ball_y - PITCH_HEIGHT / 2;

	for (int i = 0; i < team->get_players_on_pitch_count(); ++i) {
		SoccerPlayer *pPlayer = team->get_player_on_pitch(i);
		int region_id = _position[i] - 1;
		SoccerRegion region = _region[region_id];
		int region_width = (int) (region.x2 - region.x1);
		int region_height = (int) (region.y2 - region.y1);

		region.x1 += (dx * x_offset_factor[region_id]);
		region.x2 += (dx * x_offset_factor[region_id]);

		if (_position[i] == 21) {
			region.x1 = tmp + 15 * METER_TO_POINT;
			region.x2 = tmp + 25 * METER_TO_POINT;
		} else if (_position[i] == 25) {
			region.x1 = tmp + 15 * METER_TO_POINT;
			region.x2 = tmp + 25 * METER_TO_POINT;
		} else if (_position[i] == 26) {
			region.x1 = tmp + 10 * METER_TO_POINT;
			region.x2 = tmp + 20 * METER_TO_POINT;
		} else if (_position[i] == 30) {
			region.x1 = tmp + 10 * METER_TO_POINT;
			region.x2 = tmp + 20 * METER_TO_POINT;
		}

		if (region.x2 > PITCH_WIDTH - OUTSIDE_WIDTH) {
			region.x2 = PITCH_WIDTH - OUTSIDE_WIDTH;
			region.x1 = region.x2 - region_width;
		} else if (region.x1 < OUTSIDE_WIDTH) {
			region.x1 = OUTSIDE_WIDTH;
			region.x2 = region.x1 + region_width;
		}

		//进攻球员根据move typ偏移
		fix_formation_by_move_order(pPlayer->get_formation_pos(), region);

		//120是球员之间间距的合理值
		region.y1 += ((dy / (PITCH_HEIGHT / 2)) * 100);
		region.y2 += ((dy / (PITCH_HEIGHT / 2)) * 100);

		if (region.y2 > PITCH_HEIGHT - OUTSIDE_HEIGHT) {
			region.y2 = PITCH_HEIGHT - OUTSIDE_HEIGHT;
			region.y1 = region.y2 - region_height;
		} else if (region.y1 < OUTSIDE_HEIGHT) {
			region.y1 = OUTSIDE_HEIGHT;
			region.y2 = region.y1 + region_height;
		}
		double y = pPlayer->get_middle_modifer();
		region.y1 += y;
		region.y2 += y;

		pPlayer->set_home(region);
	}

	player_modifer_formation_speak(team);
}

void SoccerFormation::fix_formation_by_move_order(int formation_pos,
		SoccerRegion &home) {
	int modifer = (formation_pos - 1) % 5;
	int distance = g_game_config.get_player_config("modifer_dis");
	int plus_param = 1;

	if (_move_typ == 1) {
		if (modifer < 4) {
			int distance_to_center = abs(modifer - 4);
			home.y1 = home.y1 - plus_param * distance * distance_to_center;
			home.y2 = home.y2 - plus_param * distance * distance_to_center;
		}
	} else if (_move_typ == 2) {
		if (modifer > 0) {
			int distance_to_center = modifer;
			home.y1 = home.y1 + plus_param * distance * distance_to_center;
			home.y2 = home.y2 + plus_param * distance * distance_to_center;
		}
	} else if (_move_typ == 3) {
		if (modifer != 2) {
			int distance_to_center = modifer - 2;
			home.y1 = home.y1 - plus_param * distance * distance_to_center;
			home.y2 = home.y2 - plus_param * distance * distance_to_center;
		}
	} else if (_move_typ == 4) {
		if (modifer == 1 || modifer == 3) {
			int distance_to_center = modifer - 2;
			home.y1 = home.y1 + plus_param * distance * distance_to_center;
			home.y2 = home.y2 + plus_param * distance * distance_to_center;
		}
	}
	//tmpVec.y = tmpVec.y + g_game_config->

	if (home.y1 < g_game_config.get_player_config("modifer_all_pox_y")) {
		home.y1 += g_game_config.get_player_config("modifer_all_pox_y");
	}

	if (home.y2 < g_game_config.get_player_config("modifer_all_pox_y")) {
		home.y2 += g_game_config.get_player_config("modifer_all_pox_y");
	}

	home.fix_to_pitch();
}

void SoccerFormation::fix_formation_middle_empty(SoccerTeam *team) {
	double middle_mod = g_game_config.get_player_config("middle_modifer");
	//every line player count
	for (int i = 0; i < 10; i++) {
		int pos = this->_position[i] - 1;
		int index = pos % 5;
		if (index == 1) {
			if (team->get_player_by_formation_pos(pos + 2) == NULL) {
				SoccerPlayer *pPlayer = NULL;
				pPlayer = team->get_player_by_formation_pos(pos + 1);
				if (pPlayer != NULL) {
					double tmp_middle_mod = 0 - middle_mod;
					pPlayer->set_middle_modifer(tmp_middle_mod);
				}

				pPlayer = team->get_player_by_formation_pos(pos + 3);
				if (pPlayer != NULL) {
					pPlayer->set_middle_modifer(middle_mod);
				}
			}
		}
	}
}

int SoccerFormation::checkPointRegionIndex(Vector2D& vec) {

	for (int i = 0; i < PITCH_COUNT; ++i) {
		if (_region[i].in(vec)) {
			return i;
		}
	}
	return -1;
}

void SoccerFormation::player_modifer_formation_speak(SoccerTeam* team) {
	int speak_type = team->get_coach_speak_type();
	if (speak_type == -1) {//没有喊话内容
		return;
	}
	bool is_att_team = team->is_att_side();
	switch (speak_type) {
	case SPEAK_MORE_PASS: {
		double x = 3 * METER_TO_POINT;
		if (is_att_team) {
			this->modifer_whole_player_home_area(team, -x, 0);
		} else {
			this->modifer_whole_player_home_area(team, x, 0);
		}

	}
		break;
	case SPEAK_MORE_CORSS: {
		double x = 3 * METER_TO_POINT;
		if (is_att_team) {
			modifer_whole_player_home_area(team, x, 0);
		}
	}
		break;
	case SPEAK_MORE_EMPTY_PASS:
		break;
	case SPEAK_MORE_FOOT_PASS:
		break;
	case SPEAK_WAIT_FOR:
		break;
	case SPEAK_MORE_SPACE:
		break;
	case SPEAK_LESS_SPACE:
		break;
	case SPEAK_KILL_KICK:
		break;
	case SPEAK_GENTLEMEN:
		break;
	case SPEAK_ATTACK_ATTACK:{
		double x = 6* METER_TO_POINT;
		if (is_att_team){
			modifer_whole_player_home_area(team, x, 0);
		}
		}
		break;
	case SPEAK_DEFEND_ATTACK:
		{double x = 0.;
		if (is_att_team) {
			x = 3 * METER_TO_POINT;
			modifer_whole_player_home_area(team, -x, 0);
		} else {
			x = 6 * METER_TO_POINT;
			modifer_whole_player_home_area(team, x, 0);
		}
}
		break;
		break;
	default:
		break;
	}

}

void SoccerFormation::modifer_whole_player_home_area(SoccerTeam* team,
		double modifer_x, double modifer_y) {
	SoccerPlayer* player = NULL;
	for (int i = 0; i < team->get_players_on_pitch_count(); i++) {
		player = team->get_player_on_pitch(i);
		player->modifer_home(modifer_x, modifer_y);
	}
}
