#include "stdafx.h"
#include "Vector3f.h"
#include <math.h>

Vector3f::Vector3f(float v0, float v1, float v2)
{
	value[0] = v0;
	value[1] = v1;
	value[2] = v2;
}

Vector3f::~Vector3f()
{
}

Vector3f Vector3f::crossproduct(const Vector3f v3)
{
	Vector3f result;
	result[0] = value[1] * v3.value[2] - value[2] * v3.value[1];
	result[1] = value[2] * v3.value[0] - value[0] * v3.value[2];
	result[2] = value[0] * v3.value[1] - value[1] * v3.value[0];
	return result;
}

void Vector3f::normalize()
{
	float len = sqrt(value[0]* value[0] + value[1]* value[1] + value[2]*value[2]);
	value[0] /= len;
	value[1] /= len;
	value[2] /= len;
}

float& Vector3f::operator[](const int i)
{
	return value[i];
}

void Vector3f::operator=(const Vector3f v3)
{
	value[0] = v3.value[0];
	value[1] = v3.value[1];
	value[2] = v3.value[2];
}

Vector3f Vector3f::operator/(float f)
{
	return Vector3f(value[0] / f, value[1] / f, value[2] / f);
}

Vector3f Vector3f::operator-(Vector3f v3)
{
	return Vector3f(value[0]-v3.value[0], value[1] - v3.value[1], value[2] - v3.value[2]);
}

Vector3f Vector3f::operator+(Vector3f v3)
{
	return Vector3f(value[0] + v3.value[0], value[1] + v3.value[1], value[2] + v3.value[2]);
}

Vector3f Vector3f::operator*(float f)
{
	return Vector3f(value[0] * f, value[1] * f, value[2] * f);
}

float Vector3f::operator*(Vector3f v3)
{
	return value[0] * v3.value[0]+value[1] * v3.value[1]+value[2] * v3.value[2];
}

Vector3f Vector3f::operator^(Vector3f v3)
{
	return Vector3f(value[0]*v3.value[0], value[1] * v3.value[1], value[2] * v3.value[2]);
}
