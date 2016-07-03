//#pragma once
#include "Sample.h"

Sample& Sample::copy(Sample& splOut) {

    splOut.length = fxLength();

    splOut.dataL = new double[splOut.length];
        splOut.dataR = new double[splOut.length];

    int j = 0;
    for (int i = fxIStart; i < fxIEnd; i++) {
        splOut.dataL[j] = dataL[i];
        splOut.dataR[j++] = dataR[i];
    }
    splOut.fxRangeReset();

    return *this;
}

Sample& Sample::reverse() {

    int j = fxIEnd - 1;
    double bf;
    int hLnt = fxIStart + (length >> 1) + 1;

    for (int i = fxIStart; i < hLnt; i++) {
        
        bf = dataL[i];
        dataL[i] = dataL[j];
        dataL[j] = bf;

        bf = dataR[i];
        dataR[i] = dataR[j];
        dataR[j--] = bf;
        
    }


    return *this;
}

Sample& Sample::cut() {

    int newLength = fxIStart + length - fxIEnd;
    setBufferMinLength(newLength);

    copyToBuffer(*this, 0, 0, fxIStart);
    copyToBuffer(*this, fxIEnd, fxIStart, length - fxIEnd);

    length = newLength;
    dataL = new double[length];
    dataR = new double[length];

    copyFromBuffer(*this, 0, 0, length);

    fxRangeReset();

    return *this;
}

Sample& Sample::cut(Sample& splOut) {

    copy(splOut);
    cut();

    return *this;
}