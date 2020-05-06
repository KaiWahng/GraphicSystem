#pragma once
#include "surface.h"
class sphere :
	public surface
{
public:
	sphere(Vector3f c, float r, Vector3f ka, Vector3f kd, Vector3f ks, Vector3f p);
	~sphere();
	bool hit(Vector3f origin, Vector3f direction, float t0, float t1, hitrecord& rec);
	Vector3f normal(Vector3f point);
private:
	Vector3f center;
	float radius;
};

