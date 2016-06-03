/* 
 * File:   GensSounds.h
 * Author: tglo
 *
 * Created on 1 juin 2016, 13:48
 */

#ifndef GENSSOUNDS_H
#define	GENSSOUNDS_H



#endif	/* GENSSOUNDS_H */

#include "../src/Sample.h"

class GenSounds {
    
public:

    void genKickA() {

        //enveloppe
        double nsTot = 4;

        Sample::tempo = 147;

        Sample splSrc(1031);
        for (int i = 0; i < splSrc.fxIEnd; i++) {
            double di = ((double) i) / 25;
            splSrc.data[i] = 1 / (1 + di * di * di);
        }
        splSrc.saveToFile("env src strech.wav");
        Sample splEnv(nsTot);
        splSrc.strech(splEnv);

        splEnv.normalize(1).fadeOut(); //.fadeOut();

        splEnv.saveToFile("spl env strech.wav");

        Sample splKick(nsTot);
        splKick.genSineFEnv(50, splEnv, 450, 0, 1);

        splKick.fadeOut();
        splKick.fxRangeStep(1, 4).fadeOut();

        splKick.fxRangeStep(2, 4).fadeOut().fxRangeReset();
        splKick.saveToFile("kickA.wav");

    }

    void testLoad() {
        Sample spl(100);
        spl.loadFromFile("kickA.wav");
        spl.saveToFile("kickA load save.wav");
        
    }
};