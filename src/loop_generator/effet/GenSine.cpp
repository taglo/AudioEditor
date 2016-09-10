
#include "GenSine.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

GenSine::GenSine(){
}


bool GenSine::ajoute(){
    bool ajoute=(rand()%3)>1;
    
    if(ajoute) {
        test=rand()%100;
    }
    return ajoute;
}


void GenSine::process(){
    
    cout << "GenSine" << test << endl;
    //return 0;
}