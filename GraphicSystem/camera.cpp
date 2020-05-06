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
camera::camera(Vector3f vp, Vector3f v_set, Vector3f w_set)
{
	viewposition = vp;
	v = v_set;
	w = w_set;
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
			if (i == 85 && j == 444)
				while (0);
			hitrecord rec;
			Vector3f d = calculate_direction(viewposition, focallen,i, j);
			Vector3f result(0,0,0);
			if (scene->hit(viewposition, d, 1, 1000, rec))
			{
				Vector3f p = viewposition + d*rec.t;
				Vector3f l = l_diffuse->position - p;
				hitrecord srec;
				result += rec.k_ambient.cwiseProduct(l_ambient->illumination);
				if (!scene->hit(p, l, 0.01, INFINITY, srec))
				{
					l.normalize();
					//d = d*-1;
					//d.normalize();
					//Vector3f h = (l+d);
					//h.normalize();
					float ag_diffuse = rec.normal.dot(l);
					if (ag_diffuse > 0)
						result += rec.k_diffuse.cwiseProduct(l_diffuse->illumination)*ag_diffuse;
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


Vector3f camera::calculate_direction(Vector3f origin, float f, int i, int j)
{
	return (Vector3f(origin[0] - f, j- viewport_width /2, viewport_height /2-i) - origin);
}
