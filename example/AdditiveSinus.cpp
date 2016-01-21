#include "AdditiveSinus.h"

AdditiveSinus::AdditiveSinus() {
}

void AdditiveSinus::generate() {
    using namespace std;



    Sample splBase(44100);
    Sample splSine(44100);

    for (int i = 0; i < 20; i++) {
        
        
        double k = (double) i;
        double fq= 440 + 16 * k;
        double phase=1;
        double amplitude=150/(300+10*k);
        
        splSine.genSine(fq,phase,amplitude).fadeOut();
        splBase.mix(splSine);
    }


    splBase.saveToFile("AdditiveSinus.wav");

    cout << "ok AdditiveSinus" << endl;
}