#include "../common/head.h"

#include "soccer_config.h"
#include "soccer_match.h"
#include "enum.h"

SoccerMatch::SoccerMatch(void)
	: GameEntityBase<SoccerMatch> (0)
	, _message_dispatcher(&_entity_manager)
	, _team1(HOME_TEAM_ID, this)
	, _team2(AWAY_TEAM_ID, this)
	, _ball(1)
	//, _camera(2)
{
    _entity_manager.enregister(this);
    _ball.set_global_state(GlobalBallState::alloc());
    _ball.set_state(BallStopState::alloc());
    _entity_manager.enregister(&_ball);
    _time_scale = 1;

    //_camera.set_ball(&_ball);

    _event_frames.clear();
    _skill_frames.clear();

    goal_vec.x = PITCH_WIDTH - OUTSIDE_WIDTH;
    goal_vec.y = PITCH_HEIGHT / 2;

    union_pid = 0; // 球员PID
    union_op_pid = 0; // 球员PID
    uid = 0; // team ID

    _is_number_inj = 0;

    _status = 0;

    _fake_shoot_ending = 0;

    _ball_owner.clear();
    _ball_owner.push_back(0);

    _match_event_card_typ = 0;

    endStatus = new MatchEndStatus();

    _round_index = 0;
    _dpid.clear();

    _count_corent = 0;
    _count_penalty = 0;
    _count_free = 0;

    _round_time = 0;

    _is_match_real_begin = false;
}

SoccerMatch::~SoccerMatch(void)
{
	delete endStatus;
	endStatus = NULL;
}

Vector2D &SoccerMatch::get_goal_vec(void)
{
	return this->goal_vec;
}

bool SoccerMatch::is_outside(void)
{
    Vector2D ball_pos = _ball.get_pos();
    if ((ball_pos.y <= OUTSIDE_HEIGHT) || (ball_pos.y >= PITCH_HEIGHT - OUTSIDE_HEIGHT))
    {
        return true;
    }

    if ((ball_pos.x <= OUTSIDE_WIDTH) || (ball_pos.x >= PITCH_WIDTH - OUTSIDE_WIDTH))
    {
        return true;
    }

    return false;
}

void SoccerMatch::set_match_end_status(int at
									 , int current_end_status
									 , int sub_typ
									 , int next_typ
									 , int inj)
{
    endStatus->_current_end_status 	= current_end_status;
    endStatus->_current_end_sub_typ = sub_typ;
    endStatus->_next_round_typ 		= next_typ;
    endStatus->_injured 			= inj;
    endStatus->_at 					= at;
}

void SoccerMatch::goal_show(void)
{
	if (this->_ball.get_pos().x > (PITCH_WIDTH + OUTSIDE_WIDTH))
	{
		this->_ball.down_or_up_speed(0.1);
	}
}

MatchEndStatus *SoccerMatch::update_match(void)
{
    this->update();

    return this->endStatus;
}

void SoccerMatch::update(void)
{

    _attack_team->update(); /* 进攻方  */
    _defend_team->update(); /* 防守方  */

    _ball.update();

    if (endStatus->_current_end_status >= END_GOAL && endStatus->_current_end_status <= END_NORMAL_END) {
    	if(endStatus->_current_end_status == END_GOAL){
			if(_attack_team->get_state()->get_type() != TYPE_GoalingState){
				_attack_team->set_state(GoalingState::alloc());
			}
			if(_defend_team->get_state()->get_type() != TYPE_GoalingState){
				_defend_team->set_state(GoalingState::alloc());
			}
    	}
    	if(endStatus->_current_end_status == END_BREAK || endStatus->_current_end_status == END_GOAL_FAIL){
    		if(_attack_team->get_state()->get_type() != TYPE_TeamAttackFailedState){
    			_attack_team->set_state(TeamAttackFailedState::alloc());
    		}
    		if(_defend_team->get_state()->get_type() != TYPE_TeamDefendSuccessState){
    			_defend_team->set_state(TeamDefendSuccessState::alloc());
    		}

    	}

    }

    if (_time_scale % 2 == 1)
    {
    	update_queue_to_ball_and_goal(); /* 球 球门中心点 的距离 */
		update_queue_to_offline(); /* 球员到底线的距离 */
    	//do_judge(); /* 整体判罚,每两次判断一次 */
    }

    ++_time_scale;
}

void SoccerMatch::set_team1_current_formation(int formation_card_id)
{
	_team1.set_current_formation_card_id(formation_card_id);
}

void SoccerMatch::set_team2_current_formation(int formation_card_id)
{
	_team2.set_current_formation_card_id(formation_card_id);
}

