
#include "EffetFactory.h"

void EffetFactory::setNew(vector<Effet*> *effetVector,vector<Sound> *soundVector) {

    Effet* cEffet;
    count = (count + 1) %3;

    switch (count) {
        case 0:
            cEffet = new gSine;
            break;
        case 1:
            cEffet = new gSaw;
            break;           
        case 2:
            cEffet = new eClip;
            break;              
    }
    
    cEffet->setSoundVector(soundVector);

    if(cEffet->ajoute()){

        std::cout<<soundVector->size()<<endl;
        effetVector->push_back(cEffet);
    }

}