#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include "vector2d.h"
#include "math.h"

struct Triangle
{
    Vector2D point_a;
    Vector2D point_b;
    Vector2D point_c;

    double _area;

    Triangle(Vector2D& a,Vector2D& b, Vector2D& c)
    {
    	point_a = a;
    	point_b = b;
    	point_c = c;
    	this->_area = TriangleGetArea(point_a,point_b,point_c);
    }

    Triangle(void)
    {
    	point_a.x = 0;
    	point_a.y = 0;
    	point_b.x = 0;
    	point_b.y = 0;
    	point_c.x = 0;
    	point_c.y = 0;
    }

    double  TriangleGetArea(const Vector2D& t0,const Vector2D& t1,const Vector2D& t2){
    	double area = (t0.x * t1.y + t1.x * t2.y + t2.x * t0.y - t1.x * t0.y - t2.x * t1.y - t0.x * t2.y)*0.5;
    	area = area>0?area:-area;
    	return area;
    }

public:
		inline bool check_point_in_triangle(const Vector2D& point){
			if(point.distance(point_a) > 2*METER_TO_POINT){
				return false;
			}

    	double area0 = TriangleGetArea(point,point_a,point_b);
    	double area1 = TriangleGetArea(point,point_a,point_c);
    	double area2 = TriangleGetArea(point,point_b,point_c);
    	double d = this->_area - area0- area1-area2;
    	d= d>0?d:-d;
    	if(d< 0.0001)return true;
    	return false;
    }

};

#endif /* _VECTOR2D_H_ */
