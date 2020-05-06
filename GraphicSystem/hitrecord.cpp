#include "stdafx.h"
#include "hitrecord.h"


hitrecord::hitrecord():t(0), normal(0,0,0), k_ambient(0,0,0), k_diffuse(0,0,0), k_specular(0,0,0), phong(0,0,0)
{
}


hitrecord::~hitrecord()
{
}
