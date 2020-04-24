#include "stdafx.h"
#include "sphere.h"
#include <math.h>


sphere::sphere(vector3 c, float r, vector3 ka, vector3 kd, vector3 ks, vector3 p) : surface(ka, kd, ks, p)
{
	center = c;
	radius = r;
}


sphere::~sphere()
{
}

bool sphere::hit(vector3 origin, vector3 direction, float t0, float t1, hitrecord& rec)
{
	vector3 o_c = (origin - center);
	float o_c_2 = o_c*o_c;
	float d_2 = direction*direction;
	float d_o_c = direction*o_c;
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

vector3 sphere::normal(vector3 point)
{
	return point-center;
}
