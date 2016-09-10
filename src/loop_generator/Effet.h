/* 
 * File:   Effet.h
 * Author: tglo
 *
 * Created on 5 septembre 2016, 18:47
 */

#ifndef EFFET_H
#define	EFFET_H

#include <stdlib.h> 

class Effet {
public:
    Effet();

    /*
     * calcule si l'effet peut être ajouté
     * si c'est le cas ça le prépare
     */
    virtual bool ajoute( )=0;
    virtual void process( )=0;
    
};


#endif	/* EFFET_H */

