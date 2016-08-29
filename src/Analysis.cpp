#include "Sample.h"

Sample& Sample::extractEnvelope(int oneToZeroLength) {

    double mAmp = 1 / (double) oneToZeroLength;
    double maxL, maxR;

    maxL = 0;
    maxR = 0;

    RbjFilter rbjFilter;

    rbjFilter.calc_filter_coeffs(0, 10.0, (double) samplerate, 1, 0, false);

    // ->
    for (int i = fxIStart; i < fxIEnd; i++) {

        dataL[i] = fabs(dataL[i]);
        dataR[i] = fabs(dataR[i]);



        if (dataL[i] > maxL) {
            maxL = dataL[i];
        } else {
            dataL[i] = maxL;
        }

        if (dataR[i] > maxR) {
            maxR = dataR[i];
        } else {
            dataR[i] = maxR;
        }


        //rbjFilter.filter(dataL[i] , dataR[i], dataL[i] , dataR[i]);

        maxL -= mAmp;
        if (maxL < 0) maxL = 0;

        maxR -= mAmp;
        if (maxR < 0) maxR = 0;

        //rbjFilter.filter(maxL , maxR, dataL[i] , dataR[i]);
    }

    //<-
    maxL = 0;
    maxR = 0;
    for (int i = fxIEnd - 1; i >= fxIStart; i--) {

        if (dataL[i] > maxL) {
            maxL = dataL[i];
        } else {
            dataL[i] = maxL;
        }

        if (dataR[i] > maxR) {
            maxR = dataR[i];
        } else {
            dataR[i] = maxR;
        }

        rbjFilter.filter(dataL[i] , dataR[i], dataL[i] , dataR[i]);
        
        maxL -= mAmp;
        if (maxL < 0) maxL = 0;

        maxR -= mAmp;
        if (maxR < 0) maxR = 0;

    }

    return *this;
}

Sample& Sample::extractEnvelopeNoFilter(int oneToZeroLength) {

    double mAmp = 1 / (double) oneToZeroLength;
    double maxL, maxR;

    maxL = 0;
    maxR = 0;

    

    // ->
    for (int i = fxIStart; i < fxIEnd; i++) {

        dataL[i] = fabs(dataL[i]);
        dataR[i] = fabs(dataR[i]);



        if (dataL[i] > maxL) {
            maxL = dataL[i];
        } else {
            dataL[i] = maxL;
        }

        if (dataR[i] > maxR) {
            maxR = dataR[i];
        } else {
            dataR[i] = maxR;
        }
        
        maxL -= mAmp;
        if (maxL < 0) maxL = 0;

        maxR -= mAmp;
        if (maxR < 0) maxR = 0;

        //rbjFilter.filter(maxL , maxR, dataL[i] , dataR[i]);
    }

    //<-
    maxL = 0;
    maxR = 0;
    for (int i = fxIEnd - 1; i >= fxIStart; i--) {

        if (dataL[i] > maxL) {
            maxL = dataL[i];
        } else {
            dataL[i] = maxL;
        }

        if (dataR[i] > maxR) {
            maxR = dataR[i];
        } else {
            dataR[i] = maxR;
        }

        
        maxL -= mAmp;
        if (maxL < 0) maxL = 0;

        maxR -= mAmp;
        if (maxR < 0) maxR = 0;

    }

    return *this;
}

Sample& Sample::extractEnvelope_old(int halfLifeLength) {

    double amp = pow(0.5, 1 / (double) halfLifeLength);

    double maxL = 0, maxR = 0;

    //

    for (int i = fxIStart; i < fxIEnd; i++) {

        double nL = fabs(dataL[i]);
        double nR = fabs(dataR[i]);

        if (nL > maxL) {
            maxL = nL;
        }
        if (nR > maxR) {
            maxR = nR;
        }

        dataL[i] = maxL;
        dataR[i] = maxR;

        maxL *= amp;
        maxR *= amp;
    }

    filterLowPass(10, 1, 1);
    /*
    maxL = 0;
    maxR = 0;

    for (int i = fxIEnd; i > fxIStart; i--) {

        double nL = fabs(dataL[i]);
        double nR = fabs(dataR[i]);

        if (nL > maxL) {
            maxL = nL;
        }
        if (nR > maxR) {
            maxR = nR;
        }

        dataL[i] = maxL;
        dataR[i] = maxR;

        maxL *= amp;
        maxR *= amp;
    }
     */

    return *this;
}
