#include "trykutnyk.h"
#include <cmath>

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle &t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2.0;
    double arg = s * (s - a) * (s - b) * (s - c);
    if (arg < 0) arg = fabs(arg);
    return sqrt(arg);
}

double Triangle::area() const {
    return shoelaceArea();
}

double Triangle::shoelaceArea() const {
    return fabs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2.0);
}

bool Triangle::checkConsistency() const {
    return fabs(shoelaceArea() - heronArea(*this)) < 1e-6;
}

bool Vyrodzhenyi(const Triangle &t) {
    double cross = (t.B.x - t.A.x) * (t.C.y - t.A.y)
                 - (t.B.y - t.A.y) * (t.C.x - t.A.x);
    double ab = distance(t.A, t.B);
    double ac = distance(t.A, t.C);
    return fabs(cross) < 1e-15 * ab * ac;
}

static bool onSegment(const Point &A, const Point &B, const Point &P) {
    double cross = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
    double len = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
    if (fabs(cross) > 1e-6 * len) return false;

    if (P.x < fmin(A.x, B.x) - 1e-9 || P.x > fmax(A.x, B.x) + 1e-9) return false;
    if (P.y < fmin(A.y, B.y) - 1e-9 || P.y > fmax(A.y, B.y) + 1e-9) return false;
    return true;
}

int Triangle::onBorder(const Point &P) const {
    if (onSegment(A, B, P)) return 1;
    if (onSegment(B, C, P)) return 1;
    if (onSegment(C, A, P)) return 1;
    return 0;
}

bool Triangle::contains(const Point &P) const {
    if (Vyrodzhenyi(*this)) return false;

    double d1 = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
    double d2 = (C.x - B.x) * (P.y - B.y) - (C.y - B.y) * (P.x - B.x);
    double d3 = (A.x - C.x) * (P.y - C.y) - (A.y - C.y) * (P.x - C.x);

    bool allPos = (d1 >= -1e-9) && (d2 >= -1e-9) && (d3 >= -1e-9);
    bool allNeg = (d1 <= 1e-9)  && (d2 <= 1e-9)  && (d3 <= 1e-9);

    return allPos || allNeg;
}

bool Triangle::containsHeron(const Point &P) const {
    if (Vyrodzhenyi(*this)) return false;

    Triangle t1 = {A, B, P};
    Triangle t2 = {B, C, P};
    Triangle t3 = {C, A, P};

    double sumAreas = t1.shoelaceArea() + t2.shoelaceArea() + t3.shoelaceArea();
    double totalArea = shoelaceArea();

    return fabs(sumAreas - totalArea) < 1e-9 * totalArea + 1e-15;
}