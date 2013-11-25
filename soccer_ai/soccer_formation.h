#ifndef _SOCCER_FORMATION_H_
#define _SOCCER_FORMATION_H_

#include "soccer_region.h"

class SoccerTeam;
class SoccerPlayer;

class SoccerFormation
{
    enum
    {
        PITCH_COUNT = 40
    };

    static SoccerRegion _region[PITCH_COUNT];
    static double _ball_limit_up_x;
    static double _ball_limit_down_x;
    static double _ball_limit_up_y;
    static double _ball_limit_down_y;
    static double _x1_limit_up;
    static double _x2_limit_up;
    static double _x1_limit_down;
    static double _x2_limit_down;
    static double _y1_limit_up;
    static double _y2_limit_up;
    static double _y1_limit_down;
    static double _y2_limit_down;
    static double _pitch_width;
    static double _pitch_height;

    int _position[10];
    bool _attack;
    int _move_typ;
    int _zone_def;

public:
    static void init_pitch_region(void);
    static Vector2D get_region_pos(int);

    SoccerFormation(void)
    {
        _position[0] = 0;
        _attack = false;
        _zone_def = 1;
    }

    void set_attack(bool attack)
    {
        _attack = attack;
    }

    void set_move_typ(int move_typ)
    {
    	_move_typ = move_typ;
    }

    void set_position(int *position)
    {
        memcpy(_position, position, sizeof(_position));
        if (!_attack)
        {
            for (int i = 0; i < 10; ++i)
            {
                _position[i] = 36 - _position[i];
            }
        }
    }

    void update_defend_formation(SoccerTeam *team);

    double get_back_x(double tmp, double x);

    void update_attack_formation(SoccerTeam *team);

    void fix_formation_by_move_order(int formation_pos, SoccerRegion &home);

    //if in this line has two player , make two player near middle 
    void fix_formation_middle_empty(SoccerTeam *);

    void team_modifer_formation_speak(SoccerTeam* team);

    void modifer_whole_player_home_area(SoccerTeam* team,double modifer_x,double modifer_y);
    void player_modifer_formation_speak(SoccerTeam*);

    int checkPointRegionIndex(Vector2D& vec);
};

#endif /* _SOCCER_FORMATION_H_ */
