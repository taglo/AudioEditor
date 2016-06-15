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

    double feedback;
    int length;

    Delay() {

    }

    Delay(int inLength, double inFeedback) {
        length=inLength;
        feedback=inFeedback;
        
        iBuffer = 0;

        buffer = new double[length];
        for (int i = 0; i < length; i++) {
            buffer[i] = 0;
        }

    }

    double tick(double vin) {
        double vout;

        vout = buffer[iBuffer] * feedback + vin;

        buffer[iBuffer] = vout;

        iBuffer++;
        if (iBuffer == length) {
            iBuffer = 0;
        }
        return vout;
    }
};