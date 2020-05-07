#pragma once
#include "surface.h"
class sphere :
	public surface
{
public:
	sphere(const Vector4f * c, float r, Vector3f ka, Vector3f kd, Vector3f ks, float p);
	~sphere();
	bool hit(const Vector4f * origin, const Vector4f * direction, float t0, float t1, hitrecord& rec);
	Vector4f normal(const Vector4f * point);
private:
	Vector4f center;
	float radius;
};

