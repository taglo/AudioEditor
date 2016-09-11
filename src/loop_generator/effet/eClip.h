/* 
 * File:   genSine.h
 * Author: tglo
 *
 * Created on 8 septembre 2016, 06:24
 */



#ifndef ECLIP_H
#define	ECLIP_H

#include "../Effet.h"


class eClip : public Effet {
public:
    eClip();
    virtual bool ajoute();
    virtual void process();
    int test;
    
private :
    int idxSpl=0;
    
    
    
    
};

#endif	/* ECLIP_H */

