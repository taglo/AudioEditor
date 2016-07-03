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

    void testStereoA() {
        Sample spl(44100);
        spl.genSine(110, 0, 1, 0.1);
        spl.genSine(220, 0, 0.1, 1);

        spl.saveToFile("test stereo 1.wav");
        
        Sample spl2;
        
        spl2.loadFromFile("test stereo 1.wav").saveToFile("test load stereo.wav");
        
        
    }

    void testReverse() {
        Sample spl(44100);
        spl.genSine().fadeOut().reverse().saveToFile("testReverse.wav");
    }

    void testDelay2() {

        int lnt = 800000;
        int nIter = 15;

        Sample spl[30], splFinal(lnt), splTmp(lnt);

        spl[0].changeLength(lnt);
        for (int im = 0; im < lnt; im += 40712) {
            spl[0].dataL[im] = 1;
        }

        spl[1].changeLength(lnt);
        for (int im = 0; im < lnt; im += 40812) {
            spl[1].dataL[im] = -1;
        }
        double f = 100, fm, q;

        fm = 1.25;
        q = 14;
        int j = 0, tgm = 0;

        for (int i = 2; i < nIter; i++) {

            cout << "iter : " << i << endl;

            spl[i].changeLength(lnt);
            for (int k = 0; k < 3; k++) {
                j += (73 + i);
                j = j % i;

                spl[j].fxIStart = (i * 7013 + j * 5041) % 40310;
                spl[j].fxIEnd = lnt - ((i * 6013 + j * 4041) % 40310);
                spl[j].strech(splTmp);

                fm += 0.0213;
                if (fm > 2.5) {
                    fm -= 2.5;
                }
                f *= fm;
                if (f > 22000) {
                    f = f - 21990;
                }
                splTmp.filterBandPass(f, q, 1).normalize(log(f) / log(22000));

                spl[i].fxIStart = (i * 1713 + j * 4041) % 280310;

                splTmp.fxIEnd = lnt - spl[i].fxIStart;
                spl[i].mix(splTmp, 1);

                spl[i].fxRangeReset();
                spl[j].fxRangeReset();
                splTmp.fxRangeReset();

            }

            spl[i].delay((i * 109013) % 24310, 1, 0.5).filterHiPass(100.0, 1, 1).normalize(0.9);

            tgm += 416;
            tgm = tgm % i;
            spl[tgm].fxRangeReset().mix(spl[i], 1).reverse().fadeOut();
            splFinal.mix(spl[i], 1);
        }


        splFinal.normalize(0.9).saveToFile("testDelay2.wav");

    }

    void testDelay() {
        Sample spl(80000);

        spl.dataL[0] = 1;

        double an = 0.1, dry, feedback;
        int length = 50;

        for (int i = 0; i < 20; i++) {

            length += 16 * i * i + 50;
            while (length > 4500) {
                length = length - 4443;
            }
            dry = 0.9; //cos(an);
            feedback = 0.9 * cos(an);
            spl.delay(length, dry, feedback);
            an = an + M_2_PI * 1.0 / 7.0;
            if (an > 0.4) {
                an -= 0.8;
            }
        }
        spl.saveToFile("test delay multi.wav");

    }

    void testNotch() {
        Sample spl(40000);
        Sample src(40000);

        src.genWhiteNoise(0.5, 500);

        src.copy(spl);
        spl.filterNotch(1000, 1, 1).saveToFile("testNotch 1000 1 1.wav");

        src.copy(spl);
        spl.filterNotch(1000, 1, 2).saveToFile("testNotch 1000 1 2.wav");

        src.copy(spl);
        spl.filterNotch(1000, 1, 3).saveToFile("testNotch 1000 1 3.wav");

        src.copy(spl);
        spl.filterNotch(1000, 2, 1).saveToFile("testNotch 1000 2 1.wav");

        src.copy(spl);
        spl.filterNotch(1000, 2, 2).saveToFile("testNotch 1000 2 2.wav");

        src.copy(spl);
        spl.filterNotch(1000, 2, 3).saveToFile("testNotch 1000 2 3.wav");

        src.copy(spl);
        spl.filterNotch(1000, 2, 3).saveToFile("testNotch 1000 4 3.wav");

        src.copy(spl);
        spl.filterNotch(1000, 2, 3).saveToFile("testNotch 1000 8 3.wav");

        src.copy(spl);
        spl.filterNotch(1000, 2, 3).saveToFile("testNotch 1000 16 3.wav");

    }

    void genKickA() {

        //enveloppe
        double nsTot = 4;

        Sample::tempo = 147;

        Sample splSrc(1031);
        for (int i = 0; i < splSrc.fxIEnd; i++) {
            double di = ((double) i) / 25;
            splSrc.dataL[i] = 1 / (1 + di * di * di);
        }
        splSrc.saveToFile("env src strech.wav");
        Sample splEnv(nsTot);
        splSrc.strech(splEnv);

        splEnv.normalize(1).fadeOut(); //.fadeOut();

        splEnv.saveToFile("spl env strech.wav");

        Sample splKick(nsTot);
        splKick.genSineFEnv(50, splEnv, 450, 0, 1);

        splKick.fadeOut();
        splKick.fxRangeStep(1, 4).fadeOut();

        splKick.fxRangeStep(2, 4).fadeOut().fxRangeReset();
        splKick.saveToFile("kickA.wav");

    }

    void testLoad() {
        Sample spl(100);
        spl.loadFromFile("kickA.wav");
        spl.saveToFile("kickA load save.wav");

    }
};