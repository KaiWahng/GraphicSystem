#pragma once

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#include <iostream>
#include <Eigen/Dense>
using namespace::Eigen;

typedef enum { KEY_A, KEY_D, KEY_S, KEY_W, KEY_SPACE, KEY_NUM } keycode_t;
typedef enum { BUTTON_L, BUTTON_R, BUTTON_NUM } button_t;
typedef struct stwindow window_t;

typedef struct {
    unsigned int width;
    unsigned int height;
    //color channel
    unsigned int channels;
    unsigned char *buffer;
}
image_t;

typedef struct {
    void(*key_callback)(window_t *window, keycode_t key, int pressed);
    void(*button_callback)(window_t *window, button_t button, int pressed);
    void(*scroll_callback)(window_t *window, float offset);
} callbacks_t;

typedef struct {
    int width, height;
    Vector3f *colorbuffer;
} stframebuffer;

class windowDemo
{
public:
    windowDemo() :
        m_title(nullptr),
        m_Width(0),
        m_Height(0)
    {

    }
    ~windowDemo()
    {
    }

    /**
    * release window.
    */
    void vdestory();

    /**
    * create window.
    */
    static window_t* pCreateWindow(const char* title_, int Width, int Height);

    /**
    * window process the key/button input event.
    */
    static LRESULT CALLBACK vWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    static void vdraw_buffer(window_t *window, stframebuffer *buffer);

    static Vector3f GetBufferValue(stframebuffer *buffer, int row, int col);
    /**
    * Returns the current width of the window.
    */
    inline unsigned int GetWinWidth() const { return m_Width; }

    /**
    * Returns the current height of the window.
    */
    inline unsigned int GetWinHeight() const { return m_Height; }

private:
    unsigned int m_Width;
    unsigned int m_Height;
    const char* m_title;

    /**
    * Create the surface for this window.
    */
    static void vCreateSurface(HWND handle, int width, int height, image_t **out_surface, HDC *out_memory_dc);

    /**
    * register window.
    */
    static void register_class();

    /**
    * create window handle.
    */
    static HWND vCreateWinHandle(const char* title, int m_Width, int m_Height);

    /**
    * Display the buffer.
    */
    static void vDisplaySurface(window_t *window);

    /**
    * Trans the float to unsigned char.
    */
    static unsigned char vfloat2uchar(float value);

    static unsigned char *GetPixel(image_t *image, int row, int col);
};