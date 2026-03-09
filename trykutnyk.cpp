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
    return heronArea(*this);
}

bool Vyrodzhenyi(const Triangle &t) {
    return heronArea(t) < 1e-9;
}

bool Triangle::contains(const Point &P) const {
    Triangle T1 = {A, B, P};
    Triangle T2 = {B, C, P};
    Triangle T3 = {C, A, P};

    double S_main = area();
    double S_sum = T1.area() + T2.area() + T3.area();

    return fabs(S_main - S_sum) < 1e-9;
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