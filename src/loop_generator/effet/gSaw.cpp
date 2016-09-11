
#include "gSaw.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

gSaw::gSaw(){
    
}


bool gSaw::ajoute(){
    bool ajoute=(rand()%3)>1;
    
    if(ajoute) {
        test=rand()%100;
        
        process();
    }
    return ajoute;
}


void gSaw::process(){
    
    Sound spl;
    
    //spl=new Sound();
    
    spl.init(10000);
    spl.genSaw().fadeOut().fadeAntiClick(500);
    
    
    soundVector->push_back(spl);
    cout << soundVector->size() << endl;
    cout << "gSaw" << test << endl;
    //return 0;
}