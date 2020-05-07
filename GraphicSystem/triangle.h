#pragma once
#include "surface.h"
class triangle :
	public surface
{
public:
	triangle(const Vector4f * vertex0, const Vector4f * vertex1, const Vector4f * vertex2, Vector3f ka, Vector3f kd, Vector3f ks, float p, int id_set);
	~triangle();
	bool hit(const Vector4f * origin, const Vector4f * direction, float t0, float t1, hitrecord& rec);
private:
	Vector4f normal;
	Vector4f vertices[3];
	int id;
};

