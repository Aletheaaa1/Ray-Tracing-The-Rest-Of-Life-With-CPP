#pragma once
#include "rtweekend.h"
#include "hittable.h"

class Translate :public Hittable
{
public:
	Translate() = default;
	Translate(std::shared_ptr<Hittable> p, const vec3& displacement);

	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	AABB BoundingBox() const override;

public:
	std::shared_ptr<Hittable> ptr;
	vec3 offset;
};

inline Translate::Translate(std::shared_ptr<Hittable> p, const vec3& displacement) :ptr(std::move(p)), offset(displacement)
{
}

inline bool Translate::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	const Ray move_r{ r.orig - offset, r.dir, r.time };
	if (!ptr->Hit(move_r, t_min, t_max, rec))
	{
		return false;
	}

	rec.p += offset;
	rec.SetFrontFace(move_r, rec.normal);

	return true;
}

inline AABB Translate::BoundingBox() const
{
	return {
		ptr->BoundingBox().minmum + offset,
		ptr->BoundingBox().maxmum + offset
	};
}

class RotateY :public Hittable {
public:
	RotateY() = default;
	RotateY(std::shared_ptr<Hittable> p, double angel);
	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	AABB BoundingBox() const override;

public:
	std::shared_ptr<Hittable> ptr;
	double rotate;
	bool has_box;
	AABB box;
	double cos_theta;
	double sin_theta;
};

inline RotateY::RotateY(std::shared_ptr<Hittable> p, const double angel) : ptr(std::move(p)), rotate(angel)
{
	const auto radius = degrees_to_radius(angel);
	sin_theta = sin(radius);
	cos_theta = cos(radius);

	box = ptr->BoundingBox();
	has_box = true;

	vec3 max(-infinity, -infinity, -infinity);
	vec3 min(infinity, infinity, infinity);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				const double x = i * box.minmum.x() + (1 - i) * box.maxmum.x();
				const double y = j * box.minmum.y() + (1 - j) * box.maxmum.y();
				const double z = k * box.minmum.z() + (1 - k) * box.maxmum.z();

				const double new_x = cos_theta * x + sin_theta * z;
				const double new_z = -sin_theta * x + cos_theta * z;

				const vec3 rotate_pos(new_x, y, new_z);

				for (int n = 0; n < 3; n++)
				{
					min[n] = fmin(min[n], rotate_pos[n]);
					max[n] = fmax(max[n], rotate_pos[n]);
				}
			}
		}
	}

	box = AABB(min, max);
}

inline bool RotateY::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	auto origin = r.orig;
	auto direction = r.dir;

	origin[0] = cos_theta * r.orig[0] - sin_theta * r.orig[2];
	origin[2] = sin_theta * r.orig[0] + cos_theta * r.orig[2];

	direction[0] = cos_theta * r.dir[0] - sin_theta * r.dir[2];
	direction[2] = sin_theta * r.dir[0] + cos_theta * r.dir[2];

	const Ray rotate_r{ origin, direction, r.time };

	if (!ptr->Hit(rotate_r, t_min, t_max, rec))
	{
		return false;
	}

	auto p = rec.p;
	auto normal = rec.normal;

	p[0] = cos_theta * rec.p[0] + sin_theta * rec.p[2];
	p[2] = -sin_theta * rec.p[0] + cos_theta * rec.p[2];
	normal[0] = cos_theta * rec.normal[0] + sin_theta * rec.normal[2];
	normal[2] = -sin_theta * rec.normal[0] + cos_theta * rec.normal[2];

	rec.p = p;
	rec.SetFrontFace(rotate_r, normal);

	return true;
}

inline AABB RotateY::BoundingBox() const
{
	return box;
}
