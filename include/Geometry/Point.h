#ifndef POINT_H
#define POINT_H

#include "../Rendering/Screen.h"
#include "../Rendering/Color.h"

class Point {
public:
    int x;
    int y;
    float r;
    float theta;

    Point() = default;
    Point(int x, int y);
    Point(float r, float theta);
    ~Point() = default;
    Point copy();
    void move(int horizontal, int vertical);
    void rotate(Point pivot, double delta_angle);
    void draw(Screen* screen, Color color);
};

#endif
