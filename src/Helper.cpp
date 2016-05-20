#include "Sample.h"

double Sample::hermite1(double x, double y0, double y1, double y2, double y3) {

    // 4-point, 3rd-order Hermite (x-form)
    double c0 = y1;
    double c1 = 0.5f * (y2 - y0);
    double c2 = y0 - 2.5f * y1 + 2.f * y2 - 0.5f * y3;
    double c3 = 1.5f * (y1 - y2) + 0.5f * (y3 - y0);

    return ((c3 * x + c2) * x + c1) * x + c0;
}
