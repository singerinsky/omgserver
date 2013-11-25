#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

struct Vector2D
{
    double x;
    double y;

    Vector2D(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2D(void)
    {
        x = 0;
        y = 0;
    }

    double length(void) const
    {
        return sqrt(x * x + y * y);
    }

    void normalize(void)
    {
        double vector_length = length();
        if (vector_length > 0)
        {
            x /= vector_length;
            y /= vector_length;
        }
    }

    double dot(const Vector2D &v2) const
    {
        return x * v2.x + y * v2.y;
    }

    double distance(const Vector2D &v2) const
    {
        return sqrt(fast_distance(v2));
    }

    double fast_distance(const Vector2D &v2) const
    {
        double y_separation = (v2.y - y);
        double x_separation = (v2.x - x);
        return y_separation * y_separation + x_separation * x_separation;
    }

    const Vector2D& operator+=(const Vector2D &rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    const Vector2D& operator-=(const Vector2D &rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    const Vector2D& operator*=(const double& rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    const Vector2D& operator/=(const double& rhs)
    {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    bool operator==(const Vector2D& rhs) const
    {
        return ((x == rhs.x) && (y == rhs.y));
    }

    bool operator!=(const Vector2D& rhs) const
    {
        return ((x != rhs.x) || (y != rhs.y));
    }
};

inline Vector2D operator*(const Vector2D &lhs, double rhs)
{
    Vector2D result(lhs);
    result *= rhs;
    return result;
}

inline Vector2D operator*(double lhs, const Vector2D &rhs)
{
    Vector2D result(rhs);
    result *= lhs;
    return result;
}

inline Vector2D operator/(const Vector2D &lhs, double rhs)
{
    Vector2D result(lhs);
    result /= rhs;
    return result;
}

inline Vector2D operator/(double lhs, const Vector2D &rhs)
{
    Vector2D result(rhs);
    result /= lhs;
    return result;
}

inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs)
{
    Vector2D result(lhs);
    result.x -= rhs.x;
    result.y -= rhs.y;
    return result;
}

inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs)
{
    Vector2D result(lhs);
    result.x += rhs.x;
    result.y += rhs.y;
    return result;
}

inline Vector2D vec2d_normalize(const Vector2D &v)
{
    Vector2D vec = v;

    double vector_length = vec.length();

    if (vector_length > 0)
    {
        vec.x /= vector_length;
        vec.y /= vector_length;
    }

    return vec;
}

inline std::ostream & operator << (std::ostream &os, const Vector2D &v)
{
    os << std::fixed << std::setprecision(0) << "(" << v.x << "," << v.y << ")";
    return os;
}

#endif /* _VECTOR2D_H_ */
