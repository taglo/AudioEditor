/* 
 * File:   Test1.cpp
 * Author: tglo
 * 
 * Created on 26 janvier 2016, 07:06
 */

#include "Test1.h"

#include <iostream>
using namespace std;

Test1::Test1() {

}

void Test1::generate() {

    Sample spl(44100);
    spl.genWhiteNoise(0.2, 456789).saveToFile("white noise.wav");
    cout << "OK white noise.wav" << endl;

    spl.genSine(55, 0, 1).clip(0.5, -0.5).saveToFile("test clip.wav").fadeOut().amplify(2.0,2.0).clip(0.7, -0.7).saveToFile("test clip 2.wav");
    cout << "OK clip" << endl;

    Sample spl2(44100);
    spl2.genBrownNoise(0.5, 0.01).saveToFile("brown noise 0.01 .wav").setConstant(0);

    spl2.genBrownNoise(0.5, 0.025).saveToFile("brown noise 0.025 .wav").setConstant(0);
    spl2.genBrownNoise(0.5, 0.05).saveToFile("brown noise 0.05 .wav").setConstant(0);
    spl2.genBrownNoise(0.5, 0.02).saveToFile("brown noise 0.1 .wav").setConstant(0);
    cout << "OK brown noise.wav" << endl;

    Sample spl3(64);
    spl3.genPinkNoise(0.5).saveToFile("pink noise.wav");
    cout << "OK pink noise.wav" << endl;

    spl.setConstant(0).genSquare(55, 0.5, 0.5, 0.25).saveToFile("test square w0.25.wav");
    spl.setConstant(0).genSquare(55, 0.5, 0.5, 0.5).saveToFile("test square w0.5.wav");
    spl.setConstant(0).genSquare(55, 0.5, 0.5, 0.75).saveToFile("test square w0.75.wav");
    cout << "OK test squares" << endl;

    spl.setConstant(0);
    for (int i = 0; i < 20; i++) {
        double v = ((double) i) / 20;
        spl.genSquare(55 + 4.7 * v*v, 0.5 + v / 10, 0.25, 0.3 + v * 0.6);
    }
    spl.fxRange(5000, spl.fxIEnd).fadeOut().fxRangeReset();
    spl.fxRange(0, 3000).fadeIn().fxRangeReset();
    spl.normalize(0.8).saveToFile("test square sup.wav");
    cout << "OK test square sup" << endl;

    spl.setConstant(0);
    double cf = 880;
    double w = 0.5;
    for (int i = 0; i < 20; i++) {
        double v = ((double) i) / 20;
        cf += 11.7 * v*v;
        if (cf > 900) cf -= 20;
        w += 0.371 * v;
        if (w > 1) w -= 1;
        spl.genSquare(cf, 0.5 + v * 3.72, 0.25, w);
    }
    spl.fxRange(5000, spl.fxIEnd).fadeOut().fxRangeReset();
    spl.fxRange(0, 3000).fadeIn().fxRangeReset();
    spl.normalize(0.8).saveToFile("test square sup b.wav");
    cout << "OK test square sup b" << endl;

}