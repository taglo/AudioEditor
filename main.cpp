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

//#include "Tests.cpp"

using namespace std;

/*
 * 
 */

#include <random>
#include <ctime>

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

    spl1.genWhiteNoise(0.5);

    spl1.copy(spl2);
    spl2.filterLowPass(200, 0.5) .saveToFile("test low pass 200 0.5.wav");

    spl1.copy(spl2);
    spl2.filterLowPass(200, 1) .saveToFile("test low pass 200 1.wav");

    spl1.copy(spl2);
    spl2.filterLowPass(500, 3) .saveToFile("test low pass 500 3.wav");

    spl1.copy(spl2);
    spl2.filterLowPass(500, 10) .saveToFile("test low pass 500 10.wav");


}

int main(int argc, char** argv) {

    testFilter();

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


