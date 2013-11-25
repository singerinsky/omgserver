#ifndef _PLAYER_KEYFRAME_H_
#define _PLAYER_KEYFRAME_H_

#include "../soccer_ai/calc_direction.h"
#include "../soccer_ai/soccer_player.h"

class PlayerKeyframe
{
    int 	 _time_scale;
    int 	 _player_id;
    double 	 _speed;
    int 	 _action_type;
    int 	 _sub_action_type;
    short	 _cond;
    double 	 _x;
    double 	 _y;
    Vector2D _heading;
    int		 _direction;
    State<SoccerPlayer> *_state;
    int		_state_type;

public:
    PlayerKeyframe(int time_scale, SoccerPlayer *player)
    {
        _time_scale 	 = time_scale;
        _player_id 		 = player->_union_pid;
        _speed 			 = player->get_speed();
        _action_type 	 = player->_move_status;
        _sub_action_type = 1;
        _heading 		 = player->get_heading();
        _x 				 = player->get_pos().x;
        _y 				 = player->get_pos().y;
        _direction		 = player->get_direction();
        _state 			 = player->get_state();
        _cond			 = (short)player->get_cond();
        if (_state != NULL)
        {
        	_state_type	= static_cast<State<SoccerPlayer>*>(_state)->get_type();
        }
        else
        {
        	_state_type = -1;
        }
    }

    bool is_similar(SoccerPlayer *player) const
    {
    	if(player->is_gk()){
    		return true;
    	}

		if(player->is_own_ball()){
			return false;
		}
        return (
      		(this->_speed == player->get_speed())
             && (this->_direction == player->get_direction())             &&
        		(this->_state == player->get_state())
             );
    }

    void append_to_buffer(int time_last
    				    , omg::StringBuilder &buffer
    				    , bool reverse
    				    , bool is_half
    				    , int flag) const
    {
        int x = (int)_x;
        int y = (int)_y;
        //int d = calc_direction(_heading);

/*        if ((is_half && reverse) || (!is_half && reverse))
        {
        	x = PITCH_WIDTH - x;
			y = PITCH_HEIGHT - y;
			if (d <= 4)
			{
				d += 4;
			}
			else
			{
				d -= 4;
			}
        }*/
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

        if (x < OUTSIDE_WIDTH)
        {
        	x = OUTSIDE_WIDTH;
        }

        if (y < OUTSIDE_HEIGHT)
        {
        	y = OUTSIDE_HEIGHT;
        }

        int t_state_type = _state_type;
        if (_state_type <= -1 || _state_type > 51)
        {
        	t_state_type = 37;
        }

        char c_buff[sizeof(TimeScalePlayerInfo)+1];
        TimeScalePlayerInfo*	info = (TimeScalePlayerInfo*)c_buff;
		info->time_scale = _time_scale;
		info->pos_x = x;
		info->pos_y = y;
		info->state = t_state_type;
		c_buff[sizeof(TimeScalePlayerInfo)] = '\0';
		buffer.append((const char*)c_buff,sizeof(TimeScalePlayerInfo));
    }

    int time_scale(void) const
    {
        return _time_scale;
    }

    int get_player_id(void) const
    {
    	return _player_id;
    }

    short get_player_cond() const
   	{
    	return _cond;
  	}

    void update_keyframe(int time_scale, SoccerPlayer *player)
    {
        _time_scale 	 = time_scale;
        _player_id 		 = player->_player_id;
        _speed 			 = player->get_speed();
        _action_type 	 = player->_move_status;
        _sub_action_type = 1;
        _heading 		 = player->get_heading();
        _x 				 = player->get_pos().x;
        _y 				 = player->get_pos().y;
        _state 			 = player->get_state();
        if(_state != NULL){
        	_state_type			= static_cast<State<SoccerPlayer>*>(_state)->get_type();
        }else{
        	_state_type = -1;
        }
    }

    void dump_info(void)
    {
        VLOG(3) << _time_scale << ", " << _x << "," << _y;
    }
};

#endif /* _PLAYER_KEYFRAME_H_ */
