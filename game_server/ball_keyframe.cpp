#include "ball_keyframe.h"

#include "../soccer_ai/soccer_ball.h"

BallKeyframe::BallKeyframe(int time_scale, SoccerBall *ball)
{
    _time_scale = time_scale;
    _x 			= ball->get_pos().x;
    _y 			= ball->get_pos().y;
    _z 			= ball->get_z();
    _speed 		= ball->get_speed();
    _heading 	= ball->get_heading();
    _motion_type	= ball->get_motion_type();
}

bool BallKeyframe::is_similar(SoccerBall *ball) const
{
	if(ball->get_motion_type() == SoccerBall::GOAL_FLY){
			return false;
	}

    if (ball->get_motion_type() == SoccerBall::START_DRIBBLE)
    {
        return false;
    }

    if (ball->get_motion_type() == SoccerBall::MOVE)
    {
        return false;
    }

    if (_z != ball->get_z())
    {
        return false;
    }

    if (ball->get_motion_type() == SoccerBall::PENALTY)
    {
        return false;
    }

    if (ball->get_motion_type() == SoccerBall::FREE)
    {
        return false;
    }

    if (ball->get_motion_type() == SoccerBall::CORNER)
    {
        return false;
    }

    return ((_speed == ball->get_speed()) && (_heading == ball->get_heading()));
}

void BallKeyframe::update_keyframe(int time_scale, SoccerBall *ball)
{
    _time_scale = time_scale;
    _x 			= ball->get_pos().x;
    _y 			= ball->get_pos().y;
    _z 			= ball->get_z();
    _speed 		= ball->get_speed();
    _heading 	= ball->get_heading();
    _motion_type = ball->get_motion_type();
}
