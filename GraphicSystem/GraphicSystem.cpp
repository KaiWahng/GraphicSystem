// GraphicSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "vector3.h"
#include "hitrecord.h"
#include "surface.h"
#include "triangle.h"
#include "camera.h"
#include "sphere.h"
#include "light.h"

int main()
{
	vector3 a(30, 100, 0);
	vector3 b(0, 130, 0);
	vector3 c(0, 100, 30);
	vector3 kd(0, 1, 0);
	vector3 dummy;
	triangle tri0(a, b, c, dummy, kd, dummy, dummy);
	sphere s0(vector3(0, 0, 50), 30, dummy, kd, dummy, dummy);
	sphere s1(vector3(0, 0, 0), 20, dummy, kd, dummy, dummy);
	sphere s2(vector3(0, 100, 0), 40, dummy, kd, dummy, dummy);

	//tri0.sibling = &s0;
	s0.sibling = &s1;
	s1.sibling = &s2;
	surface scene;
	light l0(vector3(0,0,100), vector3(1,1,1));
	scene.children = &s0;
	camera ca(vector3(100,0,0), vector3(0, 0, 1), vector3(-50, 0, 0));
	ca.photo(&scene, &l0);
    return 0;
}

