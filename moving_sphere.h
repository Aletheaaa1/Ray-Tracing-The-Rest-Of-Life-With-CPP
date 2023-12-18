#pragma once
#include "hittable.h"

class MovingSphere :public Hittable
{
public:
	MovingSphere() = default;
	MovingSphere(vec3 center0, vec3 center1, double time0, double time1, double radius, std::shared_ptr<Material> mat_ptr);
	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	AABB BoundingBox() const override;

public:
	vec3 center0, center1;
	double time0, time1;
	double radius;
	std::shared_ptr<Material> mat_ptr;
};

inline MovingSphere::MovingSphere(vec3 center0, vec3 center1, double time0, double time1, double radius, std::shared_ptr<Material> mat_ptr) :
	center0(center0), center1(center1), time0(time0), time1(time1), radius(radius), mat_ptr(mat_ptr)
{
}

inline bool MovingSphere::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	vec3 center = center0 + ((r.time - time0) / (time1 - time0)) * (center1 - center0);
	vec3 oc = r.orig - center;
	auto a = r.dir.length_squared();
	auto half_b = dot(oc, r.dir);
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.At(rec.t);
	rec.mat_ptr = mat_ptr;
	const vec3 outward_normal = (rec.p - center) / radius;
	rec.SetFrontFace(r, outward_normal);

	return true;
}

inline AABB MovingSphere::BoundingBox() const
{
	return AABB{
		center0 - vec3(radius, radius, radius),
		center0 + vec3(radius, radius, radius)
	};
}
