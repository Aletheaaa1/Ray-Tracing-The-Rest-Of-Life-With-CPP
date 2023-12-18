#pragma once
#include "material.h"

class Dielectric : public Material
{
public:
	Dielectric() = default;
	Dielectric(double ior);

	bool Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const override;
	double Schlick(double cosine, double ref_idx) const;
public:
	double ior;
};

inline Dielectric::Dielectric(double ior) :ior(ior)
{
}

inline bool Dielectric::Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const
{
	double refract_ration;
	vec3 unit_dir = normalize(r_in.dir);
	vec3 dir;

	if (rec.is_front)
	{
		refract_ration = 1.0 / ior;
	}
	else
	{
		refract_ration = ior;
	}

	auto cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
	auto sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	if (refract_ration * sin_theta > 1.0 || Schlick(cos_theta, refract_ration) > random_double())
	{
		dir = reflect(unit_dir, rec.normal);
	}
	else
	{
		dir = refract(unit_dir, rec.normal, refract_ration);
	}

	scattered = Ray{ rec.p, dir, r_in.time };
	attenuation = vec3(1.0, 1.0, 1.0);

	return true;
}

inline double Dielectric::Schlick(double cosine, double ref_idx) const
{
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}
