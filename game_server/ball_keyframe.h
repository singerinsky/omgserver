#ifndef _BALL_KEYFRAME_H_
#define _BALL_KEYFRAME_H_

#include "../soccer_ai/vector2d.h"
#include "../soccer_ai/soccer_config.h"
#include "../common/string.h"
#include "../soccer_ai/enum.h"
#include "msg.h"

class SoccerBall;

class BallKeyframe
{
    int 	 _time_scale;
    double 	 _x;
    double 	 _y;
    int 	 _z;
    double 	 _speed;
    Vector2D     _heading;
    int		 _motion_type;

public:
    BallKeyframe(int time_scale, SoccerBall *ball);

    bool is_similar(SoccerBall *ball) const;

    void append_to_buffer(int time_last
    					, omg::StringBuilder &buffer
    					, bool reverse
    					, bool is_half
    					, int flag) const
    {
        int x = (int)_x;
        int y = (int)_y;
        int z = _z;


        if (is_half)
        {
        	if(reverse){
        		x = PITCH_WIDTH - x;
        		y = PITCH_HEIGHT - y;
        	}
        }else if(!is_half){
        	if(!reverse){
        		x = PITCH_WIDTH - x;
        		y = PITCH_HEIGHT - y;
        	}
        }

/*        if (x < OUTSIDE_WIDTH)
        {
        	x = OUTSIDE_WIDTH;
        }*/

        if (y < OUTSIDE_HEIGHT)
        {
        	y = OUTSIDE_HEIGHT;
        }

        if (z < 0)
        {
        	z = 0;
        }
        char c_buff[sizeof(BallRoundInfo)+1];
        BallRoundInfo*	info = (BallRoundInfo*)c_buff;
		info->time_scale = _time_scale;
		info->x = x;
		info->y = y;
		info->z = z;
		info->state = _motion_type;
		c_buff[sizeof(BallRoundInfo)] = '\0';
		buffer.append((const char*)c_buff,sizeof(BallRoundInfo));
    }

    int time_scale(void) const
    {
        return _time_scale;
    }

    void update_keyframe(int time_scale, SoccerBall *ball);

    void dump_info(void) const
    {
        VLOG(1) << _time_scale << ", " << _x << "," << _y << "," << _z;
    }
};

#endif /* _BALL_KEYFRAME_H_ */
