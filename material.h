#pragma once
#include "ray.h"
#include "hittable.h"

struct HitRecord;

class Material
{
public:
	virtual bool Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const;
	virtual double ScatteringPdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) const;
	virtual vec3 Emitted(double u, double v, const vec3& p) const;
};

inline bool Material::Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const
{
	return false;
}

inline double Material::ScatteringPdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) const
{
	return 0;
}

inline vec3 Material::Emitted(double u, double v, const vec3& p) const
{
	return { 0, 0, 0 };
}
