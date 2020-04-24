#pragma once
#include "surface.h"
#include "vector3.h"
#include "light.h"
#define viewport_width 800
#define viewport_height 480
#define dpi 1
class camera
{
public:
	camera(vector3 vp, vector3 v_set, vector3 w_set);
	~camera();
	void photo(surface* scene, light * light);
	vector3 calculate_direction(vector3 origin, float f, int i, int j);
	vector3 viewposition;
	vector3 u;
	vector3 v;
	vector3 w;
	float focallen;
	char* image;
};

