#pragma once
#include "hittable.h"
#include "material.h"

class Sphere : public Hittable
{
public:
	Sphere() = default;
	Sphere(vec3 center, double radius, std::shared_ptr<Material> mat_ptr);
	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	AABB BoundingBox() const override;
	static void GetSphereUV(const vec3& p, double& u, double& v);

public:
	vec3 center;
	double radius;
	std::shared_ptr<Material> mat_ptr;
};

inline Sphere::Sphere(vec3 center, double radius, std::shared_ptr<Material> mat_ptr) :center(center), radius(radius), mat_ptr(mat_ptr)
{
}

inline bool Sphere::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
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
	GetSphereUV(outward_normal, rec.u, rec.v);

	return true;
}

inline AABB Sphere::BoundingBox() const
{
	return AABB{
		center - vec3(radius, radius, radius),
		center + vec3(radius, radius, radius)
	};
}

inline void Sphere::GetSphereUV(const vec3& p, double& u, double& v)
{
	auto theta = acos(-p.y());
	auto phi = atan2(-p.z(), p.x()) + PI;

	u = phi / (2 * PI);
	v = theta / PI;
}
