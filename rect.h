#pragma once
#include <utility>

#include "hittable.h"

class XYRect :public Hittable
{
public:
	XYRect() = default;
	XYRect(const double x0, const double x1, const double y0, const double y1, const double k, std::shared_ptr<Material> mat) : x0(x0), y0(y0), x1(x1), y1(y1), k(k), mat(std::move(mat))
	{
	}

	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		const double t = (k - r.orig.z()) / r.dir.z();
		if (t<t_min || t>t_max)
		{
			return false;
		}

		const double x = r.orig.x() + t * r.dir.x();
		const double y = r.orig.y() + t * r.dir.y();
		if (x<x0 || x>x1 || y<y0 || y>y1)
		{
			return false;
		}

		rec.u = (x - x0) / (x1 - x0);
		rec.v = (y - y0) / (y1 - y0);
		rec.t = t;
		rec.mat_ptr = mat;
		rec.SetFrontFace(r, vec3(0, 0, 1));
		rec.p = r.At(t);

		return true;
	}

	AABB BoundingBox() const override
	{
		return AABB{ vec3(x0,y0,k - 0.0001),vec3(x1,y1,k + 0.0001) };
	}

public:
	double x0, y0, x1, y1, k;
	std::shared_ptr<Material> mat;
};

class XZRect :public Hittable
{
public:
	XZRect() = default;
	XZRect(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Material> mat)
		: x0(x0), x1(x1), z0(z0), z1(z1), k(k), mat(std::move(mat))
	{
	}

	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		const double t = (k - r.orig.y()) / r.dir.y();
		if (t<t_min || t>t_max)
		{
			return false;
		}

		const double x = r.orig.x() + t * r.dir.x();
		const double z = r.orig.z() + t * r.dir.z();
		if (x<x0 || x>x1 || z<z0 || z>z1)
		{
			return false;
		}

		rec.u = (x - x0) / (x1 - x0);
		rec.v = (z - z0) / (z1 - z0);
		rec.t = t;
		rec.mat_ptr = mat;
		rec.SetFrontFace(r, vec3(0, 1, 0));
		rec.p = r.At(t);

		return true;
	}

	AABB BoundingBox() const override
	{
		return AABB{ vec3(x0,k - 0.0001,z0),vec3(x1,k + 0.0001,z1) };
	}

	double x0, x1, z0, z1, k;
	std::shared_ptr<Material> mat;
};

class YZRect :public Hittable
{
public:
	YZRect() = default;
	YZRect(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Material> mat)
		: y0(y0), y1(y1), z0(z0), z1(z1), k(k), mat(std::move(mat))
	{
	}

	bool Hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override
	{
		const double t = (k - r.orig.x()) / r.dir.x();
		if (t<t_min || t>t_max)
		{
			return false;
		}

		const double y = r.orig.y() + t * r.dir.y();
		const double z = r.orig.z() + t * r.dir.z();
		if (y<y0 || y>y1 || z<z0 || z>z1)
		{
			return false;
		}

		rec.u = (y - y0) / (y1 - y0);
		rec.v = (z - z0) / (z1 - z0);
		rec.t = t;
		rec.mat_ptr = mat;
		rec.SetFrontFace(r, vec3(1, 0, 0));
		rec.p = r.At(t);

		return true;
	}

	AABB BoundingBox() const override
	{
		return AABB{ vec3(k - 0.0001,y0,z0),vec3(k + 0.0001,y1,z1) };
	}

	double y0, y1, z0, z1, k;
	std::shared_ptr<Material> mat;
};