void SoccerMatch::set_team1_free_cornor_penalty(int free, int cornor, int penalty)
{
	_team1.set_free_cornor_penalty(free, cornor, penalty);
}

void SoccerMatch::set_team2_free_cornor_penalty(int free, int cornor, int penalty)
{
	_team2.set_free_cornor_penalty(free, cornor, penalty);
}


void SoccerMatch::set_team_goal_state(void)
{
	_team1.set_goal_state();
	_team2.set_goal_state();
}

void SoccerMatch::set_team_is_who_kick_off(bool i)
{
	_team1.set_who_kick_off(i);
	_team2.set_who_kick_off(i);
}

void SoccerMatch::set_team_score(int u1_score, int u2_score)
{
	_team1.set_team_score(u1_score);
	_team2.set_team_score(u2_score);
}

void SoccerMatch::set_team_player_pos(double x, double y)
{
	_team1.set_player_pos(x, y);
	_team2.set_player_pos(x, y);
}


void SoccerMatch::init_match(int kick_typ
						   , MoveDefine *attack_move_define
						   , int attack_formation[]
						   , int defend_formation[])
{
    attack_move_define->update_region(); // 区域

    //重置一些变量
    _attack_team->set_move_def_define(attack_move_define);
    //_defend_team->set_move_def_define(attack_move_define);
    // 球的初始位置
    _ball.set_pos(STADIUM_CENTER_WIDTH, STADIUM_CENTER_HEIGHT);

    _kick_typ = kick_typ;
    _attack_team->re_set();
    _defend_team->re_set();
    _attack_team->init_formation(attack_formation); // 阵型
    _defend_team->init_formation(defend_formation); // 阵型

    update_queue_to_ball_and_goal();
    update_queue_to_offline();

    _attack_team->prepare_for_kick_off(); // 准备开始
    _defend_team->set_state(DefendingState::alloc());
    this->endStatus->ReSet();

}

void SoccerMatch::update_queue_to_ball_and_goal(void)
{
    _player_queue.clear();
    _player_queue_to_goal.clear();

    SoccerTeam *team[] = {&_team1, &_team2};
    for (int j = 0; j < 2; ++j)
    {
    	team[j]->clear_player_to_ball();
        int count = team[j]->get_players_on_pitch_count();
        for (int i = 0; i < count; ++i)
        {
            SoccerPlayer *player = team[j]->get_player_on_pitch(i);
            double distance = player->update_distance_to_ball(); /* 到球的距离 */
            double distance_to_goal = player->update_distance_to_goal(); /* 到球门中心点的距离 */

            _player_queue_to_goal.insert((int)distance_to_goal, player);
            _player_queue.insert((int)distance, player);
            team[j]->add_player_to_ball(player, distance);
        }
    }
}

void SoccerMatch::update_queue_to_offline(void)
{
    _player_queue_to_offline.clear();

    SoccerTeam *team[] = {&_team1, &_team2};
    for (int j = 0; j < 2; ++j)
    {
        int count = team[j]->get_players_on_pitch_count();
        for (int i = 0; i < count; ++i)
        {
            SoccerPlayer *player = team[j]->get_player_on_pitch(i);

            double distance_to_offline = player->update_distance_to_offline(); /* 距离底线 */

            _player_queue_to_offline.insert((int)distance_to_offline, player);
        }
    }
}

/* 获取进攻方离底线最近的人 */
SoccerPlayer *SoccerMatch::get_att_team_closest_to_offline(void)
{
	return this->_player_queue_to_offline.get_closest(this->get_attack_team());
}

/* 获取防守方离底线最近的人 */
SoccerPlayer *SoccerMatch::get_def_team_closest_to_offline(void)
{
	int x =0;
	SoccerPlayer* pPlayer = NULL;
	SoccerTeam *team = this->get_defend_team();
	for(int i=0;i<10;i++){
		SoccerPlayer* player = team->get_player_on_pitch(i);
		if(player->get_pos().x > x){
			x = player->get_pos().x;
			pPlayer = player;
		}
	}
	return pPlayer;
	//return this->_player_queue_to_offline.get_closest(this->get_defend_team());
}

/* 获取最近的防守的球员 */
SoccerPlayer *SoccerMatch::get_closest_to_ball_def(void)
{
	return this->_player_queue.get_closest(this->get_defend_team());
}

