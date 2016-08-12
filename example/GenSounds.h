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

    void testWaveShape() {

        Sample::tempo = 125;
        double lSound = 256;

        Sample spl(Sample::stepToInt(lSound));
        
        Sample splWS(44100);

        /*
        splWS.setConstantDynamic(-1, 1).clip(0.8, -0.8);
        splWS.addConstantDynamic(-0.2, 0.2);
        splWS.genSine(7.31, 0.5, 0.03, 0.01);
        splWS.genSine(7.71, 0.15, 0.01, 0.03);
        
        splWS.fxIEnd=10000;
        splWS.fadeOut();
        splWS.fxRangeReset();
        splWS.fxIStart=10000;
        splWS.fadeIn().fxRangeReset();
        */
        splWS.genSine(0.5,0.75,1,1);
        
        splWS.genSine(16,0,0.1,0.1);
        
        splWS.normalize(0.9);
        
        splWS.saveToFile("testWaveShape splWS");
        
        spl.genSuperSaw(55,21,7145,0.005,0.3);
        
        spl.filterLowPass(220,3,2);
        spl.filterLowPass(880,1,4);
        
        spl.normalize(1);
        spl.saveToFile("super saw src");
        
        spl.distoWaveShape(splWS,1,1);
        spl.saveToFile("super saw WS");
    }
    

    void genSndSuperSaw() {

        Sample::tempo = 125;
        double lPad = 256;

        Sample spl(Sample::stepToInt(lPad));
        Sample splEnv(Sample::stepToInt(lPad));

        spl.genSuperSaw(55, 20, 12345, 1.0 / 50.0, 0.2);
        spl.genSuperSaw(110, 20, 2345, 1.0 / 50.0, 0.15);

        spl.genSuperSaw(165, 20, 234, 1.0 / 10.0, 0.1);

        spl.fadeAntiClick(1500);
        spl.normalizeRmsW();
        spl.saveToFile("genSndSuperSaw");

    }

    void genSndAllPass() {
        Sample::tempo = 125;


        Sample spl(Sample::stepToInt(96));
        Sample splEnv(Sample::stepToInt(96));
        Sample splTmp;

        double f = 55.0;
        spl.genSaw(f, 0.5, 1, 0.3).fadeAntiClick(500);
        splEnv.setConstantDynamic(1, 0);

        double fAmp = 4000.0;
        double fSine = 0.523;

        for (int i = 0; i < 10; i++) {

            splEnv.changeLength(spl.fxLength());
            splEnv.genSine(fSine, 0.1, 0.1, 0.5);
            splEnv.fxIStart = splEnv.fxIEnd - Sample::stepToInt(1);
            splEnv.fadeOut().fxRangeReset().normalize(1.0);
            splEnv.amplify(-1, -1).swapChannel();

            if (i % 3 == 0) {
                splEnv.reverse();
            }

            fSine = fSine * 1.03 + 0.075;

            splTmp.copy(spl).filterAllPassEnv(f * 2 + 50, splEnv, f, 10.2, 3).normalize(0.8);

            f = f * 1.2 + 150.2;
            cout << "i : " << i << ", f : " << f << endl;

            spl.fxRangeReset();
            spl.mix(splTmp, -0.8, -0.1).swapChannel();

            //spl.fxIStart =Sample::stepToInt(3);//5-i%4);// + 100 + i * 114;
            //spl.mix(splTmp, -0.93, -0.1).swapChannel();

            spl.swapChannel();
            spl.fxRangeReset();
            if (i % 3 == 1) {
                spl.reverse();
            }
        }

        splEnv.saveToFile("env end");

        spl.normalize(0.8);
        spl.saveToFile("genSndAllPass");

        //track
        /* va mixer 16 step de sample tout les 64 step sur track en décalant la lecture de 1 step à chque fois*/
        double lSong = 2048;

        Sample splC(Sample::stepToInt(16));
        Sample splTrack(Sample::stepToInt(lSong));

        double sread = 0;
        int iCnt = 0;
        for (double s = 0; s < lSong; s += 64) {

            spl.fxRangeStep(sread, sread + 16.0);
            splC.copy(spl);
            if (iCnt % 2 == 0) {
                splC.swapChannel();
            }
            //splC.saveToFile("spl C");

            splC.fxRangeStep(0, 8).fadeIn();
            splC.fxRangeStep(8, 16).fadeOut();
            splC.fxRangeReset();

            //splC.saveToFile("spl C b");

            sread = sread + 1;
            splTrack.fxRangeStep(s, s + 16).mix(splC, 1, 1);

            iCnt++;
        }
        splTrack.fxRangeReset().saveToFile("A snd all pass track");

    }

    void genSndShepard() {
        Sample::tempo = 125;


        Sample spl(Sample::stepToInt(16));

        double f = 110.0 / 8.0;
        while (f < 22050) {
            spl.genSine(f, 1, 1);
            f = f * 2;

        }

        spl.fadeOut().fadeAntiClick(250);
        spl.normalize(0.8);
        spl.saveToFile("snd shepard");

    }

    void genSndCristal() {

        Sample::tempo = 125;

        Sample spl(Sample::stepToInt(64));
        int lntWf = 20000;
        Sample wf(lntWf);

        double fqWf = 44100 / ((double) lntWf);

        //wf.genSaw(fqWf, 0, 0, 0.2);
        wf.genSine(fqWf, 0, 1, 1);

        wf.saveToFile("test wf");
        wf.saveToFile("test wfb.wav");


        double fBase = 110.0;

        for (int i = 1; i < 50; i++) {

            double di = (double) i;
            double f = fBase * di;

            double phase = 0.5;

            double ampL = 1;
            double ampR = 1;

            int nadd = 0;

            cout << "harmo : " << i << endl;

            int ci = i;
            int cdiv = 2;
            while (cdiv <= ci) {
                if ((ci % cdiv) == 0) {
                    cout << "(" << ci << "," << cdiv << ") ";

                    ci = ci / cdiv;
                    nadd++;
                    ampL = ampL * 2;
                    ampR = ampR * 2;

                } else {
                    ampL = ampL / 2;
                    ampR = ampR / 2;
                    cdiv = cdiv + 1;
                }

            }
            cout << endl;

            ampL = ampL / di;
            ampR = ampR / di;

            cout << " nadd : " << nadd << ", ampL : " << ampL << endl;
            cout << endl;

            spl.genWaveform(wf, f, phase, ampL, ampR);
            wf.swapChannel();


        }

        spl.normalizeRmsW();
        spl.saveToFile("genSndCristal");

    }

    void wfHarmo() {

        Sample::tempo = 125;

        int lnt = 44100 * 10;
        int lntWf = 10000;
        double lSong = 2048;

        Sample spl(Sample::stepToInt(64));
        Sample track(Sample::stepToInt(lSong));
        Sample wf(lntWf);

        double fqWf = 44100 / ((double) lntWf);

        wf.genSaw(fqWf, 0, 0, 1);
        wf.genSine(fqWf, 0, 1, 0);
        wf.saveToFile("test wf");
        wf.saveToFile("test wfb.wav");

        int cnt = 0;

        for (double s = 0; s < lSong; s += 64) {
            double evs = s / lSong;
            cout << round(100 * evs) << "%" << endl;
            int hcnt = 5 + (cnt % 4);
            int hcnte = cnt % hcnt;

            double fBase = 110;

            int ifqb = 16 + (cnt % 32);
            double harmo = 2;

            for (int i = 1; i < 50; i++) {
                double ev = (double) i / 50.0;

                double f = fBase * harmo * (1000 + sin(ev * (11 + evs * 3.5))) / 1000;
                double phase = 0.5 + 0.5 * sin(ev * (13.2 + evs * 3.8));
                double ampL = 0.5 + sin(ev * (14.2 + evs * 6.5));
                double ampR = 0.5 + sin(ev * (15.2 + evs * 7.5));

                spl.genWaveform(wf, f, phase, ampL, ampR);
                wf.swapChannel();

                if ((i % hcnt) == hcnte) {
                    harmo += 1.0;
                }
                if (i == ifqb) {
                    fBase *= 1.2;
                }
            }

            cout << "harmo fin " << harmo << endl;
            cout << "fBase " << fBase << endl;
            cout << "hcnt " << hcnt << endl;
            cout << "hcnte " << hcnte << endl;
            cout << "ifqb " << ifqb << endl;

            spl.fadeOut().fadeAntiClick(650);
            spl.normalizeRmsW();
            track.fxRangeStep(s, s + 64);
            track.mix(spl, 1, 1);

            cnt++;
        }

        track.fxRangeReset().saveToFile("wfHarmo");

    }

    void genWaveForm() {

        int lnt = 44100 * 10;
        int lntWf = 10000;

        Sample test(lnt);
        Sample wf(lntWf);

        double fqWf = 44100 / ((double) lntWf);

        wf.genSaw(fqWf, 0, 0, 1);
        wf.genSine(fqWf, 0, 1, 0);
        wf.saveToFile("test wf");
        wf.saveToFile("test wfb.wav");

        double fBase = 110;

        for (int i = 1; i < 50; i++) {
            double ev = (double) i / 50.0;

            double f = fBase + 10 * sin(ev * 11);
            double phase = 0.5 + 0.5 * sin(ev * 13.2);
            double ampL = 0.5 + sin(ev * 14.2);
            double ampR = 0.5 + sin(ev * 15.2);

            test.genWaveform(wf, f, phase, ampL, ampR);
            wf.swapChannel();
            if ((i % 10) == 9) {
                fBase += 110;
            }
        }

        test.normalizeRmsW();
        test.saveToFile("genWaveForm");

    }

    void pulseFilt() {
        Sample::tempo = 125;

        double lSong = 2048;
        int lnt = Sample::stepToInt(lSong);
        int lnt16 = Sample::stepToInt(16);
        int lnt2 = Sample::stepToInt(2);
        int lnt1 = Sample::stepToInt(2);

        Sample splTrack(lnt);

        Sample splSndSrc(lnt16);
        Sample splSnd(lnt2);
        Sample splTmp;

        for (double s = 0; s < lSong; s += 32) {


            double ev = s / lSong;

            cout << s << endl;

            splSnd.init(lnt2);
            splSnd.dataL[0] = 1;
            splSnd.dataR[30 + (int) fmod(s / 31, 104)] = -0.01;

            if (fmod(s, 256 > 239)) {
                splSnd.dataR[lnt1] = -1;
            }

            double f = 110;
            for (double k = 0; k < 12; k++) {

                splTmp.copy(splSnd);

                splTmp.clip(0.8, -0.9);
                splTmp.filterBandPass(f * (1 + 0.1 * sin(((k / 6) + 7) * ev + k / 6.5))
                        ,
                        20
                        + 8 * sin(((k / 8.5) + 6) * ev + k / 9.5)
                        , 1);

                splTmp.normalize(1);

                splSnd.mix(splTmp, 1, 1);
                splTmp.swapChannel();

                splSnd.fxRangeStep(1 + fmod(k, 3), 20);

                splSnd.mix(splTmp, 0.2, -1);
                splSnd.fxRangeReset();

                f += 110;
                if (fmod(k, 5) > 3) {
                    f += 440;
                }
            }

            splSnd.normalizeRmsW();
            splTrack.fxRangeStep(s, s + 32);
            splTrack.mix(splSnd, 1, 1);
        }
        splTrack.fxRangeReset();
        splTrack.saveToFile("A plus pluse pulse.wav");

    }

    void vatBssNorm() {
        Sample::tempo = 125;

        double lSong = 1024;
        int lnt = Sample::stepToInt(lSong);
        int lnt16 = Sample::stepToInt(16);
        Sample splTrack(lnt);

        Sample splSndSrc(lnt16);
        Sample splSnd(lnt16);

        double es = 0, f = 100;
        for (int k = 0; k < 16; k++) {
            es += 0.945;
            splSndSrc.genSaw(
                    f + 2 * sin(es + 0.78),
                    0.5 + sin(es * 7.23 + 3.78),
                    1 + sin(es * 3.78 + 0.98),
                    1 + sin(es * 5.78 + 0.3));
            f += 110;
        }

        splSndSrc.normalize(1);

        Sample splEnv(lnt16);
        splEnv.genEnvExp(1, 0, 0.2);

        splSndSrc.modulate(splEnv);
        splSndSrc.saveToFile("sound src bss nrm.wav");

        double n1 = Sample::fqtoMidiNote(500);
        double n2 = Sample::fqtoMidiNote(5000);

        for (double s = lSong - 16; s >= 0; s -= 16) {
            double ev = s / lSong;

            splSnd.copy(splSndSrc);

            splSnd.filterNotch(Sample::midiNoteToFq(n1 + (n2 - n1) * ev), 3, 3);

            splSnd.filterNotch(Sample::midiNoteToFq(120 - s / 10), 3, 3);

            splSnd.filterLowPass(220 + 6000 * pow(s, 3) / pow(1024, 3), 1, 3);

            splTrack.fxRangeStep(s, s + 16);

            splSnd.normalizeRmsW();

            splTrack.mix(splSnd, 1, 1);

        }
        splTrack.fxRangeReset().saveToFile("A var syn s.wav");

    }

    void genWnSteckOctFilter() {
        cout << "genWnSteckOctFilter" << endl;

        Sample::tempo = 125;

        int lnt = Sample::stepToInt(512);

        Sample spl(lnt);
        Sample splBout(lnt);
        Sample splBout2(lnt);
        spl.genSaw(110, 0.5, 0.5, 0.15).genWhiteNoise(0.25, 1106);

        spl.fadeIn().fadeOut();

        spl.saveToFile("source 1.wav");
        double es = 0, smix = 0, ps;

        for (int k = 0; k < 20; k++) {
            cout << k;

            //on prend un bout
            smix = smix + 147;
            if (smix > 384) smix -= 384;


            es += 0.953;

            spl.fxRangeStep(smix, smix + 128);
            splBout.mix(spl, 1, 1);
            splBout.fxRangeStep(0, 128);

            //splBout.saveToFile("bout 1.wav");
            spl.fxRangeReset();

            splBout.fadeAntiClick(Sample::stepToInt(48));

            //splBout.saveToFile("bout 2.wav");
            //on le filtre
            double f = 2050.0 + 2000 * sin(es);
            if ((k % 5) > 2) {
                f = f * 2;
            }
            splBout.filterLowPass(f, 2 + 1.5 * sin(es * 7), 3);
            splBout.normalize(1);

            //splBout.saveToFile("bout 3.wav");

            //on le strech
            splBout2.fxRangeStep(0, 64);
            splBout.strech(splBout2);
            splBout2.swapChannel();

            //splBout2.saveToFile("bout2 1.wav");

            //on le mix ailleurs
            for (int l = 0; l < 3; l++) {
                smix = smix + 17 + ps;
                if (smix > 384) smix -= 384;

                spl.fxRangeStep(smix, smix + 64);
                spl.mix(splBout2, 0.5 + sin(es), 0.5 + cos(es));
                es += 1.207;
                ps = ps + 1;
            }


        }
        spl.fxRangeReset().normalize(0.75);
        spl.saveToFile("stren strech.wav");

    }

    void genKick() {

        cout << "genKick" << endl;

        Sample::tempo = 125;

        int lnt = Sample::stepToInt(4.0);

        Sample splSrc(1031);

        for (int i = 0; i < splSrc.fxIEnd; i++) {
            double di = ((double) i) / 31;
            splSrc.dataL[i] = 1 / (1 + di * di);
        }
        splSrc.saveToFile("env src strech.wav");
        Sample splEnv(lnt);
        splSrc.strech(splEnv);

        splEnv.normalize(1).fadeOut();

        splEnv.saveToFile("spl env strech.wav");

        Sample splKick(lnt);


        splKick.genSineFEnv(50, splEnv, 390, 0, 1);

        splKick.fadeOut();
        splKick.fxRangeStep(1, 4).fadeOut();

        splKick.fxRangeStep(2, 4).fadeOut().fxRangeReset();

        splKick.saveToFile("kick.wav");

    }

    void multiSinEnv() {


        Sample::tempo = 125;
        //Sample::
        double lSong = 128 * 16;
        Sample splTrack(Sample::stepToInt(lSong));
        Sample splEnvF(Sample::stepToInt(16));
        Sample splNote(Sample::stepToInt(16));
        //cout<<splTrack.fxLength();

        double f, fAmp, ampL, ampR, bf, ev, ntH, ampHFade;
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
            if ((s > 800) && (s < 1024)) {
                fAmp *= 1 - (s - 800) / (1024 - 800);
                splNote.amplify(fAmp, fAmp);
            }

            if (s > 1800) {
                ampHFade = 1 + pow((s - 1800) / (2048 - 1800), 2);
            } else {
                ampHFade = 1;
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

                ampL /= ampHFade;
                ampR /= ampHFade;

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

        double note1 = Sample::fqtoMidiNote(100.0);
        double note2 = Sample::fqtoMidiNote(10000.0);

        double notep = (note2 - note1) / 256;

        int cnt = 0;

        double smp = 0.31;

        for (double s = 0; s < 990; s += 4) {

            splWn.swapChannel();

            splWn.copy(splBt);

            double fq = Sample::midiNoteToFq(note1);

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