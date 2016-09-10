/* 
 * File:   genSine.h
 * Author: tglo
 *
 * Created on 8 septembre 2016, 06:24
 */



#ifndef GENSINE_H
#define	GENSINE_H

#include "../Effet.h"


class GenSine : public Effet {
public:
    GenSine();
    virtual bool ajoute();
    virtual void process();
    int test;
};

#endif	/* GENSINE_H */

