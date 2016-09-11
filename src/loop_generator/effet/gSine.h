/* 
 * File:   genSine.h
 * Author: tglo
 *
 * Created on 8 septembre 2016, 06:24
 */



#ifndef GENSINE_H
#define	GENSINE_H

#include "../Effet.h"


class gSine : public Effet {
public:
    gSine();
    virtual bool ajoute();
    virtual void process();
    int test;
};

#endif	/* GENSINE_H */

