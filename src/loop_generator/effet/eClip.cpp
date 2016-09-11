
#include "eClip.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

eClip::eClip() {
}

bool eClip::ajoute() {

    bool ajoute = (rand() % 3) > 1;

    if (soundVector->size() == 0) {
        ajoute = false;
    }
    
    if (ajoute) {
        test = rand() % 100;
        idxSpl = rand() % soundVector->size();

        process();
    }
    return ajoute;
}

void eClip::process() {


    (*soundVector)[idxSpl].clip(0.5,-0.5);

    cout << soundVector->size() << endl;
    cout << "eClip" << test << endl;
    //return 0;
}