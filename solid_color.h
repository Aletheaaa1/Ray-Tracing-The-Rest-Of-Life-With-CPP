#pragma once
#include "texture.h"

class SolidColor : public Texture
{
public:
	SolidColor() = default;
	SolidColor(const vec3& c);
	SolidColor(double r, double g, double b);

	vec3 Value(double u, double v, const vec3& position) const override;

private:
	vec3 solid_color;
};

inline SolidColor::SolidColor(const vec3& c) :solid_color(c)
{
}

inline SolidColor::SolidColor(const double r, const double g, const double b) : solid_color(vec3(r, g, b))
{
}

inline vec3 SolidColor::Value(double u, double v, const vec3& position) const
{
	return solid_color;
}
