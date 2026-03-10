#include "trykutnyk.h"

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle &t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::area() const {
    return shoelaceArea();
}

double Triangle::shoelaceArea() const {
    return fabs(
        (A.x * (B.y - C.y) +
         B.x * (C.y - A.y) +
         C.x * (A.y - B.y)) / 2.0
    );
}

bool Triangle::checkConsistency() const {
    double shoelace = shoelaceArea();
    double heron    = heronArea(*this);
    return fabs(shoelace - heron) < 1e-6;
}

bool Vyrodzhenyi(const Triangle &t) {
    return heronArea(t) < 1e-9;
}

static bool onSegment(const Point &A, const Point &B, const Point &P) {
    double cross = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
    if (fabs(cross) > 1e-9) return false;
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

    bool allPos = (d1 > 0) && (d2 > 0) && (d3 > 0);
    bool allNeg = (d1 < 0) && (d2 < 0) && (d3 < 0);

    return allPos || allNeg;
}

bool Triangle::containsHeron(const Point &P) const {
    if (Vyrodzhenyi(*this)) return false;

    Triangle t1 = {A, B, P};
    Triangle t2 = {B, C, P};
    Triangle t3 = {C, A, P};
    double sumAreas  = heronArea(t1) + heronArea(t2) + heronArea(t3);
    double totalArea = heronArea(*this);
    return fabs(sumAreas - totalArea) < 1e-6;
}