#include "stdafx.h"
#include "sphere.h"
#include <math.h>


sphere::sphere(Vector3f c, float r, Vector3f ka, Vector3f kd, Vector3f ks, Vector3f p) : surface(ka, kd, ks, p)
{
	center = c;
	radius = r;
}


sphere::~sphere()
{
}

bool sphere::hit(Vector3f origin, Vector3f direction, float t0, float t1, hitrecord& rec)
{
	Vector3f o_c = (origin - center);
	float o_c_2 = o_c.squaredNorm();
	float d_2 = direction.squaredNorm();
	float d_o_c = direction.dot(o_c);
	float discreminant = d_o_c*d_o_c - d_2*(o_c_2 - radius*radius);
	float t = 0;
	if (discreminant < 0)
		return false;
	t = (-d_o_c - sqrt(discreminant)) / d_2;
	if (t < t0)
		t= (-d_o_c + sqrt(discreminant)) / d_2;
	if (t > t1 || t<t0)
		return false;
	rec.normal = origin + direction*t - center;
	rec.normal.normalize();
	rec.k_ambient = k_ambient;
	rec.k_diffuse = k_diffuse;
	rec.k_specular = k_specular;
	rec.phong = phong;
	rec.t = t;
	return true;
}

Vector3f sphere::normal(Vector3f point)
{
	return point-center;
}
