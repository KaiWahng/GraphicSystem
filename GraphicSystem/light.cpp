#include "stdafx.h"
#include "light.h"


light::light(const Vector4f *  p, Vector3f i)
{
	position = *p;
	illumination = i;
}


light::~light()
{
}
