#include "trykutnyk.h"
#include <cmath>

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle &t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    
    double arg = s * (s - a) * (s - b) * (s - c);
    if (arg < 0) arg = 0; // Захист від від'ємного значення через похибку
    return sqrt(arg);
}

double Triangle::area() const {
    return shoelaceArea();
}

double Triangle::shoelaceArea() const {
    return fabs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2.0);
}

bool Triangle::checkConsistency() const {
    return fabs(shoelaceArea() - heronArea(*this)) < EPS;
}

bool Vyrodzhenyi(const Triangle &t) {
    // Вироджений — якщо площа менша за нашу точність
   return t.shoelaceArea() < EPS;
}

static bool onSegment(const Point &A, const Point &B, const Point &P) {
    double cross = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
    if (fabs(cross) > EPS) return false; 

    if (P.x < fmin(A.x, B.x) - EPS || P.x > fmax(A.x, B.x) + EPS) return false;
    if (P.y < fmin(A.y, B.y) - EPS || P.y > fmax(A.y, B.y) + EPS) return false;
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

    // Враховуємо EPS, щоб межа входила в "contains"
    bool allPos = (d1 >= -EPS) && (d2 >= -EPS) && (d3 >= -EPS);
    bool allNeg = (d1 <= EPS) && (d2 <= EPS) && (d3 <= EPS);

    return allPos || allNeg;
}

bool Triangle::containsHeron(const Point &P) const {
    if (Vyrodzhenyi(*this)) return false;

    double sumAreas = heronArea({A, B, P}) + heronArea({B, C, P}) + heronArea({C, A, P});
    double totalArea = heronArea(*this);

    // Сувора перевірка на 1e-9
    return fabs(sumAreas - totalArea) < EPS;
}