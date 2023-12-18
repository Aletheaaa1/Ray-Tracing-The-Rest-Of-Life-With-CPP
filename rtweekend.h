#pragma once
#include <limits>

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline constexpr double degrees_to_radius(const double degrees)
{
	return degrees * PI / 180.0;
}
