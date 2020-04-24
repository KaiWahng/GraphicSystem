#pragma once
#include "surface.h"
class sphere :
	public surface
{
public:
	sphere(vector3 c, float r, vector3 ka, vector3 kd, vector3 ks, vector3 p);
	~sphere();
	bool hit(vector3 origin, vector3 direction, float t0, float t1, hitrecord& rec);
	vector3 normal(vector3 point);
private:
	vector3 center;
	float radius;
};

