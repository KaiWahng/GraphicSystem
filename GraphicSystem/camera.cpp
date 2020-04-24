#include "stdafx.h"
#include "camera.h"
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;


camera::camera(vector3 vp, vector3 v_set, vector3 w_set)
{
	viewposition = vp;
	v = v_set;
	w = w_set;
	focallen = sqrt(w*w);
	//Allocate big array in heap
	image = new char [viewport_width *viewport_height*4];
}


camera::~camera()
{
	delete [] image;
}

void camera::photo(surface * scene, light * light)
{
	for (int i = 0; i < viewport_height; i++)
	{
		for (int j = 0; j < viewport_width; j++)
		{
			hitrecord rec;
			vector3 d = calculate_direction(viewposition, focallen,i, j);
			vector3 result;
			if (scene->hit(viewposition, d, 1, 1000, rec))
			{
				vector3 p = viewposition + d*rec.t;
				vector3 l = light->position - p;
				hitrecord srec;
				if (!scene->hit(p, l, 0.01, INFINITY, srec))
				{
					l.normalize();
					//d = d*-1;
					//d.normalize();
					//vector3 h = (l+d);
					//h.normalize();
					float ag_diffuse = rec.normal*l;
					if (ag_diffuse > 0)
						result = rec.k_diffuse^light->illumination*ag_diffuse;
				}
			}
			int index = i*viewport_width *4 + j*4;
			if (i == 237 && j == 467)
				while (0);
			image[index + 0] = char(result[0] * 255);
			image[index + 1] = char(result[1] * 255);
			image[index + 2] = char(result[2] * 255);
			image[index + 3] = 255;
			//image[index + 0] = 0;
			//image[index + 1] = 255;
			//image[index + 2] = 0;
			//image[index + 3] = 255;


		}
	}
	// ofstream(in text mode) will add "0x0D" infront of "0x0A" to prevent convert to line feed
	ofstream myfile("pic.raw", std::ios_base::out | std::ios_base::binary);
	if (myfile.is_open())
	{
		for (int count = 0; count < viewport_height*viewport_width*4; count++) {
			if (count == 760272)
				while (0);
			myfile << image[count];
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}

vector3 camera::calculate_direction(vector3 origin, float f, int i, int j)
{
	return (vector3(origin[0] - f, j- viewport_width /2, viewport_height /2-i) - origin);
}
