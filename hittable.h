#pragma once
#include "material.h"
#include "ray.h"
#include "aabb.h"

struct HitRecord {
	vec3 p;
	vec3 normal;
	double t;
	double u;
	double v;
	bool is_front;
	std::shared_ptr<Material> mat_ptr;

	inline void SetFrontFace(const Ray& r, const vec3& outward_normal)
	{
		is_front = dot(r.dir, outward_normal) < 0;
		normal = is_front ? outward_normal : -outward_normal;
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
	virtual AABB BoundingBox() const = 0;
};
