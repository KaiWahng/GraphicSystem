#pragma once
#include "surface.h"
#include "CommonWindows.h"
#include <Eigen\Dense>
#include "light.h"
#define viewport_width 800
#define viewport_height 480
#define dpi 1
using namespace::Eigen;
class camera
{
public:
	camera(Vector3f vp, Vector3f v_set, Vector3f w_set);
	~camera();
	void photo(surface* scene, light * l_diffuse, light * l_ambient, Vector3f * bg);
	//void photo(surface* scene, light * l_diffuse, light * l_ambient, Vector3f * bg, windowDemo * wd);
	Vector3f calculate_direction(Vector3f origin, float f, int i, int j);
	Vector3f viewposition;
	Vector3f u;
	Vector3f v;
	Vector3f w;
	float focallen;
	Vector3f * image;
};

