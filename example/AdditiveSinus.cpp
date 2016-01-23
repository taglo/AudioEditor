#include "AdditiveSinus.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

AdditiveSinus::AdditiveSinus() {
}

void AdditiveSinus::generate() {

    gen1();
    gen2();
    gen3();
    gen4();
    gen5();
    
    /*
        Sample splBase(44100);
        Sample splSine(44100);

        double maxFq = splSine.samplerate / 2;

        for (int j = 100; j < 110; j++) {

            int nHarmo = 50 + rand() % 100;
            double fqMin = 50 + 1000 * ((double) (rand() / RAND_MAX));
            double fqMult = 1 + ((double) (rand() / RAND_MAX));

            double fqK = 0.1 + 2 * ((double) (rand() / RAND_MAX));
            double fqK2 = 0.01 + 0.01 * ((double) (rand() / RAND_MAX));
            double fqK3 = 0.01 + 0.01 * ((double) (rand() / RAND_MAX));

            double phaseStart = ((double) (rand() / RAND_MAX));
            double phaseMult = ((double) (rand() / RAND_MAX));

            for (int i = 0; i < nHarmo; i++) {

                double k = (double) i;
                double k2 = k*k;
                double k3 = k*k2;

                double fq = fqMin + fqMult * (fqK * k + fqK2 * k2 + fqK3 * k3);

                if (fq < maxFq) {

                    double phase = phaseStart + phaseMult*k;
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

     */
    cout << "ok AdditiveSinus" << endl;
}

void AdditiveSinus::gen1() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    for (int i = 0; i < 13; i++) {

        double k = (double) i;


        double fq = 440 + k * 55;

        double amplitude = 50 / (50 + k);

        splSine.genSine(fq * (1000 + k) / 1000, 0, amplitude).fadeOut();
        splBase.mix(splSine);

        splSine.genSine(fq * (1000 - k) / 1000, 0, amplitude).fadeOut();
        splBase.mix(splSine);

    }

    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen1.wav");


    cout << "ok gen1" << endl;
}

void AdditiveSinus::gen2() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    for (int i = 0; i < 13; i++) {

        double k = (double) i;


        double fq = 440 + k * 55;

        double amplitude = 50 / (50 + k);

        splSine.genSine(fq * (200 + k) / 200, 0, amplitude).fadeOut();
        splBase.mix(splSine);

        splSine.genSine(fq * (200 - k) / 200, 0, amplitude).fadeOut();
        splBase.mix(splSine);

    }

    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen2.wav");


    cout << "ok gen2" << endl;
}

void AdditiveSinus::gen3() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    double phase = 0;

    for (int i = 0; i < 43; i++) {

        double k = (double) i;


        double fq = 440 + k * 55;

        double amplitude = 50 / (50 + k);
        phase += 0.13;
        splSine.genSine(fq * (200 + k) / 200, phase, amplitude).fadeOut();
        splBase.mix(splSine);

        splSine.genSine(fq * (200 - k) / 200, phase, amplitude).fadeOut();
        splBase.mix(splSine);

    }

    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen3.wav");


    cout << "ok gen3" << endl;
}

void AdditiveSinus::gen4() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    double phase = 0;
    
    double fq = 55;
    double fqp = 110;
    double fqpm=0.9973663339792938890897093580021;
    
    double amplitude = 1;
    double ampM = 0.994;

    do {

        phase += 0.013;
        splSine.genSine(fq, phase, amplitude).fadeOut();
        splBase.mix(splSine);

        amplitude*=ampM;
        fqp *= fqpm;
        fq += fqp;

    } while (fq < 22000);

    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen4.wav");


    cout << "ok gen4" << endl;
}

void AdditiveSinus::gen5() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    double phase = 0;
    
    double fq = 55;
    double fqp = 110;
    double fqpm=0.99973663339792938890897093580021;
    
    double amplitude = 1;
    double ampM = 0.994;

    
    do {

        phase += 0.013;
        splSine.genSine(fq, phase, amplitude).fadeOut();
        splBase.mix(splSine);

        amplitude*=ampM;
        fqp *= fqpm;
        fq += fqp;

    } while (fq < 22000);

    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen5.wav");


    cout << "ok gen5" << endl;
}