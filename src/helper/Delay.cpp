#include "Delay.h"

Delay::Delay() {

}

Delay::Delay(int length, double dry, double feedback) {
    mLength = length;
    mDry = dry;
    mFeedback = feedback;

    iBuffer = 0;

    buffer = new double[mLength];
    for (int i = 0; i < mLength; i++) {
        buffer[i] = 0;
    }

}

double Delay::tick(double vin) {
    double vout;

    vout = buffer[iBuffer] * mFeedback + vin * mDry;

    buffer[iBuffer] = vout;

    iBuffer++;
    if (iBuffer == mLength) {
        iBuffer = 0;
    }
    return vout;
}

