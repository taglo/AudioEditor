/* 
 * File:   Step.h
 * Author: tglo
 *
 * Created on 15 septembre 2016, 06:46
 */

#ifndef STEP_H
#define	STEP_H

class Step{
    
    double velocite;
    double longueur;
    
    //notes, todo class MidiNote
    std::vector<int> *note;
    
    //param
    std::vector<double> *param;
    
};



#endif	/* STEP_H */

