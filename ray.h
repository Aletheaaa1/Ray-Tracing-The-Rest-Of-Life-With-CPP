#pragma once
#include "vec3.h"

class Ray
{
public:
	Ray() = default;
	Ray(const vec3& origin, const vec3& direction, double time = 0);
	vec3 At(double t) const;

	vec3 At(double t);
public:
	vec3 orig;
	vec3 dir;
	double time;
};

inline Ray::Ray(const vec3& origin, const vec3& direction, double time) :orig(origin), dir(direction), time(time)
{
}

inline vec3 Ray::At(double t) const
{
	return orig + t * dir;
}
