#include "../common/head.h"

#include "soccer_ball.h"
#include "soccer_player.h"
#include "soccer_config.h"
#include "soccer_ai/attack_order.h"

IMPLEMENT_STATE_INSTANCE(BallCrossState)
IMPLEMENT_STATE_INSTANCE(BallDribbledState)
IMPLEMENT_STATE_INSTANCE(BallRollState)
IMPLEMENT_STATE_INSTANCE(BallStopState)
IMPLEMENT_STATE_INSTANCE(BallGoalFlyState)
IMPLEMENT_STATE_INSTANCE(GlobalBallState)

using namespace std;

void SoccerBall::move_penalty(void)
{
	set_pos(B_PENALTY_LOCATION_X, B_PENALTY_LOCATION_Y);
	set_speed(0);
}

void SoccerBall::move_free(void)
{
	set_pos(get_boll_start_pos());
	set_speed(0);
}

void SoccerBall::move_corner(void)
{
	set_pos(get_boll_start_pos());
	set_speed(0);
}

/////////////////////////
// SoccerBall
void SoccerBall::move(void)
{
	Vector2D pos_x_y = get_pos();
	if(this->_motion_type == GOAL_FLY){
		if (pos_x_y.x < OUTSIDE_WIDTH || pos_x_y.x > (PITCH_WIDTH + 2*METER_TO_POINT)
			 || pos_x_y.y < OUTSIDE_HEIGHT || pos_x_y.y > PITCH_HEIGHT - OUTSIDE_HEIGHT)
			{
				_motion_type = OUTSIZE;
				//this->set_state(BallStopState::alloc());
				set_speed(0);
				return;
			}
	}else{
		if (pos_x_y.x < OUTSIDE_WIDTH || pos_x_y.x > (PITCH_WIDTH)
		 || pos_x_y.y < 0 || pos_x_y.y > PITCH_HEIGHT)
		{
			LOG(INFO)<<pos_x_y.y<<":";
			_motion_type = OUTSIZE;
			//this->set_state(BallStopState::alloc());
			set_speed(get_speed()*0.9);
			return;
		}
	}
    set_pos(get_pos() + get_heading() * get_speed());
    if (abs(_speed_z) > 0.001 || abs(_z) > 0.001)
    {
        // 球在空中
        _z = _z + _speed_z;
        if (_z <= 0)
        {
            // 球弹在地上
            _z = 0;
            set_speed(get_speed() / 2);
            if (abs(_speed_z) < 5)
            {
                _speed_z = 0;
                _motion_type = ROLL;
            }
            else
            {
                _speed_z = -_speed_z / 2;
            }
        }
        else
        {
            _speed_z = (int)(_speed_z - GRAVITY); // 重力
        }
    }
    else
    {
        // 球在地上
        int new_speed = (int)(get_speed() - GROUND_ACCE);
        if (new_speed > 0)
        {
            set_speed(new_speed);
        }
        else
        {
            set_speed(0);
            _motion_type = STOP;
        }
    }

  //  if(this->get_pos().distance(this->_target_vec) < 2*METER_TO_POINT){
  //  	set_speed(0);
    	//_motion_type = STOP;
   // }


    //更新距离球门的距离
    Vector2D goal_vector(PITCH_WIDTH - OUTSIDE_WIDTH, PITCH_HEIGHT / 2);
    this->_distance_to_goal = goal_vector.distance(this->get_pos());
}

