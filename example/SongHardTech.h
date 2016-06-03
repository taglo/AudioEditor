/* 
 * File:   SongHardTech.h
 * Author: tglo
 *
 * Created on 3 juin 2016, 16:08
 */

#ifndef SONGHARDTECH_H
#define	SONGHARDTECH_H



#endif	/* SONGHARDTECH_H */

#include "../src/Sample.h"

class SongHardTech {
public:

    SongHardTech()
    {

    };

    void generate() {
        Sample::filePath = "F:\\sounds\\SongHardTech\\";
        Sample::tempo = 147;

        genKick();

    }

private:

    Sample splKick;

    void genKick() {

        //enveloppe
        double nsTot = 4;



        Sample splSrc(1031);

        for (int i = 0; i < splSrc.fxIEnd; i++) {
            double di = ((double) i) / 31;
            splSrc.data[i] = 1 / (1 +  di * di);
        }
        splSrc.saveToFile("env src strech.wav");
        Sample splEnv(nsTot);
        splSrc.strech(splEnv);

        splEnv.normalize(1).fadeOut(); //.fadeOut();

        splEnv.saveToFile("spl env strech.wav");

        // Sample splKick(nsTot);
        splKick.changeLength(18000).fxRangeReset();

        splKick.genSineFEnv(50, splEnv, 460, 0, 1);

        splKick.fadeOut();
        splKick.fxRangeStep(1, 4).fadeOut();

        splKick.fxRangeStep(2, 4).fadeOut().fxRangeReset();
        splKick.saveToFile("kick.wav");
    }
};