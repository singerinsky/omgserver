#ifndef _REGION_H_
#define _REGION_H_

#include "vector2d.h"
#include "soccer_config.h"

struct SoccerRegion
{
    double x1, y1, x2, y2;
    int left_top_pos_in_formation, right_bottom_pos_in_formation;

    SoccerRegion(void)
    {
        x1 = y1 = x2 = y2 = 0;
    }

    SoccerRegion(double x1, double y1, double x2, double y2)
    {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    SoccerRegion(const Vector2D &pt, int radius)
    {
        x1 = pt.x - radius;
        y1 = pt.y - radius;
        x2 = pt.x + radius;
        y2 = pt.y + radius;
    }

    SoccerRegion(const Vector2D &pt1, const Vector2D &pt2)
    {
        x1 = pt1.x;
        y1 = pt1.y;
        x2 = pt2.x;
        y2 = pt2.y;
    }

    void set_formation_property(int lp, int rb)
    {
    	this->left_top_pos_in_formation = lp;
    	this->right_bottom_pos_in_formation = rb;
    }

    /* 区域的中心点 */
    Vector2D center(void) const
    {
        Vector2D pt;
        pt.x = (x2 + x1) / 2;
        pt.y = (y2 + y1) / 2;
        return pt;
    }

    void expend_from(const Vector2D &pt, int radius)
    {
        x1 = pt.x - radius;
        x2 = pt.x + radius;
        y1 = pt.y - radius;
        y2 = pt.y + radius;
    }

    bool in(const Vector2D &pt) const
    {
        if ((pt.x >= x1) && (pt.x <= x2) && (pt.y >= y1) && (pt.y <= y2))
        {
            return true;
        }

        return false;
    }

    void fix_to_pitch(void)
    {
    	if (x1 < OUTSIDE_WIDTH)
    	{
    		x1 = OUTSIDE_WIDTH;
    	}

    	if (x2 < OUTSIDE_WIDTH)
    	{
    		x2 = OUTSIDE_WIDTH;
    	}

    	if (y1 < OUTSIDE_HEIGHT)
    	{
    		y1 = OUTSIDE_HEIGHT;
    	}

    	if (y2 < OUTSIDE_HEIGHT)
    	{
    		y2 = OUTSIDE_HEIGHT;
    	}

    	if (x1 > PITCH_WIDTH - OUTSIDE_WIDTH)
    	{
    		x1 = PITCH_WIDTH - OUTSIDE_WIDTH;
    	}

    	if (x2 > PITCH_WIDTH - OUTSIDE_WIDTH)
    	{
    		x2 = PITCH_WIDTH - OUTSIDE_WIDTH;
    	}

    	if (y1 > PITCH_HEIGHT - OUTSIDE_HEIGHT)
    	{
    		y1 = PITCH_HEIGHT - OUTSIDE_HEIGHT;
    	}

    	if (y2 > PITCH_HEIGHT - OUTSIDE_HEIGHT)
    	{
    		y2 = PITCH_HEIGHT - OUTSIDE_HEIGHT;
    	}
    }
};

class RegionSet : public SoccerRegion
{
public:
    void push_back(const SoccerRegion &r)
    {
        if (r.x1 < r.x2)
        {
            this->x1 = r.x1;
            this->x2 = r.x2;
        }
        else
        {
            this->x2 = r.x1;
            this->x1 = r.x2;
        }

        if (r.y1 < r.y2)
        {
            this->y1 = r.y1;
            this->y2 = r.y2;
        }
        else
        {
            this->y2 = r.y1;
            this->y1 = r.y2;
        }
    }
};

struct Player_Formation_Cell
{
	int pid;
	int player_index;
	int x_cell;
	int y_cell;
};


#endif /* REGION_H_ */
