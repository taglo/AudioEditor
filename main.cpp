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


//#include "Tests.cpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

/*
    Sample spla(3000);
    spla.setConstant(1).fadeOut().saveToFile("test.wav");

    cout << "Ok." << endl;
*/
    
    AdditiveSinus additiveSinus;
    additiveSinus.generate();

}

