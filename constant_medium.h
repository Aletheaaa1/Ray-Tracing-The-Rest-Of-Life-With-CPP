#pragma once
#include <memory>

#include "hittable.h"
#include "solid_color.h"
#include "rtweekend.h"

class Isotropic :public Material
{
public:
	Isotropic(vec3 c) : albedo(std::make_shared<SolidColor>(c)) {}
	bool Scatter(const Ray& r_in, vec3& attenuation, HitRecord& rec, Ray& scattered, double& pdf) const override
	{
		scattered = Ray{ rec.p, rec.normal + random_unit_vector(), r_in.time };
		attenuation = albedo->Value(rec.u, rec.v, rec.p);

		return true;
	}

public:
	std::shared_ptr<Texture> albedo;
};

class ConstantMedium :public Hittable
{
public:

	ConstantMedium(std::shared_ptr<Hittable> boundary, const double d, const vec3& c)
		: boundary(std::move(boundary)), neg_inv_density(-1.0 / d), phase_function(std::make_shared<Isotropic>(c)) {}

	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		HitRecord hit0, hit1;
		if (!boundary->Hit(r, -infinity, infinity, hit0))
		{
			return false;
		}

		if (!(boundary->Hit(r, hit0.t + 0.0001, infinity, hit1)))
		{
			return false;
		}

		if (hit0.t < t_min) hit0.t = t_min;
		if (hit1.t > t_max) hit1.t = t_max;
		if (hit0.t > hit1.t) return false;
		if (hit1.t < 0) hit1.t = 0;

		const auto ray_length = r.dir.length();
		const auto distance_inside_boundary = (hit1.t - hit0.t) * ray_length;
		const auto hit_distance = neg_inv_density * log(random_double());

		if (hit_distance > distance_inside_boundary)
		{
			return false;
		}

		rec.t = hit0.t + hit_distance / ray_length;
		rec.p = r.At(rec.t);
		rec.normal = vec3(1.0, 0, 0);
		rec.is_front = true;
		rec.mat_ptr = phase_function;

		return true;
	}

	AABB BoundingBox() const override
	{
		return boundary->BoundingBox();
	}

public:
	std::shared_ptr<Hittable> boundary;
	double neg_inv_density;
	std::shared_ptr<Material> phase_function;
};
