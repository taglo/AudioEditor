/* 
 * File:   LoopGenerator.h
 * Author: tglo
 *
 * Created on 3 septembre 2016, 18:19
 */

#ifndef LOOPGENERATOR_H
#define	LOOPGENERATOR_H

#include <vector>
#include "Sound.h"
#include "EffetFactory.h"

class LoopGenerator {
public:

    /*
     */
    // Sound *sound;



    //Paramettre param (type de boucle, séquence, position dans la séquence, notes autorisée (gamme) )
    LoopGenerator();



    void process();
private:
    std::vector<Sound> soundVector;
    std::vector<Effet*> effetVector;

    EffetFactory effetFactory;
};

#endif	/* LOOPGENERATOR_H */