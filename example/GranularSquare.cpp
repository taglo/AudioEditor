#include "GranularSquare.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>

#include <random>

#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>  

using namespace std;

GranularSquare::GranularSquare() {
}

void GranularSquare::generate() {

    int nGra = 0;

    std::ostringstream str;

    std::uniform_real_distribution<double> unif(0.0, 1.0);
    std::mt19937_64 re(12345);

    Sample spl(44100 * 5);

    Sample splGranule(44100);

    for (int i = 0; i < 3; i++) {

        str.str("");
        str.clear();
        str << "test" << i << ".wav";
        const char * cStr = str.str().c_str();

        spl.fxRangeReset().setConstant(0);

        nGra=200+(int) 100*unif(re);
        
        for (int j = 0; j < nGra; j++) {
            //spl.data[j] = 0.5;
            
            
        }
        // nGra=

        spl.saveToFile(cStr);
    }
}