/////////////////////////
// GlobalBallState
void GlobalBallState::execute(SoccerBall &b)
{
    SoccerPlayer *owner = b.get_owner();
    if (owner != NULL)
    {
        if (b.get_motion_type() == SoccerBall::STOP)
        {
            b.set_motion_type(SoccerBall::MOVE);
        }
        else if (b.get_motion_type() == SoccerBall::MOVE)
        {
            b.set_motion_type(SoccerBall::START_DRIBBLE);
        }
        else if (b.get_motion_type() == SoccerBall::OUTSIZE)
        {
        	b.set_motion_type(SoccerBall::OUTSIZE);
        }
        else if (b.get_motion_type() == SoccerBall::PENALTY)
        {
			b.set_pos(B_PENALTY_LOCATION_X, B_PENALTY_LOCATION_Y);
            b.set_speed(0);
            b.set_motion_type(SoccerBall::PENALTY);
			b.set_state(PenaltyState::alloc());
        	return;
        }
        else if (b.get_motion_type() == SoccerBall::FREE)
        {
			b.set_pos(b.get_boll_start_pos().x, b.get_boll_start_pos().y);
            b.set_speed(0);
            b.set_motion_type(SoccerBall::FREE);
			b.set_state(FreeState::alloc());
        	return;
        }
        else if (b.get_motion_type() == SoccerBall::CORNER)
        {
        	b.set_pos(b.get_boll_start_pos().x, b.get_boll_start_pos().y);
            b.set_speed(0);
            b.set_motion_type(SoccerBall::CORNER);
			b.set_state(CornerState::alloc());
        	return;
        }/*else if(b.get_motion_type() == SoccerBall::GOAL_FLY){
        	b.set_motion_type(SoccerBall::GOAL_FLY);
        	b.set_state();
        }*/
        else
        {
            b.set_motion_type(SoccerBall::DRIBBLE);
    		if ((abs((int)(b.get_pos().x - owner->get_pos().x))<2)&&(abs((int)(b.get_pos().x - owner->get_pos().x))<2))
    		{
    			b.set_speed_add(1);
    		}

    		if ((abs((int)(b.get_pos().x - owner->get_pos().x))>10)||(abs((int)(b.get_pos().x - owner->get_pos().x))>10))
    		{
    			b.set_speed_add(-1);
    		}

    		b.set_speed(owner->get_speed());
            b.set_heading(owner->get_heading());
            if (b.get_speed_add() == 1)
            {
            	b.set_pos(b.get_pos() + b.get_heading() * owner->get_speed());
            }
            else
            {
            	b.set_pos(b.get_pos() - b.get_heading() * owner->get_speed());
            }
            return;
        }
        b.set_heading(owner->get_heading());
        b.set_speed(owner->get_speed());
        b.set_pos(owner->get_pos());
    }
}

void GlobalBallState::on_message(SoccerBall &b, Telegram *message)
{
    BallTelegram *ball_msg = (BallTelegram *)message;
    switch (ball_msg->message)
    {
		case TELE_BALL_KICK:
		{
			b.kick(ball_msg->speed, ball_msg->heading);
			b.set_state(BallRollState::alloc());
		}
		break;
		case TELE_BALL_CROSS:
		{
			b.cross(ball_msg->speed, ball_msg->speed_z, ball_msg->heading);
			b.set_state(BallCrossState::alloc());
		}
		break;
		case TELE_BALL_STOP:
		{
			b.set_speed(0);
			b.set_state(BallStopState::alloc());
		}
		break;
		case TELE_PLAYER_PENALTY:
		{
			b.set_speed(0);
			b.set_state(PenaltyState::alloc());
		}
		break;
		case TELE_PLAYER_FREE:
		{
			b.set_speed(0);
			b.set_state(FreeState::alloc());
		}
		break;
		case TELE_PLAYER_CORNER:
		{
			b.set_speed(0);
			b.set_state(CornerState::alloc());
		}
		break;
		case TELE_BALL_GOAL_FLY:
		{
			b.set_speed(ball_msg->speed);
			b.set_state(BallGoalFlyState::alloc());
		}
		break;
		default:
		{

		}
		break;
    }
}

//////////////////////////////
// BallRollState
void BallRollState::execute(SoccerBall &b)
{
    b.move();
}

//////////////////////////////
// PenaltyState
void PenaltyState::execute(SoccerBall &b)
{
    b.move_penalty();
}

//////////////////////////////
//FreeState
void FreeState::execute(SoccerBall &b)
{
    b.move_free();
}

