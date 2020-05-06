#pragma once
#include "vector.h"
class Vector3f :
	public vector
{
public:
	Vector3f(float v0 = 0, float v1 = 0, float v2 = 0);
	~Vector3f();
	Vector3f crossproduct(const Vector3f v3);
	void normalize();
	float& operator [] (const int i);
	void operator = (const Vector3f v3);
	Vector3f operator / (float f);
	Vector3f operator - (Vector3f v3);
	Vector3f operator + (Vector3f v3);
	Vector3f operator * (float f);
	float operator * (Vector3f v3);
	Vector3f operator ^ (Vector3f v3);
private:
	float value[3];
};

