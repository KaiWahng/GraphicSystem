#include "stdafx.h"
#include "surface.h"


surface::surface()
{
}

surface::surface(vector3 ka, vector3 kd, vector3 ks, vector3 p):k_ambient(ka),k_diffuse(kd),k_specular(ks),phong(p)
{
}


surface::~surface()
{
}

bool surface::hit(vector3 origin, vector3 direction, float t0, float t1, hitrecord& rec)
{
	hitrecord rec_local;
	bool hitflag = false;
	surface * it = children;
	while (it)
	{
		hitflag = hitflag || it->hit(origin, direction, t0, t1, rec_local);
		if (hitflag && rec_local.t > 0)
		{
			if (rec_local.t < rec.t || rec.t == 0)
			{
				rec = rec_local;
			}
		}
		it = it->sibling;
	}
	return hitflag;
}
