#pragma once
#include <Eigen\Dense>
#include "hitrecord.h"
using namespace::Eigen;

class surface
{
public:
	surface();
	surface(Vector3f ka, Vector3f kd, Vector3f ks, float p);
	~surface();
	virtual bool hit(const Vector4f * origin, const Vector4f * direction, float t0, float t1, hitrecord& rec);
	Vector3f k_ambient;
	Vector3f k_diffuse;
	Vector3f k_specular;
	float phong;
	Vector3f backgroundcolor;
	surface* children;
	surface* sibling;
};

