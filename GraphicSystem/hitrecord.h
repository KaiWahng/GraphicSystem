#pragma once
#include <Eigen\Dense>
using namespace::Eigen;
class hitrecord
{
public:
	hitrecord();
	~hitrecord();
	float t;
	Vector3f normal;
	Vector3f k_ambient;
	Vector3f k_diffuse;
	Vector3f k_specular;
	Vector3f phong;
};

