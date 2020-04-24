#pragma once
#include "vector.h"
class vector3 :
	public vector
{
public:
	vector3(float v0 = 0, float v1 = 0, float v2 = 0);
	~vector3();
	vector3 crossproduct(const vector3 v3);
	void normalize();
	float& operator [] (const int i);
	void operator = (const vector3 v3);
	vector3 operator / (float f);
	vector3 operator - (vector3 v3);
	vector3 operator + (vector3 v3);
	vector3 operator * (float f);
	float operator * (vector3 v3);
	vector3 operator ^ (vector3 v3);
private:
	float value[3];
};

