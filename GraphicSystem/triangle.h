#pragma once
#include "surface.h"
class triangle :
	public surface
{
public:
	triangle(vector3 vertex0, vector3 vertex1, vector3 vertex2, vector3 ka, vector3 kd, vector3 ks, vector3 p);
	~triangle();
	bool hit(vector3 origin, vector3 direction, float t0, float t1, hitrecord& rec);	
private:
	vector3 normal;
	vector3 vertices[3];
};

