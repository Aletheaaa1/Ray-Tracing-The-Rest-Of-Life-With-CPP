#pragma once
#include "hittable.h"
#include "hittable_list.h"
#include "rect.h"

class Box :public Hittable
{
public:
	Box() = default;
	Box(const vec3& p0, const vec3& p1, const std::shared_ptr<Material> mat);
	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	AABB BoundingBox() const override;

	vec3 p0;
	vec3 p1;
	HittableList box_faces;
	std::shared_ptr<Material> mat;
};

inline Box::Box(const vec3& p0, const vec3& p1, const std::shared_ptr<Material> mat)
	:p0(p0), p1(p1), mat(mat)
{
	box_faces.Add(std::make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), mat));
	box_faces.Add(std::make_shared<XYRect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), mat));
	box_faces.Add(std::make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), mat));
	box_faces.Add(std::make_shared<XZRect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), mat));
	box_faces.Add(std::make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), mat));
	box_faces.Add(std::make_shared<YZRect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), mat));
}

inline bool Box::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	return box_faces.Hit(r, t_min, t_max, rec);
}

inline AABB Box::BoundingBox() const
{
	return AABB{ p0, p1 };
}
