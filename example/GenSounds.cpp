#include "GenSounds.h"

void GenSounds::tInstrum() {
    Sample::tempo = 125;

    double lSong = 2048;
    Sample splSong(Sample::stepToInt(lSong));

    int nSpl = 11;
    int lnt16 = Sample::stepToInt(16);

    Sample splSrc[nSpl];

    for (double s = 0; s < lSong; s += 16.0) {
        double evS = s / lSong;

        cout << 100 * evS << endl;

        for (int i = 0; i < nSpl; i++) {
            double ev = i / nSpl;

            splSrc[i].init(lnt16);

            double f = 110.0 * (double) i;

            double phase = sin(ev * 13 + evS * 13.413 + 7.412)*0.5 + 0.5;
            double ampBase = 15 / (double) (i + 5);

            double ampL = ampBase * (1 + 0.7 * sin(ev * 13.412 + evS * 13.413 + 0.751));
            double ampR = ampBase * (1 + 0.7 * sin(ev * 17.412 + evS * 11.413 + 1.751));

            //                splSrc[i].genSine(f, phase, ampL, ampR);

            f = f * (100 + sin(ev * 37.912 + evS * 14.813 + 7.751)) / 100;

            splSrc[i].genSaw(f, phase, ampL, ampR);

            double fFilter = 10000.0 / ((double) i + 1);

            fFilter = fFilter * (1 + 0.7 * sin(ev * 27.412 + evS * (19.913 + ev * 7) + 1.751));

            splSrc[i].fade(1, 0);
            splSrc[i].fade(1, 0);

            if (i < 3) {
                splSrc[i].filterHiPass(fFilter, 3, 3);
            } else if (i > 8) {
                splSrc[i].filterBandPass(fFilter, 3, 3);
            } else {
                splSrc[i].filterLowPass(fFilter, 3, 3);
            }


            splSrc[i].fade(1, 0);
            splSrc[i].fxRangeStep(8 + 7 * sin(ev * 13 + evS * 19.7413 + 2.0123), 16);
            splSrc[i].fadeOut();
            splSrc[i].fxRangeReset();

            splSrc[i].normalizeRmsW();

        }

        for (int i = 1; i < nSpl; i++) {

            splSrc[0].mix(splSrc[i], 1, 1);

        }

        splSrc[0].normalizeRmsW();

        splSong.fxRangeStep(s, s + 16);
        splSong.mix(splSrc[0]);
    }

    splSong.fxRangeReset();
    splSong.saveToFile("tInstrum");
    //splSrc[0].saveToFile("tInstrum");

}

void GenSounds::testVoco2() {

    const int nSine = 15, nHarmo = 3;

    double fBase = 220;

    Sample::tempo = 125;

    Sample splSrc(Sample::stepToInt(64));

    splSrc.loadFromFile("speech test");

    Sample splEnv, splSine(splSrc.fxIEnd), splOut;

    double harmo[nHarmo] = {


        5.0 / 4.0,

        3.0 / 2.0,
        2.0
    };

    double rh = 1;
    for (int i = 0; i < nHarmo; i++) {
        cout << harmo[i] << endl;
        harmo[i] = harmo[i] / rh;
        rh = rh * harmo[i];
        cout << harmo[i] << endl;
    }

    double f = fBase;
    for (int i = 0; i < nSine; i++) {
        splEnv.copy(splSrc).filterBandPass(f, 3, 2);
        splEnv.extractEnvelope_old(2000);


        splSine.setConstant(0).genSine(f, 0, 1, 1);
        splSine.modulate(splEnv);

        splOut.mix(splSine, 1, 1);


        f *= harmo[i % nHarmo];
        cout << i << " : " << f << endl;
    }

    splOut.normalizeRmsW();
    splOut.fxRangeReset().saveToFile("testVoco2");

}

