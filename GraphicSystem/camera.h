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
	camera(const Vector4f * vp, const Vector4f * v_set, const Vector4f * w_set);
	~camera();
	void photo(surface* scene, light * l_diffuse, light * l_ambient, Vector3f * bg);
	//void photo(surface* scene, light * l_diffuse, light * l_ambient, Vector3f * bg, windowDemo * wd);
	Vector4f calculate_direction(const Vector4f * origin, float f, int i, int j);
	Vector4f viewposition;
	Vector4f u;
	Vector4f v;
	Vector4f w;
	float focallen;
	Vector3f * image;
};

