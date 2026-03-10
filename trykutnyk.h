#ifndef TRYKUTNYK_H
#define TRYKUTNYK_H

#include <cmath>

struct Point {
    double x, y;
};

double distance(const Point &p1, const Point &p2);

struct Triangle {
    Point A, B, C;

    double area() const;
    double shoelaceArea() const;
    bool checkConsistency() const;

    bool contains(const Point &P) const;
    bool containsHeron(const Point &P) const;

    int onBorder(const Point &P) const;
};

double heronArea(const Triangle &t);
bool Vyrodzhenyi(const Triangle &t);

#endif