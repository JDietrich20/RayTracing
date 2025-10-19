#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
public:
    ray() {}

    ray(const point3 &origin, const vec3 &direction) : o(origin), d(direction) {}

    const point3 &origin() const { return o; }
    const vec3 &direction() const { return d; }

    // point at parameter t along the ray
    point3 at(double t) const
    {
        return o + t * d;
    }

private:
    point3 o; // origin
    vec3 d;   // direction
};

#endif