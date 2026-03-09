#include "trykutnyk.h"

double Vidstan(Point p1, Point p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double Geron(Triangle t) {
    double a = Vidstan(t.A, t.B);
    double b = Vidstan(t.B, t.C);
    double c = Vidstan(t.C, t.A);
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

bool Vyrodzhenyi(Triangle t) {
    return Geron(t) < 1e-9;
}

int VekDobytok(Triangle t, Point p) {
    double d1 = (t.B.x - t.A.x) * (p.y - t.A.y) - (t.B.y - t.A.y) * (p.x - t.A.x);
    double d2 = (t.C.x - t.B.x) * (p.y - t.B.y) - (t.C.y - t.B.y) * (p.x - t.B.x);
    double d3 = (t.A.x - t.C.x) * (p.y - t.C.y) - (t.A.y - t.C.y) * (p.x - t.C.x);

    if (fabs(d1) < 1e-9 || fabs(d2) < 1e-9 || fabs(d3) < 1e-9)
        return 2; 

    if ((d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0))
        return 1; 

    return 0; 
}