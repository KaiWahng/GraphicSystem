#pragma once
#include <Eigen\Dense>
#include "hitrecord.h"
using namespace::Eigen;

class surface
{
public:
	surface();
	surface(Vector3f ka, Vector3f kd, Vector3f ks, Vector3f p);
	~surface();
	virtual bool hit(Vector3f origin, Vector3f direction, float t0, float t1, hitrecord& rec);
	Vector3f k_ambient;
	Vector3f k_diffuse;
	Vector3f k_specular;
	Vector3f phong;
	Vector3f backgroundcolor;
	surface* children;
	surface* sibling;
};

