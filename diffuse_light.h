#pragma once
#include "material.h"
#include "solid_color.h"
#include "texture.h"

class DiffuseLight :public Material
{
public:
	DiffuseLight() = default;
	DiffuseLight(vec3 color);
	DiffuseLight(std::shared_ptr<Texture> color);
	bool Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const override;
	inline vec3 Emitted(double u, double v, const vec3& p) const override;

public:
	std::shared_ptr<Texture> emit;
};

inline DiffuseLight::DiffuseLight(vec3 color) :emit(std::make_shared<SolidColor>(color))
{
}

inline DiffuseLight::DiffuseLight(std::shared_ptr<Texture>color) : emit(std::move(color))
{
}

inline bool DiffuseLight::Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const
{
	return false;
}

inline vec3 DiffuseLight::Emitted(double u, double v, const vec3& p) const
{
	return emit->Value(u, v, p);
}
