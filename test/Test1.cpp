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

    Sample spl2(44100);
    spl2.genBrownNoise(0.5,0.01).saveToFile("brown noise 0.01 .wav").setConstant(0);
    
    spl2.genBrownNoise(0.5,0.025).saveToFile("brown noise 0.025 .wav").setConstant(0);
    spl2.genBrownNoise(0.5,0.05).saveToFile("brown noise 0.05 .wav").setConstant(0);
    spl2.genBrownNoise(0.5,0.02).saveToFile("brown noise 0.1 .wav").setConstant(0);
    cout << "OK brown noise.wav"<< endl;    
}