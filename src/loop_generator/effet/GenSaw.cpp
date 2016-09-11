
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
        
        process();
    }
    return ajoute;
}


void GenSaw::process(){
    
    Sound spl;
    
    //spl=new Sound();
    
    spl.init(10000);
    spl.genSaw().fadeOut().fadeAntiClick(500);
    
    
    soundVector->push_back(spl);
    cout << soundVector->size() << endl;
    cout << "GenSaw" << test << endl;
    //return 0;
}