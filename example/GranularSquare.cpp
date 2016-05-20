#include "GranularSquare.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

#include <random>

#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace std;

GranularSquare::GranularSquare() {
}

void GranularSquare::generate() {

    int nGra = 0;
    int lntGra = 0, imix, imixinc;
    double fq, phase, amplitude, width, ampmix, ampf, fqf;
    int dh, dhinc, dhmax;

    char fname[50];

    //std::ostringstream str;

    std::uniform_real_distribution<double> unif(0.0, 1.0);
    std::mt19937_64 re(12345);

    Sample spl(44100 * 5);

    Sample splGranule(44100);
    spl.fxRange(0, 44100);
    
    for (double dp = 0; dp <= 1; dp += 0.1) {
        sprintf(fname, "phase %g.wav", dp);
        splGranule.setConstant(0).genSquare(109.5+dp, dp, 0.5, 0.5).saveToFile(fname);
        spl.mix(splGranule, 1).fadeOut();
    }
    spl.normalize(0.9).saveToFile("test phases.wav");

    for (int i = 0; i < 3; i++) {


        spl.fxRangeReset().setConstant(0);

        nGra = 1000 + (int) 2000 * unif(re);

        imix = 0;


        dh = 1;
        dhinc = 1 + (int) 10 * unif(re);
        dhmax = 20 + (int) 40 * unif(re);

        imixinc = 10000 + (int) 5000 * pow(unif(re), 2.0);

        for (int j = 0; j < nGra; j++) {
            //spl.data[j] = 0.5;

            if (j == 0 || unif(re)<(0.02)) {
                imix = 0;
                imixinc = 1000 + (int) 2000 * pow(unif(re), 2.0);
                lntGra = 3000 + (int) 3000 * pow(unif(re), 2.0);
                dh = 1 + (int) 20 * pow(unif(re), 2);
                phase = unif(re);
                amplitude = 0.9;
                if (unif(re) < 0.5) {
                    amplitude = -amplitude;
                }
                ampf = pow(0.25, 1.0 / (10 + 100 * unif(re)));
                width = 0.1 + 0.9 * unif(re);

                fq = 55 * (double) dh;


                fqf = pow(0.99 + 0.02 * unif(re), 1.0 / (10 + 100 * unif(re)));

            }

            splGranule.fxRange(0, lntGra).setConstant(0);
            amplitude = amplitude*ampf;
            fq = fq*fqf;
            splGranule.genSquare(fq, phase, amplitude, width);

            splGranule.fadeIn().fadeOut();



            spl.fxIStart = imix;
            ampmix = 0.5;
            spl.mix(splGranule, ampmix);
            imix = (imix + imixinc) % (44100 * 4);
        }
        // nGra=
        sprintf(fname, "test%d.wav", i);
        spl.fxRangeReset().normalize(0.7).saveToFile(fname);
    }
}