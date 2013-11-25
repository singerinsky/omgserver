#ifndef _CALC_DIRECTION_H_
#define _CALC_DIRECTION_H_
#include "vector2d.h"

inline int calc_direction(const Vector2D &heading)
{
    Vector2D vertical(0, 1);
    double dot = heading.dot(vertical);
    if (heading.x >= 0)
    {
        if (dot > 0.924)
        {
            return 1;
        }
        else if (dot > 0.383)
        {
            return 8;
        }
        else if (dot > -0.383)
        {
            return 7;
        }
        else if (dot > - 0.924)
        {
            return 6;
        }
        else
        {
            return 5;
        }
    }
    else
    {
        if (dot > 0.924)
        {
            return 1;
        }
        else if (dot > 0.383)
        {
            return 2;
        }
        else if (dot > -0.383)
        {
            return 3;
        }
        else if (dot > - 0.924)
        {
            return 4;
        }
        else
        {
            return 5;
        }
    }
}

#endif /* _CALC_DIRECTION_H_ */