void GenSounds::khhEvol() {

    Sample::tempo = 125;
    double lSong = 2048;

    Sample spl(Sample::stepToInt(lSong));
    Sample splHHSrc, splHH(Sample::stepToInt(4));
    Sample splFEnv(Sample::stepToInt(4));

    splHHSrc.loadFromFile("hh src").fadeAntiClick(200).changeLengthStep(4.0);

    double phz1 = 0, phz2 = 0;

    double fAmp;
    for (double s = 0; s < lSong; s += 4) {
        double ev = s / lSong;

        if (fmod(s, 256) == 0) {

            phz1 = 13 * sin(ev * 71 + 43);
            phz2 = 14 * sin(ev * 51 + 31);

            cout << s << endl;
            cout << 100 * ev << "%" << endl;
        }

        fAmp = 7000;

        if (s >= (1024 - 200) && s < 1024) {
            double vFade = 1 - ((s - (1024 - 200)) / 200);
            fAmp = fAmp*vFade;
        }

        double smix = s;

        splFEnv.setConstant(0);
        splFEnv.addEnvExp(1, 0, 0.02 + 0.004 * sin(ev * 25.123 + phz1));

        if (s >= (2048 - 256) && s < 2048) {
            double vFade = (s - (2048 - 256)) / 256;
            vFade = 0.2 * vFade*vFade;
            cout << vFade << endl;
            splFEnv.addConstantDynamic(vFade, 0);
            //fAmp = fAmp*vFade;
        }

        splHHSrc.fxIStart = (int) 3000.0 + 199 * sin(ev * 14.101 + phz2);

        splHH.setConstant(0);
        splHH.mix(splHHSrc, 1, 1).fadeAntiClick(460);

        splHH.filterLowPassFEnv(90, splFEnv, fAmp, 1.5, 3);

        splHH.normalizeRmsW(-12, 1024);

        spl.fxRangeStep(smix, smix + 4).mix(splHH);
    }

    splFEnv.saveToFile("test env");

    spl.fxRangeReset().saveToFile("khhEvol");

}

void GenSounds::testEnvelope() {
    int lnt = 441000;

    Sample spl(lnt);

    spl.genSine(322.895, 0.5, 0.5, 0.5);

    spl.genSine(320.135, 0.5, 0.5, 0.5);

    spl.genSine(221.553, 0.5, 0.5, 0.5);
    spl.genSine(223.553, 0.5, 0.5, 0.5);

    spl.normalize(0.8);
    spl.saveToFile("testEnvelope src");

    spl.extractEnvelope(4000);

    spl.saveToFile("testEnvelope");

    spl.filterLowPass(10.0, 1, 1);

    spl.saveToFile("testEnvelopeLP");
}

void GenSounds::testXPEnvelope() {
    //xp low fi
    int lnt = 441000;

    Sample spl(lnt);

    //Sample& Sample::genSuperSaw(double fq, int nSaw, int seed, double detune, double ampMax1Saw) {
    //spl.genSuperSaw(110,10,1234,1.0/100.0,0.2);

    spl.loadFromFile("speech test");
    spl.saveToFile("testXPEnvelope a");

    spl.extractEnvelopeNoFilter(10);

    spl.saveToFile("testXPEnvelope b");
    spl.filterHiPass(20, 1, 2);

    spl.saveToFile("testXPEnvelope c");

}

void GenSounds::testVocoder() {

    const int nSine = 24, nHarmo = 6;
    const double sInc = 0.5;

    double dSInc = sInc * 2;

    double fBase = 220;

    Sample::tempo = 125;

    Sample splSrc(Sample::stepToInt(64));
    splSrc.loadFromFile("speech test"); //.saveToFile("speech test out");
    //splSrc.genSine(20,0.5,1,1);

    double lFile = Sample::intToStep(splSrc.fxIEnd);

    cout << "lFile : " << lFile << " step " << endl;

    double harmo[nHarmo] = {
        9.0 / 8.0,
        6.0 / 5.0,
        5.0 / 4.0,
        4.0 / 3.0,
        3.0 / 2.0,
        2.0
    };
    double rh = 1;
    for (int i = 0; i < nHarmo; i++) {
        cout << harmo[i] << endl;
        harmo[i] = harmo[i] / rh;
        rh = rh * harmo[i];
        cout << harmo[i] << endl;
    }

    Sample splC(Sample::stepToInt(0.5));
    Sample splD(Sample::stepToInt(1));
    Sample splOut(splSrc.fxIEnd);
    Sample splSine[nSine];

    double f = fBase;
    for (int i = 0; i < nSine; i++) {
        splSine[i].init(Sample::stepToInt(dSInc));
        splSine[i].genSine(f, 0.5, 1, 1);
        splSine[i].fxRangeStep(0, sInc).fadeIn();
        splSine[i].fxRangeStep(sInc, dSInc).fadeOut();
        splSine[i].fxRangeReset();

        cout << i << ", f : " << f << endl;

        f = f * harmo[i % nHarmo];


    }
    double rmsL, rmsR;

    for (double s = 0; s < (lFile - 1.0); s += sInc) {
        //parcours la source quart de step par quart de step
        splSrc.fxRangeStep(s, s + dSInc);

        splC.copy(splSrc);
        splC.fxRangeStep(0, sInc).fadeIn();
        splC.fxRangeStep(sInc, dSInc).fadeOut();
        splC.fxRangeReset();
        //splC.reverse();

        f = fBase;
        for (int i = 0; i < nSine; i++) {

            splD.copy(splC).filterBandPass(f, 3, 2);

            splD.avgRms(rmsL, rmsR);

            double sMix = s; // + (double) i;
            splOut.fxRangeStep(sMix, sMix + 1).mix(splSine[i], rmsL, rmsR);

            f = f * harmo[i % nHarmo];
        }

        cout << 100 * s / lFile << "%" << endl;

    }
    splOut.fxRangeReset().saveToFile("testVocoder a");

}

