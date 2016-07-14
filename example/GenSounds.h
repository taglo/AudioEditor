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

    void multiSinEnv() {


        Sample::tempo = 125;
        //Sample::
        double lSong = 128 * 16;
        Sample splTrack(Sample::stepToInt(lSong));
        Sample splEnvF(Sample::stepToInt(16));
        Sample splNote(Sample::stepToInt(16));
        //cout<<splTrack.fxLength();

        double f, fAmp, ampL, ampR, bf, ev, ntH,ampHFade;
        int cnt = 0;

        for (double s = 0; s < lSong; s += 16) {
            // splNote.amplify(0.2,0.2);
            ev = s / lSong;


            cout << "prog : " << round(ev * 100) << "%" << endl;

            //A
            f = 220;
            ntH = 1;
            if ((cnt % 8) > 5) {
                //C

                ntH = 1.2;
            }
            if ((cnt % 23) < 7) {
                //E G
                ntH *= 1.5;
                cout << "mod : " << (cnt % 23) << endl;
            }
            f *= ntH;

            fAmp = 5;


            if ((cnt % 11) == 5) {
                fAmp = 1;
            }
            if((s>800) && (s<1024)) {
                fAmp*=1-(s-800)/(1024-800);
                splNote.amplify(fAmp,fAmp);
            }
            
            if(s>1800) {
                ampHFade=1+pow((s-1800)/(2048-1800),2);
            }else{
                ampHFade=1;
            }
            
            ampL = 0.1;
            ampR = 0.2;
            splEnvF.genEnvExp(0.5, -0.5, 0.3 - ev * 0.31);
            splEnvF.genSine(4 + 2 * sin(ev * 17), 0.5, 0.1);

            splEnvF.normalize(1).swapChannel();

            for (int k = 0; k < 7; k++) {

                splNote.genSineFEnv(f, splEnvF, fAmp, 0, ampL, ampR);

                f += 220 * ntH;
                if (k == (2 + cnt % 5)) {
                    f += 440 * ntH;
                }

                if ((k == 5) && ((cnt % 2) == 0)) {
                    splEnvF.reverse();
                }
                if (k == 5) {
                    f *= 2.0;
                }
                if (((cnt * 7 + k) % 73) == 12) {
                    splEnvF.amplify(-1.0, -1.0);
                }
                if (((cnt * 7 + k) % 201) == 12) {
                    splNote.fadeOut();
                }
                if (((cnt * 7 + k) % 303) < 12) {
                    splEnvF.genSine(10 + 4 * sin(ev * 11), 0.5, 0.2);
                }
                //splEnvF.genSine(1 + 0.2 * sin(ev * 7), 0.5, 0.1);
                bf = ampR * 0.85;
                ampR = ampL;
                ampL = bf;

                ampL/=ampHFade;
                ampR/=ampHFade;
                
                fAmp *= 1.9;
            }

            splNote.fadeOut().fadeAntiClick(450);
            splNote.normalize(1);
            //splNote.normalize(1).clip(0.9,-0.9).normalize(1);

            splTrack.fxIStart = Sample::stepToInt(s);
            splTrack.mix(splNote, 1, 1);

            cnt++;
        }
        splTrack.fxRangeReset().amplify(0.75, 0.75).saveToFile("A multi sin.wav");

    }

    void testEnvGen() {
        Sample spl(44100 * 11);

        for (double speed = 0; speed < 1; speed += 0.1) {

            spl.fxIEnd = spl.fxIStart + 44100;
            spl.genEnvExp(-1, 1, speed);

            spl.fxIStart += 44100;

        }

        spl.fxRangeReset().saveToFile("testEnvGen.wav");

    }

    void testEnv() {

        Sample spl(44100);

        Sample splA(1);


        double vs, vm, vend, vamp, speed;
        double dLnt = 44100.0;
        int bInv = false;

        // for (double sspeed = 0; sspeed <= 1.0; sspeed += 0.05) {
        double sspeed = 1;
        vs = 1;

        speed = sspeed;

        if (speed <= 0.01) {
            speed = 0.01;
        } else if (speed >= 0.99) {
            speed = 0.99;
        }

        speed = speed * 2;

        if (speed > 1) {
            bInv = true;
            speed = 2 - speed;
        }
        // speed += 0.01;
        vm = pow(0.5, 1 / (1 + dLnt * speed * speed));

        vend = pow(vm, dLnt);
        vamp = 1 / (1 - vend);
        if (bInv) {
            for (int i = 44099; i >= 0; i--) {
                vs *= vm;
                spl.dataL[i] = (vs - vend) * vamp;
                spl.dataR[i] = spl.dataL[i];
            }


        } else {
            for (int i = 0; i < 44100; i++) {
                vs *= vm;
                spl.dataL[i] = 1 - ((vs - vend) * vamp);



                spl.dataR[i] = spl.dataL[i];
            }
        }
        splA.mix(spl, 1, 1);
        splA.fxIStart += 44100;

        // }
        splA.fxRangeReset().saveToFile("test env.wav");

    }

    void testStereoA() {
        Sample spl(44100);
        spl.genSine(110, 0, 1, 0.1);
        spl.genSine(220, 0, 0.1, 1);

        spl.saveToFile("test stereo 1.wav");

        Sample spl2;
        spl2.loadFromFile("test stereo 1.wav").saveToFile("test load stereo.wav");

        spl.fadeStereo(0, 1, 1, 0).saveToFile("test fade stereo.wav");

        spl.reverse().saveToFile("test reverse.wav");

        Sample splStrech(44100 * 2);

        spl.strech(splStrech);
        splStrech.saveToFile("test strech.wav");

        splStrech.fxIEnd = 44100 / 2;
        splStrech.fadeAntiClick(1000);

        spl.strech(splStrech);
        splStrech.saveToFile("test strech 2.wav");

        splStrech.fxIEnd = 44100 / 4;
        splStrech.fadeAntiClick(1000);

        spl.strech(splStrech);
        splStrech.saveToFile("test strech 3.wav");

        splStrech.fxRangeReset().saveToFile("test fadeAntiClick.wav");

        splStrech.normalize(0.5).saveToFile("test normalize.wav");

        splStrech.amplify(2, 0.5).saveToFile("test amplify.wav");


    }

    void testStereoB() {

        Sample splWn;
        splWn.init(44100 * 2);
        splWn.genWhiteNoise(0.5, 1501).saveToFile("test white noise.wav");

        Sample spl;
        splWn.copy(spl);
        spl.filterBandPass(440, 0.5, 1).saveToFile("band pass 440 05 1.wav");
        splWn.copy(spl);
        spl.filterBandPass(440, 0.5, 2).saveToFile("band pass 440 05 2.wav");
        splWn.copy(spl);
        spl.filterBandPass(440, 0.5, 4).saveToFile("band pass 440 05 4.wav");
        splWn.copy(spl);
        spl.filterBandPass(440, 1, 1).saveToFile("band pass 440 1 1.wav");
        splWn.copy(spl);
        spl.filterBandPass(440, 1, 2).saveToFile("band pass 440 1 2.wav");
        splWn.copy(spl);
        spl.filterBandPass(440, 1, 4).saveToFile("band pass 440 1 4.wav");
        splWn.copy(spl);
        spl.filterBandPass(440, 2, 1).saveToFile("band pass 440 2 1.wav");
        splWn.copy(spl);
        spl.filterBandPass(440, 2, 2).saveToFile("band pass 440 2 2.wav");
        splWn.copy(spl);
        spl.filterBandPass(440, 2, 4).saveToFile("band pass 440 2 4.wav");


    }

    void testStereoC() {

        Sample splWn;

        Sample::tempo = 125;

        splWn.init(splWn.stepToInt(4.0));

        splWn.genWhiteNoise(0.5, 4501).fadeAntiClick(250);
        splWn.saveToFile("test stc 1.wav");

        Sample spl(splWn.stepToInt(256));
        Sample splBt(splWn.stepToInt(4));

        double f = 50;
        double fm = pow(20000.0 / f, 4.0 / 256.0);
        double vol = 2;
        double volm = (0.05 - vol) / (256 / 4);

        for (double s = 0; s < 256; s += 4) {
            splWn.copy(splBt);
            splBt.filterLowPass(f, 2, 3);
            f = f*fm;
            splBt.fadeOut().fadeAntiClick(250);

            spl.fxIStart = splWn.stepToInt(s);
            spl.mix(splBt, vol, vol);
            vol += volm;

        }

        spl.fxRangeReset().fadeOut().saveToFile("test stereo c low pass.wav");


    }

    void testSwoosh() {

        Sample splWn, splEnv;

        Sample::tempo = 125;

        splWn.init(splWn.stepToInt(4.0));
        splEnv.init(splWn.stepToInt(4.0));



        splWn.genWhiteNoise(0.25, 4501).fadeAntiClick(250);
        splWn.fadeOut().fadeOut();

        splWn.genSaw(440, 0.5, 0.9, 1).fadeOut();
        splWn.genSaw(220, 0.9, 0.5, 1).fadeOut();

        splWn.genSaw(55, 2, 2, 1).fadeOut();

        //todo enveloppe mieux
        splEnv.setConstant(1).fadeOut().fadeOut().fadeOut().fadeOut();

        splWn.filterLowPassFEnv(100, splEnv, 19000, 1, 4);
        splWn.normalize(0.9);

        splWn.saveToFile("bass A wn src.wav");

        Sample spl(splWn.stepToInt(1024));
        Sample splBt(splWn.stepToInt(4));

        double note1 = spl.fqtoMidiNote(100.0);
        double note2 = spl.fqtoMidiNote(10000.0);

        double notep = (note2 - note1) / 256;

        int cnt = 0;

        double smp = 0.31;

        for (double s = 0; s < 990; s += 4) {

            splWn.swapChannel();

            splWn.copy(splBt);

            double fq = spl.midiNoteToFq(note1);

            double sm = 3;

            if ((cnt % 16) == 0) {
                smp += 0.3;

            }

            for (int i = 1; i < 6; i++) {

                splBt.normalize(1).clip(0.9, -0.9);
                splBt.filterNotch(fq, 3, 4).fadeAntiClick(500);


                fq += 1000;
                splBt.fxIStart = spl.stepToInt(round(sm));
                splBt.mix(splWn, -0.35, -0.35).fxRangeReset();

                sm += smp;

            }

            note1 += notep;

            splBt.fadeOut().fadeAntiClick(250);

            double sok = s;
            if ((cnt % 4) == 3) {
                sok += 1.0;
            }
            spl.fxIStart = splWn.stepToInt(sok);

            spl.mix(splBt, 1, 1);

            cnt++;
            std::cout << cnt << "/256" << std::endl;

        }

        spl.fxRangeReset().saveToFile("testSwoosh.wav");


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