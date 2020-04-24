#pragma once
#include "vector3.h"
class hitrecord
{
public:
	hitrecord();
	~hitrecord();
	float t;
	vector3 normal;
	vector3 k_ambient;
	vector3 k_diffuse;
	vector3 k_specular;
	vector3 phong;
};

