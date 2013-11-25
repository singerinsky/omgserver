#include "../common/head.h"

#include "soccer_match.h"
#include "soccer_team_state.h"

IMPLEMENT_STATE_INSTANCE(AttackingState)
IMPLEMENT_STATE_INSTANCE(DefendingState)
IMPLEMENT_STATE_INSTANCE(GoalingState)
IMPLEMENT_STATE_INSTANCE(TeamAttackFailedState)
IMPLEMENT_STATE_INSTANCE(TeamDefendSuccessState)

///////////////////////////////
// AttackingState
void AttackingState::execute(SoccerTeam &t)
{
    t.adjust_order();
    t.update_formation();
    t.update_players();
}

/////////////////////////////////
// DefendingState
void DefendingState::execute(SoccerTeam &t)
{
   // t.awake_frezon_player();
    t.update_formation();
    SoccerBall* ball = t.get_match()->get_ball();
	if(((ball->get_motion_type() == SoccerBall::CROSS)) && (t.get_air_defend_player() == NULL)){
		t.make_player_to_defend_air(ball->get_target_vec());
	}else if((ball->get_motion_type() == SoccerBall::ROLL) && (t.get_air_defend_player() == NULL)){
		t.make_player_to_defend_pass(ball->get_target_vec());
	}
	//如果球的状态是带球状态,判断有没有技能去包夹,看在前场还是中场，还是后场
	//只发动一次
	//TODO
	SoccerPlayer* ball_owner = ball->get_owner();
	if((ball_owner != NULL) && (ball_owner->get_state() != NULL)&&(ball_owner->get_state_type() == TYPE_DribbleState)){
		if(ball->get_ball_pos_type() == MIDDLE_POS || ball->get_ball_pos_type() == BACK_POS){
			t.check_will_unit_defend();
		}
	}

	//如果进入大禁区的话,从后卫选一个mind他
	if ((t.get_minding_player()== NULL) && (ball->get_pos().x > B_FORBIDDEN_AREA_X - 50)){
		std::vector<int> player_list;
		t.get_all_player_back(player_list);
		for(int count= 0;count< (int)player_list.size();count++){
			SoccerPlayer* player = t.get_player_on_pitch_by_union_id(player_list[count]);
			if(player!= NULL && (player->get_state_type() != TYPE_FrozenState) && player->check_ball_enter_mindarea()){
				player->set_state(MindOnBallState::alloc());
			}
		}
	}

    t.update_players();
}

/////////////////////////////////
// GoalingState
void GoalingState::execute(SoccerTeam &t)
{
	for (std::vector<SoccerPlayer *>::iterator itr = t.get_all_player_on_pitch().begin();
		 itr != t.get_all_player_on_pitch().end(); ++itr)
	{
		(*itr)->set_state(new GoalState());
	}
	t.update_players();
}

//AttackFailed进攻失败,回防
void TeamAttackFailedState::enter(SoccerTeam &t)
{
	for (std::vector<SoccerPlayer *>::iterator itr = t.get_all_player_on_pitch().begin();
		 itr != t.get_all_player_on_pitch().end(); ++itr)
	{
		(*itr)->set_state(new GoalState());
	}
}

void TeamAttackFailedState::execute(SoccerTeam &t)
{
	t.update_players();
}

//防守反击
void TeamDefendSuccessState::enter(SoccerTeam& t)
{
	for (std::vector<SoccerPlayer *>::iterator itr = t.get_all_player_on_pitch().begin();
		 itr != t.get_all_player_on_pitch().end(); ++itr)
	{
		(*itr)->set_state(new GoalState());
	}
}

void TeamDefendSuccessState::execute(SoccerTeam& t)
{
	t.update_players();
}


