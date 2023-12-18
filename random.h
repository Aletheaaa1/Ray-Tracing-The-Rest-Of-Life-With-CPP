#pragma once
#include <random>

#include "rtweekend.h"

class Random
{
public:
	static double Randomdouble();
	static double Randomdouble(double min, double max);
	static vec3 RandomInDist();
	static vec3 RandomInFace();
};

inline double Random::Randomdouble()
{
	return rand() / (RAND_MAX + 1.0);
}

inline double Random::Randomdouble(double min, double max)
{
	return min + Randomdouble() * (max - min);
}

inline vec3 Random::RandomInDist()
{
	while (true)
	{
		auto p = vec3(Randomdouble(-1.0f, 1.0f), Randomdouble(-1.0f, 1.0f), Randomdouble(-1.0f, 1.0f));
		if (p.length() > 1.0f) continue;
		return p;
	}
}

inline vec3 Random::RandomInFace()
{
	double theta = Randomdouble() * 2.0f * PI;
	double phi = Randomdouble() * PI;

	return {
		sin(phi) * cos(theta),
		cos(phi),
		sin(phi) * sin(theta),
	};
}
