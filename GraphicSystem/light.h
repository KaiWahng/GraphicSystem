#pragma once
#include <Eigen\Dense>
using namespace::Eigen;
class light
{
public:
	light(Vector3f p, Vector3f i);
	~light();
	Vector3f position;
	Vector3f illumination;
};

