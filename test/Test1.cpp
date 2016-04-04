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
    spl.genWhiteNoise(0.2).saveToFile("white noise.wav");
    cout << "OK white noise.wav"<< endl;

    spl.genSine(55,0,1).clip(0.5,-0.5).saveToFile("test clip.wav").fadeOut().amplify(2).clip(0.7,-0.7).saveToFile("test clip 2.wav");
    cout << "OK clip"<< endl;
    
    Sample spl2(44100);
    spl2.genBrownNoise(0.5,0.01).saveToFile("brown noise 0.01 .wav").setConstant(0);
    
    spl2.genBrownNoise(0.5,0.025).saveToFile("brown noise 0.025 .wav").setConstant(0);
    spl2.genBrownNoise(0.5,0.05).saveToFile("brown noise 0.05 .wav").setConstant(0);
    spl2.genBrownNoise(0.5,0.02).saveToFile("brown noise 0.1 .wav").setConstant(0);
    cout << "OK brown noise.wav"<< endl;    
    
    Sample spl3(64);
    spl3.genPinkNoise(0.5).saveToFile("pink noise.wav");
    cout << "OK pink noise.wav"<< endl; 

    spl.setConstant(0).genSquare(55,0.5,0.5,0.25).saveToFile("test square w0.25.wav");
    spl.setConstant(0).genSquare(55,0.5,0.5,0.5).saveToFile("test square w0.5.wav");
    spl.setConstant(0).genSquare(55,0.5,0.5,0.75).saveToFile("test square w0.75.wav");
    cout << "OK clip"<< endl;    
}