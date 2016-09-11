/* 
 * File:   process.h
 * Author: tglo
 *
 * Created on 11 septembre 2016, 11:12
 */

#ifndef PROCESS_H
#define	PROCESS_H

#include <iostream>
#include <vector>
#include "Square.h"
#include "SquareAdd.h"

class Process {
public:

    void gen() {

        squareVector=new vector<Square>;
        
        SquareAdd sqAdd(squareVector);
        
        squareVector->clear();

        for(int i=0;i<10;i++) {
            sqAdd.add();
        }
        
        std:cout << squareVector->size() << endl;
        
        
        for(int i=0;i<10;i++) {
            (*squareVector)[i].debug();
            
            
        }
         
        
    }
private:
    
    std::vector<Square> *squareVector;

};


#endif	/* PROCESS_H */

