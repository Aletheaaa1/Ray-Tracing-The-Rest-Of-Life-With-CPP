#pragma once
#include "material.h"

class Metallic : public Material
{
public:
	Metallic() = default;
	Metallic(vec3 albedo, double roughness);
	bool Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const override;

public:
	vec3 albedo;
	double roughness;
};

inline Metallic::Metallic(vec3 albedo, double roughness) :albedo(albedo), roughness(roughness)
{
}

inline bool Metallic::Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const
{
	vec3 dir = reflect(normalize(r_in.dir), rec.normal) + roughness * random_unit_vector();
	scattered = Ray{ rec.p, dir, r_in.time };
	attenuation = albedo;

	return dot(dir, rec.normal) > 0;
}
