/* 
 * File:   EffetFactory.h
 * Author: tglo
 *
 * Created on 8 septembre 2016, 06:29
 */

#ifndef EFFETFACTORY_H
#define	EFFETFACTORY_H
#include "parametre/Parametre.h"

#include "effet/gSine.h"
#include "effet/gSaw.h"
#include "effet/eClip.h"


class EffetFactory{
public :
    
    int count=0;
    void setNew(
            vector<Effet*> *effetVector,
            vector<Sound> *soundVector,
            Parametre *parametre
            );
    
};


#endif	/* EFFETFACTORY_H */

