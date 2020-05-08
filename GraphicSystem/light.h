#pragma once
#include "Eigen\Dense"
using namespace::Eigen;
class light
{
public:
	light(const Vector4f * p, Vector3f i);
	~light();
	Vector4f position;
	Vector3f illumination;
};

