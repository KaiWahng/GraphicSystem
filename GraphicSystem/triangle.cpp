#include "stdafx.h"
#include "triangle.h"


triangle::triangle(Vector3f vertex0, Vector3f vertex1, Vector3f vertex2, Vector3f ka, Vector3f kd, Vector3f ks, Vector3f p, int id_set) : surface(ka, kd, ks, p)
{
	vertices[0] = vertex0;
	vertices[1] = vertex1;
	vertices[2] = vertex2;
	normal = (vertex1 - vertex0).cross(vertex2 - vertex0);
	normal.normalize();
	id = id_set;
}


triangle::~triangle()
{
}

bool triangle::hit(Vector3f origin, Vector3f direction, float t0, float t1, hitrecord& rec)
{
	float a = vertices[0][0] - vertices[1][0];
	float b = vertices[0][1] - vertices[1][1];
	float c = vertices[0][2] - vertices[1][2];
	float d = vertices[0][0] - vertices[2][0];
	float e = vertices[0][1] - vertices[2][1];
	float f = vertices[0][2] - vertices[2][2];
	float g = direction[0];
	float h = direction[1];
	float i = direction[2];
	float j = vertices[0][0] - origin[0];
	float k = vertices[0][1] - origin[1];
	float l = vertices[0][2] - origin[2];

	float ei_hf = e*i - h*f;
	float gf_di = g*f - d*i;
	float dh_eg = d*h - e*g;
	float ak_jb = a*k - j*b;
	float jc_al = j*c - a*l;
	float bl_kc = b*l - k*c;

	float M = a*ei_hf + b*gf_di + c*dh_eg;
	if (M == 0)
		return false;
	float t = -(f*ak_jb + e*jc_al + d*bl_kc) / M;
	if ((t<t0) || (t>t1))
		return false;
	float beta = (j*ei_hf + k*gf_di + l*dh_eg) / M;
	if (beta < 0 || beta>1)
		return false;
	float gamma = (i*ak_jb + h*jc_al + g*bl_kc) / M;
	if (gamma < 0 || gamma>1 || beta + gamma > 1)
		return false;
	rec.normal = normal;
	rec.k_ambient = k_ambient;
	rec.k_diffuse = k_diffuse;
	rec.k_specular = k_specular;
	rec.phong = phong;
	rec.t = t;
	return true;
}
