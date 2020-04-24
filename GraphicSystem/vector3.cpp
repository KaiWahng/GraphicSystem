#include "stdafx.h"
#include "vector3.h"
#include <math.h>

vector3::vector3(float v0, float v1, float v2)
{
	value[0] = v0;
	value[1] = v1;
	value[2] = v2;
}

vector3::~vector3()
{
}

vector3 vector3::crossproduct(const vector3 v3)
{
	vector3 result;
	result[0] = value[1] * v3.value[2] - value[2] * v3.value[1];
	result[1] = value[2] * v3.value[0] - value[0] * v3.value[2];
	result[2] = value[0] * v3.value[1] - value[1] * v3.value[0];
	return result;
}

void vector3::normalize()
{
	float len = sqrt(value[0]* value[0] + value[1]* value[1] + value[2]*value[2]);
	value[0] /= len;
	value[1] /= len;
	value[2] /= len;
}

float& vector3::operator[](const int i)
{
	return value[i];
}

void vector3::operator=(const vector3 v3)
{
	value[0] = v3.value[0];
	value[1] = v3.value[1];
	value[2] = v3.value[2];
}

vector3 vector3::operator/(float f)
{
	return vector3(value[0] / f, value[1] / f, value[2] / f);
}

vector3 vector3::operator-(vector3 v3)
{
	return vector3(value[0]-v3.value[0], value[1] - v3.value[1], value[2] - v3.value[2]);
}

vector3 vector3::operator+(vector3 v3)
{
	return vector3(value[0] + v3.value[0], value[1] + v3.value[1], value[2] + v3.value[2]);
}

vector3 vector3::operator*(float f)
{
	return vector3(value[0] * f, value[1] * f, value[2] * f);
}

float vector3::operator*(vector3 v3)
{
	return value[0] * v3.value[0]+value[1] * v3.value[1]+value[2] * v3.value[2];
}

vector3 vector3::operator^(vector3 v3)
{
	return vector3(value[0]*v3.value[0], value[1] * v3.value[1], value[2] * v3.value[2]);
}