//////////////////////////////
//CornerState
void CornerState::execute(SoccerBall &b)
{
    b.move_corner();
}

//////////////////////////////
// BallCrossState
void BallCrossState::execute(SoccerBall &b)
{
    b.move();
}

void BallDribbledState::execute(SoccerBall &b)
{
	b.move();
}

void BallGoalFlyState::execute(SoccerBall &b){
	b.set_motion_type(SoccerBall::GOAL_FLY);
	b.move();
}

void SoccerBall::set_owner(SoccerPlayer *owner)
{
	_previous_owner = _owner;
	_owner 			= owner;
	if (owner != NULL)
	{
		set_state(BallDribbledState::alloc());
		_last_owner = owner;
		switch (_owner->get_behavior())
		{
			case ORDER_PENALTY:
			{
				_motion_type = PENALTY;
			}
			break;
			case ORDER_FREE:
			{
				_motion_type = FREE;
			}
			break;
			case ORDER_CORNER:
			{
				_motion_type = CORNER;
			}
			break;
			default:
			{
				_motion_type = STOP;
			}
			break;
		}
	}
}

bool SoccerBall::is_reach_final_point(){
	if(this->get_pos().x > PITCH_WIDTH){
		return true;
	}
	return false;
}


void SoccerBall::show_round_end_ball_move(RoundEndSubTyp round_end_typ){
	/*Vector2D goal_vec(PITCH_WIDTH, PITCH_HEIGHT / 2);
	switch(round_end_typ){
	case SHOT_PENALTY_FORWARD_OUTTARGET:		//点球前锋射门偏出	16		点球点	1前锋，1门将
	case SHOT_PENALTY_FORWARD_CROSSBAR:		//点球前锋射中门楣	17		点球点	1前锋，1门将
	case SHOT_PENALTY_FORWARD_GOALPOST:	//点球前锋射中门柱	18		点球点	1前锋，1门将
	case SHOT_DIRECT_FREE_KICK_FORWARD_OUTTARGET:	//直接任意球前锋射门偏出	19		禁区外	1前锋，1门将，人墙
	case SHOT_DIRECT_FREE_KICK_FORWARD_CROSSBAR:		//直接任意球前锋射中门楣	20		禁区外	1前锋，1门将，人墙
	case SHOT_DIRECT_FREE_KICK_FORWARD_GOALPOST:		//直接任意球前锋射中门柱	21		禁区外	1前锋，1门将，人墙
	case SHOT_FORWARD_OUTTARGET:						//前锋射门偏出	22		球门前	1前锋，1门将，1后卫
	case SHOT_FORWARD_CROSSBAR:					//前锋射中门楣	23		球门前	1前锋，1门将，1后卫
	case SHOT_FORWARD_GOALPOST:						//前锋射中门柱	24		球门前	1前锋，1门将，1后卫
	case SHOT_DIRECT_FREE_KICK_WALL:					//前锋任意球打人墙	25		禁区外	1前锋，1门将，人墙
	case SHOT_DEFENDER_INTERUPT_OUTSIDE:				//被后卫挡出底线	26		球门前	1前锋，1门将，1后卫
	case SHOT_DEFENDER_INTERUPT:						//被后卫挡出，未出界	27		球门前	1前锋，1门将，1后卫
		int index = RAND_INT%2;
		Vector2D target_vec;
		if(index == 0){
			target_vec.x = PITCH_WIDTH;
			target_vec.y = goal_vec.y - (7.32/2 + RAND_INT%3)*METER_TO_POINT;
		}else{
			target_vec.x = PITCH_WIDTH;
			target_vec.y = goal_vec.y + (7.32/2 + RAND_INT%3)*METER_TO_POINT;
		}
		Vector2D head = (this->get_pos() - target_vec).normalize();
		this->_head_vec = head;
		this->_target_vec = target_vec;

		break;
	}
	default:

*;*/



}