void SoccerMatch::do_judge(void)
{
	/* 判断是否越位 */
	SoccerPlayer *def_player = get_def_team_closest_to_offline();
	SoccerPlayer *att_player = get_att_team_closest_to_offline();

	//前面有球无所谓
	if(att_player->get_pos().x < this->get_ball()->get_pos().x){
		return;
	}

	double dis_check = g_game_config.get_player_config("offside_check");
	if (((this->get_attack_team() != 0)) && ((def_player->get_pos().x - att_player->get_pos().x) < dis_check))
	{
		/* 计算是否要越位 动态调整 */
		bool rst = false;
		double a_s = RAND_INT%100;
		double d_s = RAND_INT%100;
		if (d_s > a_s)
		{
			rst = true;
		}

		if (rst == true)
		{
			int offside = 0;
			if ((def_player->get_pos().x - att_player->get_pos().x) > 6)
			{
				offside = 2;
			}
			else
			{
				offside = 1;
			}

			this->get_attack_team()->set_offside(offside);
			this->get_attack_team()->set_offside_player(att_player);
			att_player->set_state(OffSideState::alloc());
		}
	}
}

void SoccerMatch::calc_pently_match(int& home_score,int& away_score){
	std::vector<SoccerPlayer*> home_player_list;
	std::vector<SoccerPlayer*> away_player_list;

	SoccerTeam* home_team = this->get_home_team();
	SoccerTeam* away_team = this->get_away_team();

	home_team->get_top_shooter(home_player_list,5);
	away_team->get_top_shooter(away_player_list,5);

	MatchPentlyEvent home_event;
	MatchPentlyEvent away_event;

	//

	for(int i=0;i<5;i++){
		if((i == 4)){
			if(home_score == away_score){
				int rand_index = RAND_INT%2;
				if(rand_index == 0){
					home_player_list[i]->do_pently_cmp(1,home_event);
					away_player_list[i]->do_pently_cmp(-1,away_event);
					home_score++;
					home_event.shoot_dir = RAND_INT%9 + 1;
					away_event.shoot_dir = RAND_INT%6 + 10;
					//away_score--;
				}else{
					home_player_list[i]->do_pently_cmp(-1,home_event);
					away_player_list[i]->do_pently_cmp(1,away_event);
					//home_score--;
					away_event.shoot_dir = RAND_INT%9 + 1;
					home_event.shoot_dir = RAND_INT%6 + 10;
					away_score++;
				}
			}else{
				home_player_list[i]->do_pently_cmp(1,home_event);
				away_player_list[i]->do_pently_cmp(1,away_event);
				home_score++;
				away_score++;
				away_event.shoot_dir = RAND_INT%9 +1;
				home_event.shoot_dir = RAND_INT%9 +1;
			}
		}else{
			if(home_player_list[i]->do_pently_cmp(0,home_event)){
				home_event.shoot_dir = RAND_INT%9 + 1;
				home_score++;
			}else{
				//home_score--;
				home_event.shoot_dir = RAND_INT%6 + 10;
			}

			if(away_player_list[i]->do_pently_cmp(0,away_event)){
				away_score++;
				away_event.shoot_dir = RAND_INT%9 + 1;
			}else{
				//away_score--;
				away_event.shoot_dir = RAND_INT%6 + 10;
			}
		}
		this->_pently_frames.push_back(home_event);
		this->_pently_frames.push_back(away_event);

		//如果剩下的轮数已经决定胜负的话
		if((4-i) < abs(home_score - away_score)){
			VLOG(0)<<"第"<<(i+1)<<"轮"<<"  "<<home_score<<":"<<away_score<<" 胜负已经决定!";
			break;
		}
	}
}

void SoccerMatch::general_all_attack_pently(){
	std::vector<SoccerPlayer*> home_player_list;
	std::vector<SoccerPlayer*> away_player_list;

	SoccerTeam* home_team = this->get_home_team();
	SoccerTeam* away_team = this->get_away_team();

	home_team->get_top_shooter(home_player_list,5);
	away_team->get_top_shooter(away_player_list,5);

	MatchPentlyEvent home_event;
	MatchPentlyEvent away_event;
	if(home_team->is_team_all_attack()){
		for(int i=0;i<3;i++){
			home_player_list[i]->do_pently_cmp(1,home_event);
			away_player_list[i]->do_pently_cmp(-1,away_event);
			home_event.shoot_dir = RAND_INT%9 + 1;
			away_event.shoot_dir = RAND_INT%6 + 10;
			this->_pently_frames.push_back(home_event);
			this->_pently_frames.push_back(away_event);
		}
	}else if(away_team->is_team_all_attack()){
		for(int i=0;i<3;i++){
			home_player_list[i]->do_pently_cmp(-1,home_event);
			away_player_list[i]->do_pently_cmp(1,away_event);
			away_event.shoot_dir = RAND_INT%9 + 1;
			home_event.shoot_dir = RAND_INT%6 + 10;
			this->_pently_frames.push_back(home_event);
			this->_pently_frames.push_back(away_event);
		}
	}
}
