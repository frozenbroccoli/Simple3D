#include <stdexcept>
#include <cmath>
#include <cstring>
#include "Rendering/Screen.h"


Screen::Screen(int h, int w) {
    if (w <= 0 || h <= 0) {
        throw std::invalid_argument("Screen dimensions must be positive");
    }
    width = w;
    height = h;
    hdc = GetDC(NULL);
    if (!hdc) {
        throw std::runtime_error("Failed to get DC");
    }

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage = 0;
    bmi.bmiHeader.biXPelsPerMeter = 0;
    bmi.bmiHeader.biYPelsPerMeter = 0;
    bmi.bmiHeader.biClrUsed = 0;
    bmi.bmiHeader.biClrImportant = 0;

    h_bitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&framebuffer, NULL, 0);
    if (!h_bitmap) {
        throw std::runtime_error("Failed to create DIB section");
    }
}

Screen::~Screen() {
    if (h_bitmap) {
        DeleteObject(h_bitmap);
    }
    if (hdc) {
        ReleaseDC(NULL, hdc);
    }
}

void Screen::set_pixel(int x, int y, Color color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::runtime_error("Index out of bounds of screen size");
    }

    int offset = (y * width + x) * 4;
    framebuffer[offset] = color.b;
    framebuffer[offset + 1] = color.g;
    framebuffer[offset + 2] = color.r;
}

void Screen::clear() {
    std::memset(reinterpret_cast<void*>(framebuffer), 0, width * height * 4);
}

void Screen::display() {
    HDC mem_dc = CreateCompatibleDC(hdc);
    if (!mem_dc) {
        throw std::runtime_error("Failed to create compatible DC");
    }

    if (!SelectObject(mem_dc, h_bitmap)) {
        DeleteDC(mem_dc);
        throw std::runtime_error("Failed to select bitmap into memory DC");
    }

    if (!BitBlt(hdc, 0, 0, width * 8, height, mem_dc, 0, 0, SRCCOPY)) {
        DeleteDC(mem_dc);
        throw std::runtime_error("Failed to blit to screen");
    }

    DeleteDC(mem_dc);
}


