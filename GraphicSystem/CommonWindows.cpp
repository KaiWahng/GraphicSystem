#include "stdafx.h"
#include "CommonWindows.h"

#define int_min(x, y) x < y ? x : y


static const char *WINDOW_CLASS_NAME = "Class";
static const char *WINDOW_ENTRY_NAME = "Entry";


struct stwindow {
    HWND handle;
    HDC memory_dc;
    image_t *surface;
    /* common data */
    int should_close;
    char keys[KEY_NUM];
    char buttons[BUTTON_NUM];
    callbacks_t callbacks;
    void *userdata;
};

HWND windowDemo::vCreateWinHandle(const char* title_, int Width, int Height)
{
    DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    RECT rect;
    HWND handle;

    const char *title = title_;

    rect.left = 0;
    rect.top = 0;
    rect.right = Width;
    rect.bottom = Height;
    AdjustWindowRect(&rect, style, 0);
    Width = rect.right - rect.left;
    Height = rect.bottom - rect.top;

    handle = CreateWindow(L"xx", L"xx", style,
        CW_USEDEFAULT, CW_USEDEFAULT, Width, Height,
        NULL, NULL, GetModuleHandle(NULL), NULL);
    assert(handle != NULL);
    return handle;
}

void windowDemo::vCreateSurface(HWND handle, int Width, int Height,
    image_t **out_surface, HDC *out_memory_dc)
{
    image_t *pSurface;

    BITMAPINFOHEADER bi_header;
    HDC window_dc;
    HDC memory_dc;
    HBITMAP dib_bitmap;
    HBITMAP old_bitmap;
    unsigned char *buffer;

    window_dc = GetDC(handle);
    memory_dc = CreateCompatibleDC(window_dc);
    ReleaseDC(handle, window_dc);

    memset(&bi_header, 0, sizeof(BITMAPINFOHEADER));
    bi_header.biSize = sizeof(BITMAPINFOHEADER);
    bi_header.biWidth = Width;
    bi_header.biHeight = -Height;  /* top-down */
    bi_header.biPlanes = 1;
    bi_header.biBitCount = 32;
    bi_header.biCompression = BI_RGB;
    dib_bitmap = CreateDIBSection(memory_dc, (BITMAPINFO*)&bi_header,
        DIB_RGB_COLORS, (void**)&buffer, NULL, 0);
    assert(dib_bitmap != NULL);
    old_bitmap = (HBITMAP)SelectObject(memory_dc, dib_bitmap);
    DeleteObject(old_bitmap);

    pSurface = (image_t*)malloc(sizeof(image_t));
    pSurface->width = Width;
    pSurface->height = Height;
    pSurface->channels = 4;
    pSurface->buffer = buffer;

    *out_surface = pSurface;
    *out_memory_dc = memory_dc;
}

void windowDemo::register_class(void) {
    static int initialized = 0;
    if (initialized == 0) {
        ATOM class_atom;
        WNDCLASS window_class;
        window_class.style = CS_HREDRAW | CS_VREDRAW;
        //current we don't have the key message handle
        window_class.lpfnWndProc = vWindowProc;
        window_class.cbClsExtra = 0;
        window_class.cbWndExtra = 0;
        window_class.hInstance = GetModuleHandle(NULL);
        window_class.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
        window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
        window_class.lpszMenuName = NULL;
        window_class.lpszClassName = L"xx";
        class_atom = RegisterClass(&window_class);
        assert(class_atom != 0);
        initialized = 1;
    }
}

window_t* windowDemo::pCreateWindow(const char* title_, int Width, int Height) {
    window_t *pwindow;
    HWND handle;
    image_t *surface;
    HDC memory_dc;

    register_class();
    handle = windowDemo::vCreateWinHandle(title_, Width, Height);
    windowDemo::vCreateSurface(handle, Width, Height, &surface, &memory_dc);

    pwindow = (window_t*)malloc(sizeof(window_t));
    memset(pwindow, 0, sizeof(window_t));
    pwindow->handle = handle;
    pwindow->memory_dc = memory_dc;
    pwindow->surface = surface;

    SetProp(handle, L"xx", pwindow);
    ShowWindow(handle, SW_SHOW);
    return pwindow;
}

LRESULT CALLBACK windowDemo::vWindowProc(HWND hWnd, UINT uMsg,
    WPARAM wParam, LPARAM lParam) {
    window_t *window = (window_t*)GetProp(hWnd, L"xx");
    if (window == NULL) {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    else if (uMsg == WM_CLOSE) {
        window->should_close = 1;
        return 0;
    }
    else if (uMsg == WM_KEYDOWN) {
        //handle_key_message(window, wParam, 1);
        return 0;
    }
    else if (uMsg == WM_KEYUP) {
        //handle_key_message(window, wParam, 0);
        return 0;
    }
    else if (uMsg == WM_LBUTTONDOWN) {
       // handle_button_message(window, BUTTON_L, 1);
        return 0;
    }
    else if (uMsg == WM_RBUTTONDOWN) {
        //handle_button_message(window, BUTTON_R, 1);
        return 0;
    }
    else if (uMsg == WM_LBUTTONUP) {
        //handle_button_message(window, BUTTON_L, 0);
        return 0;
    }
    else if (uMsg == WM_RBUTTONUP) {
        //handle_button_message(window, BUTTON_R, 0);
        return 0;
    }
    else if (uMsg == WM_MOUSEWHEEL) {
        float offset = GET_WHEEL_DELTA_WPARAM(wParam) / (float)WHEEL_DELTA;
        //handle_scroll_message(window, offset);
        return 0;
    }
    else {
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

void windowDemo::vDisplaySurface(window_t *window) {
    HDC window_dc = GetDC(window->handle);
    HDC memory_dc = window->memory_dc;
    image_t *surface = window->surface;
    int width = surface->width;
    int height = surface->height;
    BitBlt(window_dc, 0, 0, width, height, memory_dc, 0, 0, SRCCOPY);
    ReleaseDC(window->handle, window_dc);
}

Vector3f windowDemo::GetBufferValue(stframebuffer *buffer, int row, int col) {
    int index = row * buffer->width + col;
    return buffer->colorbuffer[index];
}

void windowDemo::vdraw_buffer(window_t *window, stframebuffer *buffer) 
{
    int width = int_min(buffer->width, window->surface->width); 
    int height = int_min(buffer->height, window->surface->height);
    int r, c;
    for (r = 0; r < height; r++) {
        for (c = 0; c < width; c++) {
            int flipped_r = r;
            Vector3f src_value = windowDemo::GetBufferValue(buffer, flipped_r, c);
            unsigned char *dst_pixel = windowDemo::GetPixel(window->surface, r, c);
            dst_pixel[0] = windowDemo::vfloat2uchar(src_value[0]);  /* red */
            dst_pixel[1] = windowDemo::vfloat2uchar(src_value[1]);  /* green */
            dst_pixel[2] = windowDemo::vfloat2uchar(src_value[2]);  /* blue */
        }
    }

    windowDemo::vDisplaySurface(window);
}

unsigned char windowDemo::vfloat2uchar(float value) {
	return (unsigned char)(value + 0.5f);
}

unsigned char *windowDemo::GetPixel(image_t *image, int row, int col) {
    int index = row * image->width * image->channels + col * image->channels;
    return &(image->buffer[index]);
}