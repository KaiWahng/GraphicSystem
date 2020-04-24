#include "stdafx.h"
#include "vector.h"


vector::vector()
{
}


vector::~vector()
{
}

float& vector::operator[](const int i)
{
	return _value;
}
