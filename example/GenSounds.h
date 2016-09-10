/* 
 * File:   GensSounds.h
 * Author: tglo
 *
 * Created on 1 juin 2016, 13:48
 */

#ifndef GENSSOUNDS_H
#define	GENSSOUNDS_H



#endif	/* GENSSOUNDS_H */

#include "../src/Sample.h"
using namespace std;

class GenSounds {
public:

    void tInstrum() ;
    void testVoco2();
    void khhEvol() ;
    void testEnvelope();
    void testXPEnvelope();
    void testVocoder() ;
    void testWaveShapeB();
    void testWaveShape() ;
    void genSndSuperSaw() ;
    void genSndAllPass() ;
    void genSndShepard() ;
    void genSndCristal();
    void wfHarmo();
    void genWaveForm();
    void pulseFilt() ;
    void vatBssNorm();
    void genWnSteckOctFilter();
    void genKick() ;
    void multiSinEnv();
    
    void testEnvGen() ;

    void testEnv() ;

    void testStereoA() ;

    void testStereoB();

    void testStereoC() ;

    void testSwoosh() ;

    void testReverse() ;

    void testDelay2() ;

    void testDelay();

    void testNotch();

    void genKickA();

    void testLoad();
};