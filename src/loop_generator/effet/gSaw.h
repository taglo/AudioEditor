/* 
 * File:   genSine.h
 * Author: tglo
 *
 * Created on 8 septembre 2016, 06:24
 */



#ifndef GENSAW_H
#define	GENSAW_H

#include "../Effet.h"


class gSaw : public Effet {
public:
    gSaw();
    virtual bool ajoute();
    virtual void process();
    int test;
};

#endif	/* GENSAW_H */

