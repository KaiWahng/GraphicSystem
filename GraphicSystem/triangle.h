#pragma once
#include "surface.h"
class triangle :
	public surface
{
public:
	triangle(Vector3f vertex0, Vector3f vertex1, Vector3f vertex2, Vector3f ka, Vector3f kd, Vector3f ks, Vector3f p, int id_set);
	~triangle();
	bool hit(Vector3f origin, Vector3f direction, float t0, float t1, hitrecord& rec);	
private:
	Vector3f normal;
	Vector3f vertices[3];
	int id;
};

