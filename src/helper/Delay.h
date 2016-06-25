/* 
 * File:   Delay.h
 * Author: tglo
 *
 * Created on 15 juin 2016, 08:45
 */



#ifndef DELAY_H
#define	DELAY_H



#endif	/* DELAY_H */

class Delay {
private:

    double *buffer;
    int iBuffer;
public:

    double mDry, mFeedback;
    int mLength;

    Delay() {

    }

    Delay(int length, double dry, double feedback) {
        mLength=length;
        mDry=dry;
        mFeedback=feedback;
        
        iBuffer = 0;

        buffer = new double[mLength];
        for (int i = 0; i < mLength; i++) {
            buffer[i] = 0;
        }

    }

    double tick(double vin) {
        double vout;

        vout = buffer[iBuffer] * mFeedback + vin * mDry;

        buffer[iBuffer] = vout;

        iBuffer++;
        if (iBuffer == mLength) {
            iBuffer = 0;
        }
        return vout;
    }
};