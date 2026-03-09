#ifndef TRYKUTNYK_H
#define TRYKUTNYK_H

#include <cmath>

struct Point {
    double x, y;
};

struct Triangle {
    Point A, B, C;
};

double Vidstan(Point p1, Point p2);
double Geron(Triangle t);
bool Vyrodzhenyi(Triangle t);
int VekDobytok(Triangle t, Point p);

#endif