/* 
 * File:   Delay.h
 * Author: tglo
 *
 * Created on 15 juin 2016, 08:45
 */


#pragma once

#ifndef DELAY_H
#define	DELAY_H


class Delay {
private:

    double *buffer;
    int iBuffer;
    
public:

    double mDry, mFeedback;
    int mLength;

    Delay() ;

    Delay(int length, double dry, double feedback) ;
    double tick(double vin) ;
    
};




#endif	/* DELAY_H */