void GenSounds::testWaveShapeB() {

    Sample::tempo = 125;

    Sample splWS(200);

    Sample spl(Sample::stepToInt(256));

    splWS.setConstantDynamic(-1, 1);
    int j = 100;
    for (int i = 100; i < 200; i++) {

        splWS.dataL[i] = pow(splWS.dataL[i], 0.5 - splWS.dataL[i] / 3.0);
        splWS.dataL[j] = -splWS.dataL[i];
        j--;
    }
    splWS.mixChannel(1, 1, 0, 0);
    splWS.saveToFile("splWS b");

    spl.genSine(55, 0.5, 1, 1).fadeOut();
    spl.genSine(110, 0.5, 1, 1).fadeIn();

    spl.fxRangeStep(230, 256).fadeOut().fxRangeReset();

    spl.distoWaveShape(splWS, 1, 1);

    Sample splEnv(Sample::stepToInt(256));
    splEnv.setConstantDynamic(1, 0);
    spl.filterNotchEnv(110, splEnv, 5000, 1, 3);

    spl.distoWaveShape(splWS, 1, 1);
    spl.filterNotchEnv(220, splEnv, 10000, 1, 3);

    spl.saveToFile("testWaveShapeB");

}

void GenSounds::testWaveShape() {

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
    splWS.genSine(0.5, 0.75, 1, 1);

    splWS.genSine(16, 0, 0.1, 0.1);

    splWS.normalize(0.9);

    splWS.saveToFile("testWaveShape splWS");

    spl.genSuperSaw(55, 21, 7145, 0.005, 0.3);

    spl.filterLowPass(220, 3, 2);
    spl.filterLowPass(880, 1, 4);

    spl.normalize(1);
    spl.saveToFile("super saw src");

    spl.distoWaveShape(splWS, 1, 1);
    spl.saveToFile("super saw WS");
}

void GenSounds::genSndSuperSaw() {

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

void GenSounds::genSndAllPass() {
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

        splTmp.copy(spl).filterAllPassEnv(f * 2 + 50, splEnv, f, 10.2, 3);
        splTmp.normalize(0.8);

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

void GenSounds::genSndShepard() {
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

void GenSounds::genSndCristal() {

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

        spl.genWaveForm(wf, f, phase, ampL, ampR);
        wf.swapChannel();


    }

    spl.normalizeRmsW();
    spl.saveToFile("genSndCristal");

}

void GenSounds::wfHarmo() {

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

            spl.genWaveForm(wf, f, phase, ampL, ampR);
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

void GenSounds::genWaveForm() {

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

        test.genWaveForm(wf, f, phase, ampL, ampR);
        wf.swapChannel();
        if ((i % 10) == 9) {
            fBase += 110;
        }
    }

    test.normalizeRmsW();
    test.saveToFile("genWaveForm");

}

void GenSounds::pulseFilt() {
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

void GenSounds::vatBssNorm() {
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
    splEnv.addEnvExp(1, 0, 0.2);

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

void GenSounds::genWnSteckOctFilter() {
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

void GenSounds::genKick() {

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

void GenSounds::multiSinEnv() {


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
        splEnvF.addEnvExp(0.5, -0.5, 0.3 - ev * 0.31);
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

void GenSounds::testEnvGen() {
    Sample spl(44100 * 11);

    for (double speed = 0; speed < 1; speed += 0.1) {

        spl.fxIEnd = spl.fxIStart + 44100;
        spl.addEnvExp(-1, 1, speed);

        spl.fxIStart += 44100;

    }

    spl.fxRangeReset().saveToFile("testEnvGen.wav");

}

void GenSounds::testEnv() {

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

void GenSounds::testStereoA() {
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

void GenSounds::testStereoB() {

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

void GenSounds::testStereoC() {

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

void GenSounds::testSwoosh() {

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

void GenSounds::testReverse() {
    Sample spl(44100);
    spl.genSine().fadeOut().reverse().saveToFile("testReverse.wav");
}

void GenSounds::testDelay2() {

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

void GenSounds::testDelay() {
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

void GenSounds::testNotch() {
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

void GenSounds::genKickA() {

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

void GenSounds::testLoad() {
    Sample spl(100);
    spl.loadFromFile("kickA.wav");
    spl.saveToFile("kickA load save.wav");

}
