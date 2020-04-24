#pragma once
#include "vector3.h"
class light
{
public:
	light(vector3 p, vector3 i);
	~light();
	vector3 position;
	vector3 illumination;
};

