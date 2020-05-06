#include "stdafx.h"
#include "surface.h"


surface::surface()
{
}

surface::surface(Vector3f ka, Vector3f kd, Vector3f ks, Vector3f p):k_ambient(ka),k_diffuse(kd),k_specular(ks),phong(p)
{
}


surface::~surface()
{
}

bool surface::hit(Vector3f origin, Vector3f direction, float t0, float t1, hitrecord& rec)
{
	bool hitflag = false;
	surface * it = children;
	while (it)
	{
		hitrecord rec_local;
		hitflag = it->hit(origin, direction, t0, t1, rec_local) || hitflag ;
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
