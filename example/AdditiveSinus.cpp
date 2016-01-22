#include "AdditiveSinus.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

AdditiveSinus::AdditiveSinus() {
}

void AdditiveSinus::generate() {
    using namespace std;

    Sample splBase(44100);
    Sample splSine(44100);

    double maxFq = splSine.samplerate / 2;

    for (int j = 100; j < 110; j++) {

        int nHarmo = 50 + rand() % 100;
        double fqMin = 50 + 1000 * ((double) (rand() / RAND_MAX));
        double fqMult = 1 +  ((double) (rand() / RAND_MAX));

        double fqK = 0.1 + 2 * ((double) (rand() / RAND_MAX));
        double fqK2 = 0.01 + 0.01 * ((double) (rand() / RAND_MAX));
        double fqK3 = 0.01 + 0.01 * ((double) (rand() / RAND_MAX));

        double phaseStart=((double) (rand() / RAND_MAX));
        double phaseMult=((double) (rand() / RAND_MAX));
        
        for (int i = 0; i < nHarmo; i++) {

            double k = (double) i;
            double k2 = k*k;
            double k3 = k*k2;

            double fq = fqMin + fqMult * (fqK * k + fqK2 * k2 + fqK3 * k3);

            if (fq < maxFq) {
                
                double phase = phaseStart+phaseMult*k;
                double amplitude = 150 / (300 + 8 * k);

                splSine.genSine(fq, phase, amplitude).fadeOut();
                splBase.mix(splSine);
            }
        }

        splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

        splBase.normalize(0.8);

        std::stringstream sstm;
        sstm << "AdditiveSinus" << j << ".wav";
        const char* fileName = sstm.str().c_str();


        splBase.saveToFile(fileName);

    }


    cout << "ok AdditiveSinus" << endl;
}