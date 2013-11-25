#ifndef _SOCCER_BALL_H_
#define _SOCCER_BALL_H_

#include "game_entity.h"
#include "movable_entity.h"

#include "../common/object_pool.h"
#include "state_type.h"
#include "enum.h"

class SoccerPlayer;
class SoccerBall;

BEGIN_DECLARE_STATE(GlobalBallState, SoccerBall)
public:
    void execute(SoccerBall &b);
    void on_message(SoccerBall &b, Telegram *message);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(BallCrossState, SoccerBall)
public:
    void execute(SoccerBall &b);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(BallRollState, SoccerBall)
public:
    void execute(SoccerBall &b);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(BallStopState, SoccerBall)
END_DECLARE_STATE

BEGIN_DECLARE_STATE(PenaltyState, SoccerBall)
public:
    void execute(SoccerBall &b);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(FreeState, SoccerBall)
public:
    void execute(SoccerBall &b);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(CornerState, SoccerBall)
public:
    void execute(SoccerBall &b);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(BallDribbledState, SoccerBall)
	void execute(SoccerBall &b);
END_DECLARE_STATE

BEGIN_DECLARE_STATE(BallGoalFlyState, SoccerBall)
	void execute(SoccerBall &b);
END_DECLARE_STATE


class SoccerBall : public MovableEntity, public GameEntityBase<SoccerBall>
{
public:
    typedef enum
    {
        STOP,
        ROLL,
        START_DRIBBLE,
        DRIBBLE,
        CROSS,
        MOVE,
        OUTSIZE, // 出界
        PENALTY, // 点球
        FREE, // 任意球
        CORNER, // 角球，
        GOAL_FLY	//进球后飞行
    } MotionType;

private:
    SoccerPlayer *_owner;
    SoccerPlayer *_last_owner;
    SoccerPlayer *_previous_owner;
    MotionType 	 _motion_type;
    Vector2D 	 _head_vec;
    Vector2D 	 _target_vec;
    int 	     _speed_z;
    int 		 _z;

    int 		 _speed_add;

    Vector2D	_boll_start_pos;
    //距离球门的距离
    double 		_distance_to_goal;
public:
    SoccerBall(uint32_t id)
    	: GameEntityBase<SoccerBall> (id)
    {
        _motion_type 	= STOP;
        _owner 			= NULL;
        _last_owner 	= NULL;
        _previous_owner = NULL;
        _speed_z 		= 0;
        _z 				= 0;
    }

    int get_z(void) const
    {
        return _z;
    }

    void set_z(int z)
    {
        _z = z;
    }

    void kick(uint32_t speed, Vector2D vector)
    {
        set_speed(speed);
        set_heading(vector);
        _speed_z 	 = 0;
        _z 			 = 0;
        _motion_type = ROLL;
    }

    void cross(uint32_t speed, uint32_t speed_z, Vector2D vector)
    {
        set_speed(speed);
        set_heading(vector);
        _z 			 = 0;
        _speed_z 	 = speed_z;
        _motion_type = CROSS;
    }

    SoccerPlayer *get_owner(void)
    {
        return _owner;
    }

    SoccerPlayer *get_previous_owner(void)
    {
        return _previous_owner;
    }

    void set_owner(SoccerPlayer *owner);

    SoccerPlayer *get_last_owner(void) const
    {
        return _last_owner;
    }

    MotionType get_motion_type(void) const
    {
        return _motion_type;
    }

    void set_motion_type(MotionType mt)
    {
        _motion_type = mt;
    }

    const Vector2D &get_target_vec(void) const
    {
        return _target_vec;
    }

    void set_target_vec(const Vector2D &vec)
    {
        _target_vec = vec;
    }

    const Vector2D &get_head_vec(void) const
    {
        return _head_vec;
    }

    void set_head_vec(const Vector2D &vec)
    {
        _head_vec = vec;
    }

    virtual void move(void);

    virtual void move_penalty(void);

    virtual void move_free(void);

    virtual void move_corner(void);

    void set_boll_start_pos(Vector2D tmp)
    {
    	_boll_start_pos.x = tmp.x;
    	_boll_start_pos.y = tmp.y;
    }

    Vector2D get_boll_start_pos(void)
    {
    	return _boll_start_pos;
    }

    void set_speed_add(int add)
    {
    	this->_speed_add = add;
    }

    int get_speed_add(void)
    {
    	return this->_speed_add;
    }

    double distance_goal(){
    	return this->_distance_to_goal;
    }

    void show_round_end_ball_move(RoundEndSubTyp round_end_typ);

    bool is_reach_final_point();

    BALL_POS	get_ball_pos_type(){
	if(get_pos().x > 0 && get_pos().x <= (32 * METER_TO_POINT)){
		return BACK_POS;
	}else if((get_pos().x > 32 * METER_TO_POINT) && get_pos().x <= (PITCH_WIDTH - 32 * METER_TO_POINT)){
		return MIDDLE_POS;
	}else if(get_pos().x > (PITCH_WIDTH - 32 * METER_TO_POINT) && get_pos().x < PITCH_WIDTH){
		return FRONT_POS;
	}
	return BACK_POS;	
    }
};

#endif /* _SOCCER_BALL_H_ */
