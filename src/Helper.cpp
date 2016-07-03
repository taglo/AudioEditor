#include "Sample.h"

double Sample::hermite1(double x, double y0, double y1, double y2, double y3) {

    // 4-point, 3rd-order Hermite (x-form)
    double c0 = y1;
    double c1 = 0.5f * (y2 - y0);
    double c2 = y0 - 2.5f * y1 + 2.f * y2 - 0.5f * y3;
    double c3 = 1.5f * (y1 - y2) + 0.5f * (y3 - y0);

    return ((c3 * x + c2) * x + c1) * x + c0;
}


// laurent de soras

double Sample::hermite4(double frac_pos, double xm1, double x0, double x1, double x2) {

    // xm1 ---> x[n-1] x0 ---> x[n] x1 ---> x[n+1] x2 ---> x[n+2] fractional position stands for a fraction between 0 and 1 to interpolate

    double c = (x1 - xm1) * 0.5f;
    double v = x0 - x1;
    double w = c + v;
    double a = w + v + (x2 - x0) * 0.5f;
    double b_neg = w + a;

    return ((((a * frac_pos) - b_neg) * frac_pos + c) * frac_pos + x0);
}