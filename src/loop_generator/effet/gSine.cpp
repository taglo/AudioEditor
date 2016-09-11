
#include "gSine.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

gSine::gSine(){
}


bool gSine::ajoute(){
    bool ajoute=(rand()%3)>1;
    
    if(ajoute) {
        test=rand()%100;
        
        process();
    }
    return ajoute;
}


void gSine::process(){
    
    Sound spl;
    
    spl.init(10000);
    spl.genSine().fadeOut().fadeAntiClick(500);
    
    
    soundVector->push_back(spl);
    cout << soundVector->size() << endl;
    cout << "gSine" << test << endl;
}