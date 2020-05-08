// GraphicSystem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "hitrecord.h"
#include "surface.h"
#include "triangle.h"
#include "camera.h"
#include "sphere.h"
#include "light.h"
#include "CommonWindows.h"
#include <iostream>
#include <fstream>
#include "Eigen\Dense"
using namespace::Eigen;

int main()
{
	Vector3f kd(0, 0.5, 0);
	Vector3f ks(0.5, 1, 0.5);
	Vector3f kd_t(1, 1, 1);
	Vector3f dummy(0,0,0);
	float phong1 = 3;
	float phong2 = 200;
	Vector4f a(-100, -50, 50, 1);
	Vector4f b(-100, 50, 50, 1);
	Vector4f c(-100, -50, -50, 1);
	Vector4f d(-100, 50, -50, 1);
	Vector4f e(-200, -50, 50, 1);
	Vector4f f(-200, 50, 50, 1);
	Vector4f g(-200, -50, -50, 1);
	Vector4f h(-200, 50, -50, 1);
	Vector4f p1_3(-1000, -1000, -100, 1);
	Vector4f p1_1(1000, 1000, -100, 1);
	Vector4f p1_2(-1000, 1000, -100, 1);
	Vector4f p1_4(1000, -1000, -100, 1);
	triangle tri11(&a, &c, &b, kd_t, kd_t, kd_t, phong1, 11);
	triangle tri12(&d, &b, &c, kd_t, kd_t, kd_t, phong1,12);
	triangle tri21(&b, &d, &f, kd_t, kd_t, kd_t, phong1,21);
	triangle tri22(&h, &f, &d, kd_t, kd_t, kd_t, phong1,22);
	triangle tri31(&a, &b, &e, kd_t, kd_t, kd_t, phong1,31);
	triangle tri32(&f, &e, &b, kd_t, kd_t, kd_t, phong1,32);
	triangle tri41(&g, &e, &h, kd_t, kd_t, kd_t, phong1,41);
	triangle tri42(&f, &h, &e, kd_t, kd_t, kd_t, phong1,42);
	triangle tri51(&a, &e, &c, kd_t, kd_t, kd_t, phong1,51);
	triangle tri52(&g, &c, &e, kd_t, kd_t, kd_t, phong1,52);
	triangle tri61(&c, &g, &d, kd_t, kd_t, kd_t, phong1,61);
	triangle tri62(&h, &d, &g, kd_t, kd_t, kd_t, phong1,62);
	triangle plane1_1(&p1_1, &p1_2, &p1_4, kd_t, kd_t, kd_t, phong1, 62);
	triangle plane1_2(&p1_3, &p1_4, &p1_2, kd_t, kd_t, kd_t, phong1, 62);

	surface cube;
	cube.children = &tri11;
	tri11.sibling = &tri12;
	tri12.sibling = &tri21;
	tri21.sibling = &tri22;
	tri22.sibling = &tri31;
	tri31.sibling = &tri32;
	tri32.sibling = &tri41;
	tri41.sibling = &tri42;
	tri42.sibling = &tri51;
	tri51.sibling = &tri52;
	tri52.sibling = &tri61;
	tri61.sibling = &tri62;

	//cube.children = &tri32;
	//tri32.sibling = &tri31;
	//tri31.sibling = &tri11;
	//tri11.sibling = &tri12;
	//a = Vector3f(-100, -50, 350);
	//b = Vector3f(-100, 50, 350);
	//c = Vector3f(-100, -50, 250);
	//d = Vector3f(-100, 50, 250);

	//triangle tri2(a, c, b, dummy, kd_t, dummy, dummy);
	//triangle tri3(b, c, d, dummy, kd_t, dummy, dummy);

	//a = Vector3f(-100, -50, -250);
	//b = Vector3f(-100, 50, -250);
	//c = Vector3f(-100, -50, -350);
	//d = Vector3f(-100, 50, -350);
	//triangle tri4(a, c, b, dummy, kd_t, dummy, dummy);
	//triangle tri5(b, c, d, dummy, kd_t, dummy, dummy);

	//a = Vector3f(-100, -350, 50);
	//b = Vector3f(-100, -250, 50);
	//c = Vector3f(-100, -350, -50);
	//d = Vector3f(-100, -250, -50);
	//triangle tri6(a, c, b, dummy, kd_t, dummy, dummy);
	//triangle tri7(b, c, d, dummy, kd_t, dummy, dummy);

	//a = Vector3f(0, 350, 50);
	//b = Vector3f(0, 450, 50);
	//c = Vector3f(0, 350, -50);
	//d = Vector3f(0, 450, -50);
	//triangle tri8(a, c, b, dummy, kd_t, dummy, dummy);
	//triangle tri9(b, c, d, dummy, kd_t, dummy, dummy);
	
	sphere s0(&Vector4f(0, 100, 100, 1), 50, kd, kd, ks, phong2);
	sphere s1(&Vector4f(0, 0, 0, 1), 20, kd, kd, ks, phong2);
	sphere s2(&Vector4f(0, 400, 0, 1), 20, kd, kd, ks, phong2);
	sphere s3(&Vector4f(0, 100, 70, 1), 20, kd, kd, ks, phong2);
	sphere s4(&Vector4f(0, -100, 0, 1), 20, kd, kd, ks, phong2);
	sphere s5(&Vector4f(0, 0, -100, 1), 20, kd, kd, ks, phong2);
	sphere s6(&Vector4f(0, 0, 0, 1), 50, kd, kd, ks, phong2);

	//tri0.sibling = &s0;
	s0.sibling = &s1;
	s1.sibling = &s2;
	s2.sibling = &s3;
	s3.sibling = &s4;
	s4.sibling = &s5;
	cube.sibling = &s0;

	s5.sibling = &plane1_1;
	plane1_1.sibling = &plane1_2;
	surface scene;
	light la(&Vector4f(0, 0, 0, 1), Vector3f(0.1, 0.1, 0.1));
	light l0(&Vector4f(500, 0, 500, 1), Vector3f(0.5, 0.5, 0.5));
	light l1(&Vector4f(500, 0, 0, 1), Vector3f(0.5, 0.5, 0.5));
	light l2(&Vector4f(500, 500, 0, 1), Vector3f(0.5, 0.5, 0.5));
	l0.sibling = &l1;
	l1.sibling = &l2;
	Vector3f bg(0.1, 0.1, 0.1);
	scene.children = &cube;
	camera ca(&Vector4f(100,100,100, 1), &Vector4f(0, 0, 1, 0), &Vector4f(-50, 0, 0, 0));
	char * fn = new char[12];
	windowDemo myDemo = windowDemo();
	window_t* mywindowIns = myDemo.pCreateWindow("Viewer", 800, 400);
	stframebuffer *framebuffer;
	framebuffer = (stframebuffer*)malloc(sizeof(stframebuffer));
	framebuffer->width = 800;
	framebuffer->height = 480;
	framebuffer->colorbuffer = ca.image;

	std::cout << "test" << std::endl;
	for (int i = -300; i < 300; i+=5)
	{
		std::string index = std::to_string(i);
		//sprintf_s(fn, 12, "pic%03d.raw", i);
		l0.position[1] = i;
		ca.photo(&scene, &l0, &la, &bg);	
		myDemo.vdraw_buffer(mywindowIns, framebuffer);
		// ofstream(in text mode) will add "0x0D" infront of "0x0A" to prevent convert to line feed
		/*std::ofstream myfile("Pic000.raw", std::ios_base::out | std::ios_base::binary);
		if (myfile.is_open())
		{
			for (int count = 0; count < viewport_height*viewport_width; count++) {
				myfile << char(ca.image[count][0]+0.5f);
				myfile << char(ca.image[count][1]+0.5f);
				myfile << char(ca.image[count][2]+0.5f);
			}
			myfile.close();
		}
		else std::cout << "Unable to open file";*/
	}	
    return 0;
}

