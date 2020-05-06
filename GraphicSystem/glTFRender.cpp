#include <iostream>
#include "CommonWindows.h"

static const char *WINDOW_TITLE = "Viewer";

void framebuffer_clear_color(stframebuffer *framebuffer, vec4 color) {
    int num_elems = framebuffer->width * framebuffer->height;
    int i;
    for (i = 0; i < num_elems; i++) {
        framebuffer->colorbuffer[i] = color;
    }
}

void framebuffer_clear_depth(stframebuffer *framebuffer, float depth) {
    int num_elems = framebuffer->width * framebuffer->height;
    int i;
    for (i = 0; i < num_elems; i++) {
        framebuffer->depthbuffer[i] = depth;
    }
}

int main()
{
    vec4 default_color = { 0, 100, 0, 1 };
    float default_depth = 1;
    int num_elems = 800 * 480;
    stframebuffer *framebuffer;

    framebuffer = (stframebuffer*)malloc(sizeof(stframebuffer));
    framebuffer->width = 800;
    framebuffer->height = 480;
    framebuffer->colorbuffer = (vec4*)malloc(sizeof(vec4) * num_elems);
    framebuffer->depthbuffer = (float*)malloc(sizeof(float) * num_elems);

    framebuffer_clear_color(framebuffer, default_color);
    framebuffer_clear_depth(framebuffer, default_depth);

    //create window
    windowDemo myDemo = windowDemo();
    window_t* mywindowIns = myDemo.pCreateWindow(WINDOW_TITLE, 800, 400);
    while (1)
    {
        myDemo.vdraw_buffer(mywindowIns, framebuffer);
    }
    std::cout << "test" << std::endl;

}