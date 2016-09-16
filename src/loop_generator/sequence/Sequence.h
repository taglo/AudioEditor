/* 
 * File:   Sequence.h
 * Author: tglo
 *
 * Created on 15 septembre 2016, 06:48
 */

#ifndef SEQUENCE_H
#define	SEQUENCE_H
#include "Step.h"
#include "../parametre/Parametre.h"
#include <iostream> 
#include <vector>

class Sequence{
    
public :
    Sequence();
    void process(vector<Step> *stepVectorIn);    
    void setParametre(Parametre *parametreIn);
    
    std::vector<Step> *stepVector;
    
private :
    int nParam;
    
    
    
    Parametre *parametre;
};

#endif	/* SEQUENCE_H */

