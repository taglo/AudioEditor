/* 
 * File:   SquareAdd.h
 * Author: tglo
 *
 * Created on 11 septembre 2016, 11:16
 */

#ifndef SQUAREADD_H
#define	SQUAREADD_H

#include "Square.h"

class SquareAdd{
public:
    SquareAdd(std::vector<Square> *squareVectorIn) {
        squareVector=squareVectorIn;
        
    }
    void add() {
        Square sq;
        squareVector->push_back(sq);
        squareVector->size();
    }
private :    
    std::vector<Square> *squareVector;
};

#endif	/* SQUAREADD_H */

