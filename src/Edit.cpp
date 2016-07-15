//#pragma once
#include "Sample.h"

Sample& Sample::copy(Sample& splIn) {

    delete[] dataL;
    delete[] dataR;
    
    length = splIn.fxLength();

    dataL = new double[length];
    dataR = new double[length];

    int j = 0;
    for (int i = splIn.fxIStart; i < splIn.fxIEnd; i++) {
        dataL[j] = splIn.dataL[i];
        dataR[j++] = splIn.dataR[i];
    }
    fxRangeReset();

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

Sample& Sample::cut(Sample& splIn) {

    copy(splIn);
    splIn.cut();

    return *this;
}