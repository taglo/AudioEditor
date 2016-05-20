#include "Sample.h"

Sample& Sample::clip(double maxValue, double minValue) {


    for (int i = fxIStart; i < fxIEnd; i++) {
        if (data[i] > maxValue) {
            data[i] = maxValue;
        } else if (data[i] < minValue) {
            data[i] = minValue;
        }
    }

    return *this;
}

Sample& Sample::strech(Sample& splOut) {


    double pitch = ((double) fxLength()) / ((double) splOut.fxLength());
    double jRead = (double) fxIStart;
    int iRead = 0;
    double y0 = 0, y1 = 0, y2 = 0, y3 = 0;

    for (int i = splOut.fxIStart; i < splOut.fxIEnd; i++) {

        y3 = y2;
        y2 = y1;
        y1 = y0;

        iRead = (int) jRead;
        y0 = data[iRead];

        splOut.data[i] = hermite1(jRead - (double) iRead, y0, y1, y2, y3);
        
        jRead += pitch;

    }
    
    return *this;

}