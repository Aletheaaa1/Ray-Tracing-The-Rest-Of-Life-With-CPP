#pragma once
#include <glm/common.hpp>

#include "ray.h"

class AABB
{
public:
	AABB() = default;
	AABB(const vec3& a, const vec3& b);

	bool Hit(const Ray& ray, double t_min, double t_max) const;
	static AABB SurroundingBox(const AABB& box0, const AABB& box1);

public:
	vec3 minmum;
	vec3 maxmum;
};

inline AABB::AABB(const vec3& minimum, const vec3& maxmum) : minmum(minimum), maxmum(maxmum)
{
}

inline bool AABB::Hit(const Ray& ray, double t_min, double t_max) const
{
	for (int i = 0; i < 3; i++)
	{
		const auto invD = 1.0 / ray.dir[i];
		auto t0 = (minmum[i] - ray.orig[i]) * invD;
		auto t1 = (maxmum[i] - ray.orig[i]) * invD;
		if (invD < 0.0)
		{
			std::swap(t0, t1);
		}

		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;

		if (t_max <= t_min)
		{
			return false;
		}
	}

	return true;
}

inline AABB AABB::SurroundingBox(const AABB& box0, const AABB& box1)
{
	vec3 min{
		fmin(box0.minmum.x(), box1.minmum.x()),
		fmin(box0.minmum.y(), box1.minmum.y()),
		fmin(box0.minmum.z(), box1.minmum.z())
	};
	vec3 max{
		fmax(box0.maxmum.x(), box1.maxmum.x()),
		fmax(box0.maxmum.y(), box1.maxmum.y()),
		fmax(box0.maxmum.z(), box1.maxmum.z())
	};

	return AABB{ min, max };
}
