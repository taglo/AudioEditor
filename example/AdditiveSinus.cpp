#include "AdditiveSinus.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace std;

AdditiveSinus::AdditiveSinus() {
}

void AdditiveSinus::generate() {

    /*
    gen1();
    gen2();
    gen3();
    gen4();
    gen5();
    gen6();
    gen7();
    gen8();
    gen9();
    gen10();
    gen11();
    gen12();
    gen13();
    gen14();
    gen15();
    gen16();
    gen17();
    gen18();
    gen19();
    gen20();
    gen21(); 
    gen22();
    gen23();
    gen24();
    gen25();
     *  */


    gen26();

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
    double fqpm = 0.9973663339792938890897093580021;

    double amplitude = 1;
    double ampM = 0.994;

    do {

        phase += 0.013;
        splSine.genSine(fq, phase, amplitude).fadeOut();
        splBase.mix(splSine);

        amplitude *= ampM;
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
    double fqpm = 0.99973663339792938890897093580021;

    double amplitude = 1;
    double ampM = 0.994;


    do {

        phase += 0.013;
        splSine.genSine(fq, phase, amplitude).fadeOut();
        splBase.mix(splSine);

        amplitude *= ampM;
        fqp *= fqpm;
        fq += fqp;

    } while (fq < 22000);

    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen5.wav");


    cout << "ok gen5" << endl;
}

void AdditiveSinus::gen6() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    double phase = 0;

    double ph1 = 0;
    double ph2 = 0;
    double fq = 55;

    int k = 0;
    do {

        phase += M_PI * 51 / 103;

        ph1 += M_PI / 73;
        ph2 += M_PI / 71;

        fq += fabs(71 * sin(ph1) * sin(ph2));

        splSine.genSine(fq, phase, 1 / fq);
        splBase.mix(splSine);
        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 44100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen6.wav");


    cout << "ok gen6" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen7() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    double phase = 0;

    double ph1 = 0;
    double ph2 = 0;
    double fq = 55;

    int k = 0;
    do {

        phase += M_PI * 51 / 103;

        ph1 += M_PI / 73;
        ph2 += M_PI / 71;

        fq += fabs(71 * sin(ph1 + 4 * sin(ph2)));

        splSine.genSine(fq, phase, 1 / fq);
        splBase.mix(splSine);
        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 44100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen7.wav");


    cout << "ok gen7" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen8() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    double phase = 0;

    double ph1 = 0;
    double ph2 = 0;
    double fq = 55;

    int k = 0;
    do {

        phase += M_PI * 21 / 103;

        ph1 += M_PI / 73;
        ph2 += M_PI / 103;

        fq += 16 + fabs(103 * sin(ph1 + 4 * sin(ph2)));

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11));
        splBase.mix(splSine);
        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 44100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen8.wav");


    cout << "ok gen8" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen9() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    double phase = 0;

    double ph1 = 0;
    double pph1 = M_PI / 73;
    double ph2 = 0;
    double fq = 55;

    int k = 0;
    do {

        phase += M_PI * 21 / 103;

        pph1 *= 1.00006933874625;
        ph1 += pph1;
        ph2 += M_PI / 103;

        fq += 16 + fabs(103 * sin(ph1 + 4 * sin(ph2)));

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 44100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen9.wav");


    cout << "ok gen9" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen10() {


    Sample splBase(2 * 44100);
    Sample splSine(2 * 44100);

    double phase = 0;

    double ph1 = 0;
    double pph1 = M_PI / 73;
    double ph2 = 0;
    double fq = 55;

    int k = 0;
    do {

        phase += M_PI * 21 / 103;

        pph1 *= 1.00006933874625;
        ph1 += pph1;
        ph2 += M_PI / 103;

        fq += 3 + fabs((8 + 6 * sin(ph2)) * sin(ph1));

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 44100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen10.wav");


    cout << "ok gen10" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen11() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double ph1 = 0;
    double pph1 = M_PI / 473;
    double ph2 = 0;
    double pph2 = M_PI / 373;
    double fq = 55;

    int k = 0;
    do {

        phase += M_PI * 21 / 103;

        pph1 *= 1.00006933874625;
        ph1 += pph1;

        pph2 *= 1.00007933874625;
        ph2 += pph2;

        fq += 3 + fabs((8 + 7 * sin(ph2)) * sin(ph1));

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen11.wav");
    cout << "ok gen11" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen12() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double ph1 = 0;
    double pph1 = M_PI / 43;
    double ph2 = 0;
    double pph2 = M_PI / 33;
    double fq = 55;

    int k = 0;
    do {

        phase += M_PI * 21 / 103;

        pph1 *= 0.9996933874625;
        ph1 += pph1;

        pph2 *= 0.9987933874625;
        ph2 += pph2;

        fq += 3 + fabs((13 + 7 * sin(ph2)) * sin(ph1));

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen12.wav");
    cout << "ok gen12" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen13() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double ph1 = 0;
    double pph1 = M_PI / 43;
    double ph2 = 0;
    double pph2 = M_PI / 33;
    double fq = 55;
    double fbase = 3;

    int k = 0;
    do {

        phase += M_PI * 21 / 103;

        pph1 *= 0.9996933874625;
        ph1 += pph1;

        pph2 *= 0.9987933874625;
        ph2 += pph2;

        fbase *= 1.012;

        fq += fbase + fabs((13 + 7 * sin(ph2)) * sin(ph1));

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen13.wav");
    cout << "ok gen13" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen14() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double ph1 = 0;
    double pph1 = M_PI / 43;
    double ph2 = 0;
    double pph2 = M_PI / 33;
    double fq = 55;
    double fbase = 1;

    int k = 0;
    do {

        phase += M_PI * 11 / 103;

        pph1 *= 0.9996933874625;
        ph1 += pph1;

        pph2 *= 0.9987933874625;
        ph2 += pph2;

        fbase *= 1.00912;

        fq += fbase + fabs((4 + 3 * sin(ph2)) * sin(ph1));

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen14.wav");
    cout << "ok gen14" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen15() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double ph1 = 0;
    double pph1 = M_PI / 43;
    double ph2 = 0;
    double pph2 = M_PI / 33;
    double fq = 55;
    double fbase = 1;

    int k = 0;
    do {

        phase += M_PI * 11 / 103;

        pph1 *= 0.9996933874625;
        ph1 += pph1;

        pph2 *= 0.9987933874625;
        ph2 += pph2;

        fbase *= 1.008912;
        if ((k % 7) == 0) {
            fq += 203;
        }

        fq += fbase + fabs((3 + 2 * sin(ph2)) * sin(ph1));

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen15.wav");
    cout << "ok gen15" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen16() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double ph1 = 0;
    double pph1 = M_PI / 43;
    double ph2 = 0;
    double pph2 = M_PI / 33;
    double fq = 20;
    double fbase = 1;

    int k = 0;
    do {

        phase += M_PI * 11 / 103;

        pph1 *= 0.9996933874625;
        ph1 += pph1;

        pph2 *= 0.9987933874625;
        ph2 += pph2;

        fbase *= 1.0078912;
        if ((k % 14) == 13) {
            fq += 73;
        }

        fq += fbase + fabs((3 + 2 * sin(ph2)) * sin(ph1));

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen16.wav");
    cout << "ok gen16" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen17() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double fq = 20;


    int k = 0;
    do {

        phase += 11 / 103;


        fq += 7.073;
        if ((k % 23) > 13) {
            fq *= 23 / 22;
        }
        if ((k % 14) == 13) {
            fq += 73;
        }
        if ((k % 11) == 10) {
            fq *= 7 / 5;
        }

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen17.wav");
    cout << "ok gen17" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen18() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double fq = 20;


    int k = 0;
    do {

        phase += 11 / 103;
        fq += 7.073;
        if ((k % 23) > 13) {
            fq *= 23 / 22;
            phase /= 2;
        }
        if ((k % 13) == 12) {
            fq += 103;
            phase += 1 / 5;
        }
        if ((k % 19) < 10) {
            fq *= 7 / 5;
            phase += -1 / 7;
        }

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen18.wav");
    cout << "ok gen18" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen19() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double fq = 20;


    int k = 0;
    do {

        phase += 11 / 103;

        fq += 3.073;

        if ((k % 23) > 13) {
            fq *= 23 / 22;
            phase /= 2;
        } else {
            fq *= 19 / 13;
            phase += 16 / 17;
        }
        if ((k % 13) == 12) {
            fq += 103;
            phase += 1 / 5;
        }
        if ((k % 19) < 10) {
            fq *= 7 / 5;
            phase += -1 / 7;
        }

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen19.wav");
    cout << "ok gen19" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen20() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double fq = 20;


    int k = 0;
    do {

        phase += 11 / 103;

        fq += 3.073;

        if ((k % 23) > 13) {
            fq *= 23 / 22;
            phase += 0.965454;
        } else {
            fq *= 19 / 13;
            phase += 16 / 17;
        }
        if ((k % 13) == 12) {
            fq += 203;
            phase += 1 / 5;
        }
        if ((k % 19) < 10) {
            fq *= 7 / 5;
            phase += -1 / 7;
        } else {
            fq += 403;
            phase += 0.43915;
        }

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen20.wav");
    cout << "ok gen20" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen21() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double fq = 20;


    int k = 0;
    do {

        phase += 11 / 103;

        fq += 3.073;

        if ((k % 24) > 13) {
            fq *= 31 / 30;
            phase += 0.965454;
        } else {
            fq *= 19 / 17;
            phase += 16 / 17;
        }
        if ((k % 14) == 12) {
            fq += 103;
            phase += 1 / 5;
        }
        if ((k % 20) < 10) {
            fq *= 7 / 6;
            phase += -1 / 7;
        } else {
            fq += 203;
            phase += 0.43915;
        }

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen21.wav");
    cout << "ok gen21" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen23() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double fq = 20;


    int k = 0;
    do {

        phase += 11 / 103;
        fq += 10;

        if ((k % 31) < 10) {
            phase += 79 / 103;
            fq *= 19 / 15;

        }
        if ((k % 23) > 16) {
            phase += 55 / 103;
            fq *= 63 / 61;
        }
        if ((k % 19) > 7) {
            phase += 43 / 103;
            fq *= 6 / 5;
        }
        if ((k % 17) == 16) {
            phase += 31 / 103;
            fq += 400;
        }

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen23.wav");
    cout << "ok gen23" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen24() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double fq = 20;


    int k = 0;
    do {

        phase += 11 / 103;
        fq += 50;

        if ((k % 31) < 10) {
            phase += 79 / 103;
            fq *= 19 / 13;

        }
        if ((k % 23) > 16) {
            phase += 55 / 103;
            fq *= 63 / 51;
        }
        if ((k % 19) > 7) {
            phase += 43 / 103;
            fq *= 8 / 5;
        }
        if ((k % 17) == 16) {
            phase += 31 / 103;
            fq += 400;
        }

        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen24.wav");
    cout << "ok gen24" << endl;
    cout << k << " iteration" << endl;

}

void AdditiveSinus::gen25() {


    Sample splBase(44100);
    Sample splSine(44100);

    double phase = 0;

    double fq = 20;


    int k = 0;
    double x, x2, x3, x4;

    do {

        x = (double) k / 1000;
        x2 = x*x;
        x3 = x2*x;
        x4 = x3*x;

        phase += 11 / 103;
        fq += 10 + fabs(2.43 + 7.23 * x4 - 5.61 * x3 - 4 * x2 + 7 * x);


        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 24100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen25.wav");
    cout << "ok gen25" << endl;
    cout << k << " iteration" << endl;

}


void AdditiveSinus::gen26() {


    Sample splBase(4*44100);
    Sample splSine(4*44100);

    double phase = 0;

    double fq = 20;


    int k = 0;
    double x, x2, x3, x4;

    do {

        x = (double) k / 1000;
        x2 = x*x;
        x3 = x2*x;
        x4 = x3*x;

        phase += 11 / 103;
        fq += 10 + fabs(2.43 + 6.23 * x4 - 4.61 * x3 - 3.43 * x2 + 6.13 * x);


        splSine.genSine(fq, phase, pow(1.0 / fq, 1.0 / 11.0));

        splBase.mix(splSine);

        k++;
    } while (fq < 22000);

    splBase.fxRangeReset().fxIStart = 3*44100;
    splBase.fadeOut();
    splBase.fxRange(0, 2000).fadeIn().fxRangeReset();

    splBase.normalize(0.8);

    splBase.saveToFile("AdditiveSinus_gen26.wav");
    cout << "ok gen26" << endl;
    cout << k << " iteration" << endl;

}