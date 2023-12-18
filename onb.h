#pragma once
#include "vec3.h"

class ONB
{
public:
	ONB() = default;

	vec3 operator[] (unsigned int i) const;

	vec3 u() const;
	vec3 v() const;
	vec3 w() const;

public:
	vec3 axis[3];
};

inline vec3 ONB::operator[](const unsigned int i) const
{
	return axis[i];
}

inline vec3 ONB::u() const
{
	return axis[0];
}

inline vec3 ONB::v() const
{
	return axis[1];
}

inline vec3 ONB::w() const
{
	return axis[2];
}
