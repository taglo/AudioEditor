#include <windef.h>

#include "Sample.h"
#include "helper/rbjFilter.h"

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


    double okLength = ((double) fxLength()) - 3;
    double pitch = okLength / ((double) splOut.fxLength());

    double jRead = ((double) fxIStart) + 2;

    int iRead = 0,iTmp;
    //double x, y0, y1, y0, y2, y0, y3;


    for (int i = splOut.fxIStart; i < splOut.fxIEnd; i++) {

        iRead = (int) jRead;
        iTmp =iRead+ 1;

        splOut.data[i] = hermite1(jRead - ((double) iRead), data[iTmp--], data[iTmp--],  data[iTmp--],  data[iTmp]);

        jRead += pitch;

    }

    return *this;

}

void Sample::getSampleForHermite(double jRead, int iMin, int iMax, double *dataIn, double& x, double& y0, double& y1, double& y2, double& y3) {
    int iRead = (int) jRead, iTmp;
    x = jRead - ((double) iRead);

    y2 = dataIn[iRead];
    iTmp = iRead - 2;
    if (iTmp >= iMin) {
        y0 = dataIn[iTmp++];
        y1 = dataIn[iTmp];
    } else {
        iTmp++;
        if (iTmp >= iMin) {
            y0 = dataIn[iTmp];
            y1 = dataIn[iTmp];
        } else {
            y0 = y2;
            y1 = y2;
        }
    }
    iTmp = iRead + 1;
    if (iTmp < iMax) {
        y3 = dataIn[iTmp];
    } else {
        y3 = y2;
    }
}

Sample& Sample::filterLowPass(double f, double q, int nPass) {

    RbjFilter* rbjFilter = new RbjFilter[nPass];

    rbjFilter[0].calc_filter_coeffs(0, f, (double) samplerate, q, 0, false);

    for (int j = 1; j < nPass; j++) {
        rbjFilter[j].copy_filter_coeffs(rbjFilter[0]);
    }

    for (int i = fxIStart; i < fxIEnd; i++) {
        for (int j = 0; j < nPass; j++) {
            data[i] = rbjFilter[j].filter(data[i]);
        }
    }

    delete[] rbjFilter;

    return *this;

}

Sample& Sample::filterLowPassFEnv(double f, Sample& fEnv, double fAmp, double q, int nPass) {

    double fD;
    int jRead = fEnv.fxIStart;

    RbjFilter* rbjFilter = new RbjFilter[nPass];


    for (int i = fxIStart; i < fxIEnd; i++) {

        fD = f + fEnv.data[jRead++] * fAmp;

        rbjFilter[0].calc_filter_coeffs(0, fD, (double) samplerate, q, 0, false);

        for (int j = 1; j < nPass; j++) {
            rbjFilter[j].copy_filter_coeffs(rbjFilter[0]);
        }

        for (int j = 0; j < nPass; j++) {
            data[i] = rbjFilter[j].filter(data[i]);
        }
    }

    delete[] rbjFilter;

    return *this;

}