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

#include <random>

int main(int argc, char** argv) {

    /*
        Sample spla(3000);
        spla.setConstant(1).fadeOut().saveToFile("test.wav");

        cout << "Ok." << endl;
     */
    double lower_bound = -1;
    double upper_bound = 1;
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::mt19937_64 re(752);

    /*
  double a_random_double = unif(re);
  
    std::mt19937_64 rd(100);
std::default_random_engine re(rd()); 

       rng.seed(100);
     */

    for (int i = 0; i < 10; ++i)
        std::cout << unif(re) << std::endl;

    /*
    AdditiveSinus additiveSinus;
    additiveSinus.generate();
     */
}

