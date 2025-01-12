#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line {
public:
    Point start;
    Point end;
    Point center;
    float length;

    Line() = default;
    Line(Point start, Point end);
    ~Line() = default;
    Line copy();
    void move(int horizontal, int vertical);
    void rotate(Point pivot, float delta_angle);
    void draw(Screen* screen, Color color);
};

#endif
