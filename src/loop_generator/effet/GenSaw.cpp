
#include "GenSaw.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

GenSaw::GenSaw(){
}


bool GenSaw::ajoute(){
    bool ajoute=(rand()%3)>1;
    
    if(ajoute) {
        test=rand()%100;
    }
    return ajoute;
}


void GenSaw::process(){
    
    cout << "GenSaw" << test << endl;
    //return 0;
}