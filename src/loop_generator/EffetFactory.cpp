
#include "EffetFactory.h"

Effet * EffetFactory::getNew() {

    Effet *cEffet;
    count = (count + 1) % 2;

    switch (count) {
        case 0:
            cEffet = new GenSine;
            break;
        case 1:
            cEffet = new GenSaw;
            break;            
    }

    return cEffet;

}