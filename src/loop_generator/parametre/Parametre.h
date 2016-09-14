/* 
 * File:   Parameter.h
 * Author: tglo
 *
 * Created on 13 septembre 2016, 19:47
 */

#ifndef PARAMETRE_H
#define	PARAMETRE_H
#include <string>

using namespace std;

struct Parametre{
    double nStep=2048;
    double tempo=125;
    
    string typeBoucle="";
    int iTypeBoucle;
    
    static const int nTypeBoucle=6;
    static const string arrTypeBoucle[6];
    
};



#endif	/* PARAMETRE_H */

