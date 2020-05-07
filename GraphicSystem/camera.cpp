#include "stdafx.h"
#include "camera.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

char cam_min(unsigned int a, unsigned int b)
{
	return a < b ? a : b;
}
camera::camera(const Vector4f *  vp, const Vector4f *  v_set, const Vector4f *  w_set)
{
	viewposition = *vp;
	v = *v_set;
	w = *w_set;
	focallen = w.norm();
	//Allocate big array in heap
	image = new Vector3f [viewport_width *viewport_height];
}


camera::~camera()
{
	delete [] image;
}

void camera::photo(surface * scene, light * l_diffuse, light * l_ambient, Vector3f * bg)
{
	for (int i = 0; i < viewport_height; i++)
	{
		for (int j = 0; j < viewport_width; j++)
		{
			hitrecord rec;
			Vector4f d = calculate_direction(&viewposition, focallen,i, j);
			Vector3f result(0,0,0);
			// Look for ray hit any object
			if (scene->hit(&viewposition, &d, 1, 1000, rec))
			{
				Vector4f p = viewposition + d*rec.t;
				Vector4f l = l_diffuse->position - p;
				hitrecord srec;
				// Shade the object - ambient
				result += rec.k_ambient.cwiseProduct(l_ambient->illumination);
				// Look for if there something block the object from been lightened
				if (!scene->hit(&p, &l, 0.01, INFINITY, srec))
				{

					// Shade the object - diffuse
					l.normalize();
					float ag_diffuse = rec.normal.dot(l);
					if (ag_diffuse > 0)
						result += rec.k_diffuse.cwiseProduct(l_diffuse->illumination)*ag_diffuse;
					
					// Shade the object - specular
					d = d*-1;
					d.normalize();
					Vector4f h = (l + d);
					h.normalize();
					float ag_specular = rec.normal.dot(h);
					if (ag_specular > 0)
						result += rec.k_specular.cwiseProduct(l_diffuse->illumination)*(pow(ag_specular, rec.phong));					
				}
			}
			else
				result = *bg;
			int index = i*viewport_width + j;
			image[index][0] = min(255, result[0] * 255);
			image[index][1] = min(255, result[1] * 255);
			image[index][2] = min(255, result[2] * 255);


		}
	}
	// ofstream(in text mode) will add "0x0D" infront of "0x0A" to prevent convert to line feed
	//ofstream myfile(filename, std::ios_base::out | std::ios_base::binary);
	//if (myfile.is_open())
	//{
	//	for (int count = 0; count < viewport_height*viewport_width*3; count++) {
	//		myfile << image[count];
	//	}
	//	myfile.close();
	//}
	//else cout << "Unable to open file";
}


Vector4f camera::calculate_direction(const Vector4f * origin, float f, int i, int j)
{
	return (Vector4f((*origin)[0] - f, j- viewport_width /2, viewport_height /2-i, 1) - *origin);
}
