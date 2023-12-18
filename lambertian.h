#pragma once
#include "material.h"
#include "ray.h"
#include "solid_color.h"
#include "checker_texture.h"
#include "texture.h"

class Lambertian : public Material
{
public:
	Lambertian() = default;
	Lambertian(vec3 a);
	Lambertian(std::shared_ptr<Texture> a);

	bool Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const override;
	double ScatteringPdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) const override;

	std::shared_ptr<Texture> albedo;
};

inline Lambertian::Lambertian(vec3 a) :albedo(std::make_shared<SolidColor>(a))
{
}

inline Lambertian::Lambertian(std::shared_ptr<Texture> a) : albedo(std::move(a))
{
}

inline bool Lambertian::Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const
{
	const vec3 dir = random_in_hemisphere(rec.normal);
	scattered = Ray{ rec.p, dir, r_in.time };
	attenuation = albedo->Value(rec.u, rec.v, rec.p);

	pdf = ScatteringPdf(r_in, rec, scattered);

	return true;
}

inline double Lambertian::ScatteringPdf(const Ray& r_in, const HitRecord& rec, const Ray& scattered) const
{
	const auto cosine = dot(rec.normal, normalize(scattered.dir));
	return cosine < 0.0 ? 0 : cosine / PI;
	//return 0.5 / PI;
}
