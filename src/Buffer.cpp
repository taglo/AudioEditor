#include "Sample.h"

void Sample::setBufferMinLength(int minLength) {
    if (minLength > bufferLength) {
        bufferLength = minLength;
        bufferL = new double[bufferLength];
        bufferR= new double[bufferLength];
    }
}

void Sample::copyToBuffer(Sample splIn, int iIn, int iBuffer, int copyLength) {
    
    setBufferMinLength(iBuffer + copyLength);
    
    int iEnd = iIn + copyLength;
    for (int i = iIn; i < iEnd; i++) {
        bufferL[iBuffer] = splIn.dataL[i];
        bufferR[iBuffer++] = splIn.dataR[i];
    }
}

void Sample::copyFromBuffer(Sample& splOut, int iOut, int iBuffer, int copyLength) {
    int iEnd = iOut + copyLength;
    for (int i = iOut; i < iEnd; i++) {
        splOut.dataL[i] = bufferL[iBuffer];
        splOut.dataR[i] = bufferR[iBuffer++];
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
