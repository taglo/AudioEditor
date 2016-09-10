/* 
 * File:   EffetFactory.h
 * Author: tglo
 *
 * Created on 8 septembre 2016, 06:29
 */

#ifndef EFFETFACTORY_H
#define	EFFETFACTORY_H

#include "effet/GenSine.h"
#include "effet/GenSaw.h"

class EffetFactory{
public :
    
    int count=0;
    Effet* getNew();
    
};


#endif	/* EFFETFACTORY_H */

