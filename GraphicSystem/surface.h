#pragma once
#include "vector3.h"
#include "hitrecord.h"
class surface
{
public:
	surface();
	surface(vector3 ka, vector3 kd, vector3 ks, vector3 p);
	~surface();
	virtual bool hit(vector3 origin, vector3 direction, float t0, float t1, hitrecord& rec);
	vector3 k_ambient;
	vector3 k_diffuse;
	vector3 k_specular;
	vector3 phong;
	vector3 backgroundcolor;
	surface* children;
	surface* sibling;
};

