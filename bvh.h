#pragma once
#include <algorithm>

#include "hittable.h"
#include "hittable_list.h"

class BVH : public Hittable
{
public:
	BVH() = default;
	BVH(const HittableList& list);
	BVH(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end);

	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;
	AABB BoundingBox() const override;

	static bool Compare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, unsigned int axis);
	static bool CompareX(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
	static bool CompareY(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
	static bool CompareZ(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b);
public:
	std::shared_ptr<Hittable> left;
	std::shared_ptr<Hittable> right;
	AABB box;
};

inline BVH::BVH(const HittableList& list)
	:BVH(list.objects, 0, list.objects.size())
{
}

inline BVH::BVH(const std::vector<std::shared_ptr<Hittable>>& src_objects, size_t start, size_t end)
{
	auto objects = src_objects;

	const int axis = static_cast<int>(random_double(0, 3.0));
	const auto comparator = (axis == 0) ? CompareX
		: (axis == 1) ? CompareY
		: CompareZ;

	size_t object_span = end - start;
	if (object_span == 1)
	{
		left = right = objects[start];
	}
	else if (object_span == 2)
	{
		if (comparator(objects[start], objects[start + 1]))
		{
			left = objects[start];
			right = objects[start + 1];
		}
		else
		{
			left = objects[start + 1];
			right = objects[start];
		}
	}
	else
	{
		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		const size_t mid = start + object_span / 2.0;
		left = std::make_shared<BVH>(objects, start, mid);
		right = std::make_shared<BVH>(objects, mid, end);
	}

	const auto left_box = left->BoundingBox();
	const auto right_box = right->BoundingBox();
	box = AABB::SurroundingBox(left_box, right_box);
}

inline bool BVH::Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const
{
	if (!box.Hit(r, t_min, t_max))
	{
		return false;
	}

	const auto hit_left = left->Hit(r, t_min, t_max, rec);
	const auto hit_right = right->Hit(r, t_min, hit_left ? rec.t : t_max, rec);

	return hit_left || hit_right;
}

inline AABB BVH::BoundingBox() const
{
	return box;
}

inline bool BVH::Compare(const std::shared_ptr<Hittable>& a, const std::shared_ptr<Hittable>& b, unsigned axis)
{
	return (a->BoundingBox().minmum[axis] < b->BoundingBox().minmum[axis]);
}

inline bool BVH::CompareX(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
{
	return Compare(a, b, 0);
}

inline bool BVH::CompareY(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
{
	return Compare(a, b, 1);
}

inline bool BVH::CompareZ(const std::shared_ptr<Hittable> a, const std::shared_ptr<Hittable> b)
{
	return Compare(a, b, 2);
}
