#ifndef SCREEN_H
#define SCREEN_H

#include <windows.h>
#include "Vertex.h"
#include "Color.h"

class Screen {
private:
    Vertex* vertexbuffer;
    uint32_t* framebuffer;
    HDC hdc;
    BITMAPINFO bmi;
    HBITMAP h_bitmap;

public:
    int height;
    int width;
    Screen() = default;
    Screen(int height, int width);
    ~Screen() = default;
    void set_pixel(int x, int y, Color color);
    void display();
};

#endif
