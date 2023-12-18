#pragma once
#include "random.h"
#include "vec3.h"
#include "ray.h"

class Camera
{
public:
	Camera(double vfov, double aspect, vec3 look_from, vec3 look_at, vec3 v_up, double time0 = 0, double time1 = 0);
	Ray GetRay(double u, double v);

private:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 front;
	vec3 right;
	vec3 up;
	double len_radius;
	double focus_dist;
	double time0, time1;
};

inline Camera::Camera(const double vfov, const double aspect, const vec3 look_from, const vec3 look_at, const vec3 v_up, double time0, double time1) :len_radius(0.0)
{
	const double theta = vfov * PI / 180.0;
	const double h = tan(theta / 2.0);

	const auto view_height = 2.0 * h;
	const auto view_width = aspect * view_height;

	front = normalize(look_from - look_at);
	right = normalize(cross(v_up, front));
	up = cross(front, right);

	focus_dist = (look_from - look_at).length();
	origin = look_from;
	horizontal = focus_dist * view_width * right;
	vertical = focus_dist * view_height * up;
	lower_left_corner = origin - vertical / 2.0 - horizontal / 2.0 - focus_dist * front;

	this->time0 = time0;
	this->time1 = time1;
}

inline Ray Camera::GetRay(double u, double v)
{
	vec3 rd = len_radius * random_in_unit_disk();
	vec3 offsets = right * rd.x() + up * rd.y();

	return Ray{
		origin + offsets,
		lower_left_corner + u * horizontal + v * vertical - origin - offsets,
		random_double(time0, time1)
	};
}
