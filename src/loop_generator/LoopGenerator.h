/* 
 * File:   LoopGenerator.h
 * Author: tglo
 *
 * Created on 3 septembre 2016, 18:19
 */

#ifndef LOOPGENERATOR_H
#define	LOOPGENERATOR_H

#include <vector>
#include <sstream>
#include "Sound.h"
#include "EffetFactory.h"
#include "parametre/Parametre.h"

class LoopGenerator {
public:

    /*
     */
    // Sound *sound;



    //Paramettre param (type de boucle, séquence, position dans la séquence, notes autorisée (gamme) )
    LoopGenerator();



    void process();
    
private:
    
    std::vector<Sound> *soundVector;
    std::vector<Effet*> *effetVector;
    
    Parametre parametre;
    EffetFactory effetFactory;    
    
    //void addEffet();
    void genSeq();
    
    void initParametre();
    

};

#endif	/* LOOPGENERATOR_H */