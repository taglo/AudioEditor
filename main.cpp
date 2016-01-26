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
#include "test/Test1.h"

//#include "Tests.cpp"

using namespace std;

/*
 * 
 */

#include <random>
#include <ctime>

int main(int argc, char** argv) {

    /*
        Sample spla(3000);
        spla.setConstant(1).fadeOut().saveToFile("test.wav");

        cout << "Ok." << endl;
     */

    

    
    /*
  double a_random_double = unif(re);
  
    std::mt19937_64 rd(100);
std::default_random_engine re(rd()); 

       rng.seed(100);
     */

    Test1 test;
    test.generate();

    /*
    AdditiveSinus additiveSinus;
    additiveSinus.generate();
     */
}

