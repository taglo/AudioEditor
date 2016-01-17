#include "Sample.h"

void Sample::setBufferMinLength(int minLength) {
    if (minLength > bufferLength) {
        bufferLength = minLength;
        buffer = new double[bufferLength];
    }
}

void Sample::copyToBuffer(double *dataIn, int iIn, int iBuffer, int copyLength) {
    
    setBufferMinLength(iBuffer + copyLength);
    
    int iEnd = iIn + copyLength;
    for (int i = iIn; i < iEnd; i++) {
        buffer[iBuffer++] = dataIn[i];
    }
}

void Sample::copyFromBuffer(double *dataOut, int iOut, int iBuffer, int copyLength) {
    int iEnd = iOut + copyLength;
    for (int i = iOut; i < iEnd; i++) {
        dataOut[i] = buffer[iBuffer++];
    }
}

Sample& Sample::prepareForSplIn(Sample& splIn, int& jRead, int& iMixEnd) {
    jRead = splIn.fxIStart;
    iMixEnd = fxIStart + splIn.fxLength();

    if (iMixEnd > length) {
        changeLength(iMixEnd);
    }

    return *this;
}
