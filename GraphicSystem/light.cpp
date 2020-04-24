#include "stdafx.h"
#include "light.h"


light::light(vector3 p, vector3 i)
{
	position = p;
	illumination = i;
}


light::~light()
{
}
