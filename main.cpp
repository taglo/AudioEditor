/* 
 * File:   main.cpp
 * Author: tglo
 *
 * Created on 9 janvier 2016, 15:12
 */
//#pragma once

#include <iostream>

#include "src/Sample.h"
#include "example/AdditiveSinus.h"
#include "example/GranularSquare.h"
#include "test/Test1.h"
#include "example/GenSounds.h"
#include "example/SongHardTech.h"

//#include "Tests.cpp"

using namespace std;

/*
 * 
 */

#include <random>
#include <ctime>

int main(int argc, char** argv) {

    /*
    Rng r(1234,-1.0,1.0);
    
    cout << "Seed 1234" << endl;
    cout << "Random value: " << r.next() << endl;
    cout << "Random value: " << r.next() << endl;
    cout << "Random value: " << r.next() << endl;
    
    Rng rb(12345,-1.0,1.0);
    
    cout << "Seed 12345" << endl;
    cout << "Random value: " << rb.next() << endl;
    cout << "Random value: " << rb.next() << endl;
    cout << "Random value: " << rb.next() << endl;
    
    Rng rc(1234,-1.0,1.0);
    
    cout << "Seed 1234" << endl;
    cout << "Random value: " << rc.next() << endl;
    cout << "Random value: " << rc.next() << endl;
    cout << "Random value: " << rc.next() << endl;
    
    Rng rd(12345,-1.0,100.0);
    
    cout << "Seed 12345" << endl;
    cout << "Random value: " << rd.next() << endl;
    cout << "Random value: " << rd.next() << endl;
    cout << "Random value: " << rd.next() << endl;
     */


   ///SongHardTech sng;
   //sng.generate();


     GenSounds gSnd;
     //gSnd.testStereoA();
    // gSnd.testStereoB();
      //gSnd.testStereoC();
     //gSnd.testEnvGen();
     gSnd.multiSinEnv();
             
     // gSnd.testSwoosh();
     //gSnd.testDelay2();

      //gSnd.testReverse();
    //gSnd.testLoad();
    //gSnd.genKickA();


    //testMx2();

    // testMx();

    //testFilter2();

    //testFilter();

    //testWfEnv();

    //testSineFm();
    //testWfMultiFun();
    //testWf();
    return 0;

    /*
        Sample spla(3000);
        spla.setConstant(1).fadeOut().saveToFile("test.wav");

        cout << "Ok." << endl;
     */
    double amp;


    Sample spla(40000);
    spla.genSine(55, 0, 0.5);

    Sample splb(15000);
    spla.strech(splb);
    splb.saveToFile("strech.wav");
    cout << "Ok." << endl;

    spla.setConstant(0);
    spla.genSine(305, 0, 0.5);

    spla.genPulse(302, 0, 0.25);

    spla.genPulse(290.59, 0, -0.25).fadeOut();

    splb.changeLength(29000).setConstant(0);

    splb.fxIEnd = 9000;
    amp = 0.75;
    for (int i = 0; i < 10; i++) {

        spla.strech(splb);
        spla.fxIStart = i * 71;
        spla.mix(splb, amp).fxRangeReset().normalize(0.9).clip(0.7);

        splb.fxIEnd += 500 - i*i;
        amp *= 0.9;
    }

    spla.saveToFile("multi strech.wav");


    /*
  double a_random_double = unif(re);
  
    std::mt19937_64 rd(100);
std::default_random_engine re(rd()); 

       rng.seed(100);
     */
    GranularSquare granularSquare;
    granularSquare.generate();

    /*
    Test1 test;
    test.generate();
     */
    /*
    AdditiveSinus additiveSinus;
    additiveSinus.generate();
     */
}

void testWf() {
    Sample splWf(1000);

    splWf.genSaw(44.1, 0, 1).saveToFile("splwf source.wav");

    Sample spla(44100);

    spla.genWaveform(splWf, 10, 0, 0.5).saveToFile("test wf 10hz.wav").setConstant(0);

    spla.genWaveform(splWf, 100, 0, 0.5).saveToFile("test wf 100hz.wav");

}

void testWfMultiFun() {

    Sample splWf(1000);
    Sample spla(441000);

    for (int i = 0; i < 20; i++) {
        double v = ((double) i) / 20;

        splWf.genSaw(44.1 + v * 3.2, 0, 0.2).normalize(0.7);

        spla.genWaveform(splWf, 50 + v * (1.2 + v * 0.31), v, 0.5);

    }

    spla.normalize(0.9).saveToFile("testWfMultiFun.wav");

}

void testSineFm() {


    Sample spla(441000);
    Sample splFm(441000);

    for (int i = 0; i < 20; i++) {

        double v = ((double) i) / 20;

        splFm.genSine(0.1 + 0.2 * v, v, 0.5).normalize(0.9);

        //(Sample& splIn, double f, double phase, double amplitude, double fmAmp)
        spla.genSineSplFM(splFm, 55 * v * 20, 0.3 * v*v, 0.3, 505 * v);

    }

    spla.normalize(0.9).saveToFile("testSineFm.wav");

}

