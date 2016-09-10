
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
        
        process();
    }
    return ajoute;
}


void GenSine::process(){
    
    Sound spl;
    spl.init(10000);
    spl.genSine();
    
    soundVector->push_back(spl);
    cout << soundVector->size() << endl;
    cout << "GenSine" << test << endl;
    //return 0;
}