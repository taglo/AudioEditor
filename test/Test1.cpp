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
}