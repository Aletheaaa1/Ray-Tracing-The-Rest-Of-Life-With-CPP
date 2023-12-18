#pragma once
#include <charconv>
#include <memory>
#include <vector>

#include "hittable.h"

class HittableList : public Hittable
{
public:
	HittableList() = default;

	void Clear();
	void Add(const std::shared_ptr<Hittable> obj);
	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	AABB BoundingBox() const override;

public:
	std::vector<std::shared_ptr<Hittable>> objects;
	AABB box;
};

inline void HittableList::Clear()
{
	objects.clear();
}

inline void HittableList::Add(const std::shared_ptr<Hittable> obj)
{
	objects.push_back(obj);
}

inline bool HittableList::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	double closest_so_far = t_max;
	bool hit_anything = false;
	HitRecord temp_rec;

	for (const auto& obj : objects)
	{
		if (obj->Hit(r, t_min, closest_so_far, temp_rec))
		{
			rec = temp_rec;
			hit_anything = true;
			closest_so_far = temp_rec.t;
		}
	}

	return hit_anything;
}

inline AABB HittableList::BoundingBox() const
{
	AABB temp_box;
	AABB box;
	bool first_box = true;

	for (const auto& obj : objects)
	{
		temp_box = obj->BoundingBox();
		box = first_box ? temp_box : AABB::SurroundingBox(box, temp_box);
		first_box = false;
	}

	return box;
}
