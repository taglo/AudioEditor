/* 
 * File:   rbjFilter.h
 * Author: tglo
 *
 * Created on 25 mai 2016, 15:30
 */


#pragma once
#ifndef RBJFILTER_H
#define	RBJFILTER_H

#include <cmath>



class RbjFilter {
public:
    // filter coeffs
    double b0a0, b1a0, b2a0, a1a0, a2a0;

    RbjFilter();
    void filter(double in0L, double in0R, double &outL, double &outR);
    void copy_filter_coeffs(RbjFilter filterIn) ;
    void calc_filter_coeffs(int type, double frequency, double sample_rate, double q, double db_gain, bool q_is_bandwidth) ;
    
private:



    // in/out history
    double ou1L, ou2L, in1L, in2L;
    double ou1R, ou2R, in1R, in2R;
};

#endif	/* RBJFILTER_H */