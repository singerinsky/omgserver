#ifndef _ATTACK_ORDER_H_
#define _ATTACK_ORDER_H_

#include "soccer_player.h"
#include "soccer_region.h"

typedef enum
{
    ORDER_CROSS = 0,
    ORDER_DRIBBLE,
    ORDER_PASS,
    ORDER_SHOOT,
    ORDER_MOVE,
    ORDER_PENALTY,
    ORDER_FREE,
    ORDER_CORNER,
    ORDER_FORCE_CROSS, // 强制长传
    ORDER_FORCE_SHOOT, // 强制射门
    ORDER_FGK_KICKOFF	//门将开球
} Behavior;

struct AttackOrder
{
    AttackOrder(Behavior b)
    {
        target_player_id = -1;
        target_region_lt = -1;
        target_region_rb = -1;
        src_player_id	 = -1;
        src_region_lt	 = -1;
        src_region_rb    = -1;
        behavior 		 = b;
    }

    AttackOrder(const AttackOrder &o)
    {
        target_regions 		= o.target_regions;
        target_player_id 	= o.target_player_id;
        target_region_lt 	= o.target_region_lt;
        target_region_rb 	= o.target_region_rb;
        src_player_id		= o.src_player_id;
        src_region_rb		= o.src_region_rb;
        src_region_lt		= o.src_region_lt;
        behavior 			= o.behavior;
    }

    bool is_target_in_by_formation_pos(int player_pos)
    {
    	int lx = (this->target_region_lt-1) % 5;
    	int ly = (int)ceil((this->target_region_lt-1) / 5);

    	int rx = (this->target_region_rb-1) % 5;
    	int ry = (int)ceil((this->target_region_rb-1) / 5);

    	int px = (player_pos-1) % 5;
    	int py = (int)ceil((player_pos-1) / 5);

        if ((px >= lx) && (px <= rx) && (py >= ly) && (py <= ry))
        {
            return true;
        }

        return false;
    }

    bool is_src_in_by_formation_pos(int player_pos)
    {
    	int lx = (this->src_region_lt-1) % 5;
    	int ly = (int)ceil((this->src_region_lt-1) / 5);

    	int rx = (this->src_region_rb-1) % 5;
    	int ry = (int)ceil((this->src_region_rb-1) / 5);

    	int px = (player_pos-1) % 5;
    	int py = (int)ceil((player_pos-1) / 5);

        if ((px >= lx) && (px <= rx) && (py >= ly) && (py <= ry))
        {
            return true;
        }

        return false;
    }

    RegionSet target_regions;
    RegionSet src_regions;

    int target_region_lt;
    int target_region_rb;
    int target_player_id;

    int src_player_id;
    int src_region_lt;
    int src_region_rb;

    Behavior behavior;
};

#endif /* _ATTACK_ORDER_H_ */
