#include "stdafx.h"
#include "light.h"


light::light(Vector3f p, Vector3f i)
{
	position = p;
	illumination = i;
}


light::~light()
{
}