void testWfEnv() {

    Sample splWf(1000);
    splWf.genSaw(44.1, 0, 1);


    Sample splEnv(441000);
    splEnv.genSine(1, 0.5, 0.25).genSine(1.1, 0.5, 0.25).addConstant(0.5).fadeOut();

    Sample spla(441000);

    spla.genWaveformEnv(splWf, splEnv, 110, 55, 0, 0.75).saveToFile("testWfEnv.wav");


    splEnv.setConstant(1).fadeOut();

    spla.setConstant(0).genWaveformEnv(splWf, splEnv, 110, 110, 0, 0.75).saveToFile("testWfEnv220v110.wav");
}

void testFilter() {

    Sample spl1(44100);
    Sample spl2(44100);

    spl1.genWhiteNoise(0.5, 75012365);

    spl1.copy(spl2);
    spl2.filterLowPass(200, 0.5, 1).normalize(0.9) .saveToFile("test low pass 200 0.5 1 pass.wav");

    spl1.copy(spl2);
    spl2.filterLowPass(200, 0.5, 2).normalize(0.9) .saveToFile("test low pass 200 0.5 2 pass.wav");

    spl1.copy(spl2);
    spl2.filterLowPass(200, 0.5, 4).normalize(0.9) .saveToFile("test low pass 200 0.5 4 pass.wav");

    spl1.copy(spl2);
    spl2.filterLowPass(200, 4, 1).normalize(0.9) .saveToFile("test low pass 200 4 1 pass.wav");

    spl1.copy(spl2);
    spl2.filterLowPass(200, 4, 2).normalize(0.9) .saveToFile("test low pass 200 4 2 pass.wav");

    spl1.copy(spl2);
    spl2.filterLowPass(200, 4, 4).normalize(0.9) .saveToFile("test low pass 200 4 4 pass.wav");
}

void testFilter2() {
    Sample spl1(44100);
    Sample spl2(44100);
    Sample spl3(44100);

    spl1.genSaw(55, 0.5, 0.5); //.fadeAntiClick(5000); //.saveToFile("testFilter2 saw source.wav");

    for (int nPass = 1; nPass < 10; nPass += 2) {
        for (double q = 0.5; q < 4; q += 0.5) {
            spl1.copy(spl2);
            spl2.filterLowPass(220, q, nPass).normalize(0.9).fadeAntiClick(5000);
            spl3.mix(spl2, 1);
            spl3.fxIStart += 44100;
        }
    }



    spl3.fxRangeReset();

    spl3.saveToFile("testFilter2 z progressif.wav");

}

void testMx() {

    //enveloppe
    double nsTot = 64;

    Sample::tempo = 123.0;

    Sample splEnvSrc(4.0);

    Sample splEnv(4.0);
    splEnvSrc.setConstantDynamic(1, 0).fadeAntiClick(350);
    splEnvSrc.saveToFile("env src.wav");
    int k = 0;
    for (double smix = 0; smix < nsTot; smix += 4) {
        splEnvSrc.clip(0.95, -0.9).normalize(1).fade(1, 0.27);
        splEnvSrc.saveToFile("env src test1.wav");

        splEnv.fxRangeStep(smix, smix + 4.0);
        splEnv.mix(splEnvSrc, 0.9);
        k++;
        if ((k) % 3 == 0) {
            smix -= 1;
        }
        if ((k) % 5 == 0) {
            smix -= 3;
        }
    }
    splEnv.fxRangeReset(). saveToFile("env dyna clip.wav");

    Sample splSaw(nsTot);
    splSaw.genSaw(55, 0, 0.5).filterLowPassFEnv(55, splEnv, 2500, 1, 4);
    splSaw.normalize(0.8);
    splSaw.saveToFile("saw dyna low filt.wav");

}

void testMx2() {

    //enveloppe
    double nsTot = 64;

    Sample::tempo = 120.0;

    Sample splEnv1(nsTot);
    Sample splEnv2(nsTot);

    splEnv1.genSine(4, 0.5, 1);
    splEnv1.fxRangeStep(0, 32).fadeOut().fxRangeStep(32, 64).fadeIn();
    splEnv1.fxRangeReset().fade(0.8, 1).clip(0.8, -0.8);

    splEnv2.genSine(8, 0.5, 1);
    splEnv2.fxRangeStep(0, 32).fadeIn().fxRangeStep(32, 64).fadeOut();
    splEnv2.fxRangeReset().fade(1, 0.8).clip(0.8, -0.8);

    splEnv1.mix(splEnv2, 1);


    Sample splSaw(nsTot);
    double phase = 0.111;
    for (double f = 55; f < 56; f += 0.09123) {
        splSaw.genSaw(f, phase, 1);
        phase += 0.0789;
    }
    splSaw.clip(1, -1).normalize(0.9);
    splSaw.filterLowPassFEnv(200, splEnv1, 200, 1, 4);

    splSaw.normalize(0.8);

    splSaw.saveToFile("saw dyna low filt testMx2.wav");

}
