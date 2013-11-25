#ifndef _MOVABLE_ENTITY_H_
#define _MOVABLE_ENTITY_H_

#include "vector2d.h"
#include "calc_direction.h"

class MovableEntity // 8个值
{
    Vector2D 	_position;
    Vector2D 	_heading;
    double 		_speed;
    int 		_direction;

public:
    MovableEntity(void)
    {
        _speed = 0;
    }
    
    virtual ~MovableEntity(void) {}

    void set_pos(double x, double y)
    {
        _position.x = x;
        _position.y = y;
    }

    virtual void set_pos(const Vector2D &position)
    {
        _position = position;
    }

	void modifer_pos(double x, double y)
	{
		_position.x += x;
		_position.y += y;
	}

    const Vector2D &get_pos(void) const
    {
        return _position;
    }

    virtual void move(void)
    {
        _position += _heading * _speed;
    }

    virtual void set_speed(double speed)
    {
        _speed = speed;
    }

    virtual void down_or_up_speed(double pre)
    {
    	_speed = _speed * pre;
    }

    virtual void heading_to(const Vector2D &vector)
    {
        _heading = vector - _position;
        _direction = calc_direction(_heading);
        _heading.normalize();
    }

    virtual void set_heading(const Vector2D &vector)
    {
        _heading = vector;
        _direction = calc_direction(_heading);
    }

    double get_speed(void) const
    {
        return _speed;
    }

    int get_direction(void) const
    {
    	return _direction;
    }

    Vector2D get_heading(void) const
    {
        return _heading;
    }
};

#endif /* _MOVABLE_ENTITY_H_ */
