#include <windef.h>

#include "Sample.h"

Sample& Sample::clip(double maxValue, double minValue) {


    for (int i = fxIStart; i < fxIEnd; i++) {
        if (dataL[i] > maxValue) {
            dataL[i] = maxValue;
        } else if (dataL[i] < minValue) {
            dataL[i] = minValue;
        }
        if (dataR[i] > maxValue) {
            dataR[i] = maxValue;
        } else if (dataR[i] < minValue) {
            dataR[i] = minValue;
        }
    }

    return *this;
}

Sample& Sample::distoWaveShape(Sample& splWS, double ampL, double ampR) {

    double rl = ((double) splWS.fxLength()) / 2;
    double rc = ((double) splWS.fxIStart) + rl;


    double val;

    for (int i = fxIStart; i < fxIEnd; i++) {



        dataL[i] = distoWS(dataL[i] * ampL, splWS.dataL, rl, rc);
        dataR[i] = distoWS(dataR[i] * ampL, splWS.dataR, rl, rc);

    }

    return *this;
}

double Sample::distoWS(double val, double *WS, double rl, double rc) {
    double pread, frac_pos;
    int x0, xm1, x1, x2;

    if (val > 0.95) {
        val = 0.95;
    } else if (val<-0.95) {
        val = -0.95;
    }

    pread = rc + val*rl;

    x0 = (int) pread;

    frac_pos = pread - ((double) x0);
    xm1 = x0 - 1;
    x1 = x0 + 1;
    x2 = x1 + 2;

    return hermite4(frac_pos, WS[xm1], WS[x0], WS[x1], WS[x2]);
}

Sample& Sample::strech(Sample& splOut) {


    double okLength = ((double) fxLength()) - 2; //todo : pitch faux de 3/fxLength
    double pitch = okLength / ((double) splOut.fxLength());

    double jRead = ((double) fxIStart) + 2;

    //int iRead = 0, iTmp;
    //double x, y0, y1, y0, y2, y0, y3;


    for (int i = splOut.fxIStart; i < splOut.fxIEnd; i++) {

        int x0 = (int) jRead;

        double frac_pos = jRead - ((double) x0);
        int xm1 = x0 - 1;
        int x1 = x0 + 1;
        int x2 = x1 + 2;

        splOut.dataL[i] = hermite4(frac_pos, dataL[xm1], dataL[x0], dataL[x1], dataL[x2]);
        splOut.dataR[i] = hermite4(frac_pos, dataR[xm1], dataR[x0], dataR[x1], dataR[x2]);

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

Sample& Sample::delay(int length, double dry, double feedback) {
    Delay delay(length, dry, feedback);

    for (int i = fxIStart; i < fxIEnd; i++) {
        dataL[i] = delay.tick(dataL[i]);
    }

    return *this;
}

Sample& Sample::filterUtlRBJ(int type, double f, double q, int nPass) {
    RbjFilter* rbjFilter = new RbjFilter[nPass];

    rbjFilter[0].calc_filter_coeffs(type, f, (double) samplerate, q, 0, false);

    for (int j = 1; j < nPass; j++) {
        rbjFilter[j].copy_filter_coeffs(rbjFilter[0]);
    }

    for (int i = fxIStart; i < fxIEnd; i++) {
        for (int j = 0; j < nPass; j++) {
            rbjFilter[j].filter(dataL[i], dataR[i], dataL[i], dataR[i]);
        }
    }

    delete[] rbjFilter;

}

Sample& Sample::filterUtlRBJFEnv(int type, double f, Sample& fEnv, double fAmp, double q, int nPass) {
    double fD;
    int jRead = fEnv.fxIStart;

    RbjFilter* rbjFilter = new RbjFilter[nPass];


    for (int i = fxIStart; i < fxIEnd; i++) {

        fD = f + fEnv.dataL[jRead++] * fAmp;

        rbjFilter[0].calc_filter_coeffs(type, fD, (double) samplerate, q, 0, false);

        for (int j = 1; j < nPass; j++) {
            rbjFilter[j].copy_filter_coeffs(rbjFilter[0]);
        }

        for (int j = 0; j < nPass; j++) {
            rbjFilter[j].filter(dataL[i], dataR[i], dataL[i], dataR[i]);
        }
    }

    delete[] rbjFilter;
}

Sample& Sample::filterLowPass(double f, double q, int nPass) {

    filterUtlRBJ(0, f, q, nPass);
    return *this;

}

Sample& Sample::filterLowPassFEnv(double f, Sample& fEnv, double fAmp, double q, int nPass) {

    filterUtlRBJFEnv(0, f, fEnv, fAmp, q, nPass);

    return *this;

}

Sample& Sample::filterBandPass(double f, double q, int nPass) {

    filterUtlRBJ(2, f, q, nPass);
    return *this;

}

Sample& Sample::filterBandPassFEnv(double f, Sample& fEnv, double fAmp, double q, int nPass) {

    filterUtlRBJFEnv(2, f, fEnv, fAmp, q, nPass);

    return *this;

}

Sample& Sample::filterHiPass(double f, double q, int nPass) {

    filterUtlRBJ(1, f, q, nPass);
    return *this;

}

Sample& Sample::filterHiPassFEnv(double f, Sample& fEnv, double fAmp, double q, int nPass) {

    filterUtlRBJFEnv(1, f, fEnv, fAmp, q, nPass);

    return *this;

}

Sample& Sample::filterNotch(double f, double q, int nPass) {

    filterUtlRBJ(4, f, q, nPass);
    return *this;

}

Sample& Sample::filterNotchEnv(double f, Sample& fEnv, double fAmp, double q, int nPass) {

    filterUtlRBJFEnv(4, f, fEnv, fAmp, q, nPass);

    return *this;

}

Sample& Sample::filterAllPass(double f, double q, int nPass) {

    filterUtlRBJ(5, f, q, nPass);
    return *this;

}

Sample& Sample::filterAllPassEnv(double f, Sample& fEnv, double fAmp, double q, int nPass) {

    filterUtlRBJFEnv(5, f, fEnv, fAmp, q, nPass);

    return *this;

}