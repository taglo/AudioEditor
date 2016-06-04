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
using namespace std;

class SongHardTech {
public:

    SongHardTech() {

    };

    void generate() {
        Sample::filePath = "F:\\sounds\\SongHardTech\\";
        Sample::tempo = 147;



        genKick();
        genBass();
        genHihat();

        genKickTrack();
        genBassTrack();

        //todo suite affine hihat, gen hihat track sur track[2]
        //cf http://joesul.li/van/synthesizing-hi-hats/
        /*
        for(int i=0;i<10;i++){
            track[0].loadFromFile("track0.wav").saveToFile("track0");
            cout << "test load save" << i << endl;
        }
         */

        //mixdown
        track[0].fxRangeStep(0, nsSong);
        for (int i = 1; i < 2; i++) {
            track[i].fxRangeStep(0, nsSong);

            track[0].mix(track[i], 1);
        }
        track[0].saveToFile("SongHardTech.wav");
    }

private:

    double nsSong = 3072;
    Sample splKick;
    Sample splBass;
    Sample splHihat;

    Sample track[50];

    void genKick() {
        cout << "genKick" << endl;

        //enveloppe
        double nsTot = 4;



        Sample splSrc(1031);

        for (int i = 0; i < splSrc.fxIEnd; i++) {
            double di = ((double) i) / 31;
            splSrc.data[i] = 1 / (1 + di * di);
        }
        splSrc.saveToFile("env src strech.wav");
        Sample splEnv(nsTot);
        splSrc.strech(splEnv);

        splEnv.normalize(1).fadeOut(); //.fadeOut();

        splEnv.saveToFile("spl env strech.wav");

        // Sample splKick(nsTot);
        splKick.changeLengthStep(4.0).fxRangeReset();

        splKick.genSineFEnv(50, splEnv, 460, 0, 1);

        splKick.fadeOut();
        splKick.fxRangeStep(1, 4).fadeOut();

        splKick.fxRangeStep(2, 4).fadeOut().fxRangeReset();
        splKick.saveToFile("kick.wav");
    }

    void genBass() {
        cout << "genBass" << endl;

        //enveloppe
        double nsTot = 3;

        Sample splSrc(997);

        for (int i = 0; i < splSrc.fxIEnd; i++) {
            double di = ((double) i) / 36;
            splSrc.data[i] = 1 / (1 + di * di);
        }
        splSrc.saveToFile("env src strech bss.wav");
        Sample splEnv(nsTot);
        splSrc.strech(splEnv);

        splEnv.normalize(1).fadeOut(); //.fadeOut();

        splEnv.saveToFile("spl env strech bss.wav");

        splBass.changeLengthStep(nsTot).fxRangeReset();

        splBass.genSineFEnv(50, splEnv, 53, 0, 1);
        splBass.genSineFEnv(50.13, splEnv, 55, 0.1, 1);
        splBass.genSineFEnv(51.73, splEnv, 45, 0.1, 1);

        splBass.normalize(0.5);
        splBass.fxRangeStep(2, 3).fadeOut();

        splBass.fxRangeStep(2.5, 3).fadeOut().fxRangeReset();
        splBass.fadeAntiClick(250);
        splBass.saveToFile("bass.wav");
    }

    void genHihat() {
        cout << "genHihat" << endl;
        double nsTot = 5;
        splHihat.changeLengthStep(nsTot).fxRangeReset();

        splHihat.genWhiteNoise(0.1, 723).fadeOut(); //todo seed

        //todo hi pass
        splHihat.fxRangeStep(1, nsTot).fadeOut();
        splHihat.fxRangeStep(4, nsTot).fadeOut();

        splHihat.fxRangeReset();

        splHihat.saveToFile("hihat A.wav");

        uniform_real_distribution<double> unif(120.0, 530.0);
        mt19937_64 re(666777);

        double fq = 0;
        double phase = 0;
        double width = 0;
        
        for (int i = 0; i < 31; i++) {
            phase += 1.0 / 2.203;
            width += 1.0 / 7.431;
            if (width > 1) {
                width = phase / 16;
            }
            fq=unif(re);
            splHihat.genSquare(fq, phase, 0.3, width);


        }

        splHihat.filterHiPass(400, 1.89, 1);
        splHihat.fxRangeStep(0.0, 0.05).fadeIn();
        splHihat.fxRangeReset();

        splHihat.normalize(0.3);
        splHihat.fxRangeStep(1, nsTot).fadeOut();
        splHihat.fxRangeStep(4, nsTot).fadeOut();
        splHihat.fxRangeReset();

        splHihat.normalize(0.3);
        splHihat.saveToFile("hihat B.wav");

        splHihat.filterBandPass(9000, 0.89, 1);
        splHihat.normalize(0.3);
        splHihat.saveToFile("hihat C.wav");

        splHihat.filterHiPass(3000, 1.189, 1);
        splHihat.filterHiPass(4000, 1.89, 1);
        splHihat.filterHiPass(6000, 1.089, 1);


        splHihat.normalize(0.3);

        splHihat.saveToFile("hihat.wav");

    }

    void genKickTrack() {

        cout << "genKickTrack" << endl;

        track[0].changeLengthStep(nsSong).fxRangeReset();

        for (double s = 0; s < nsSong; s += 4) {
            track[0].fxRangeStep(s, s + 4).mix(splKick);
        }


        double sstart = 0;
        double sinc = 1024;
        double send;
        do {
            double ev = sstart / nsSong;
            send = sstart + sinc;
            if (send >= nsSong) {
                send = nsSong;
            }
            track[0].fxRangeStep(sstart, send);
            track[0].fade(0.7 + 0.3 * ev, 0.99);
            sinc = sinc - 128;
            sstart = send;
        } while (send < nsSong);

        track[0].fxRangeStep(990, 1024).fadeOut();
        track[0].fxRangeStep(1000, 1024).fadeOut();
        track[0].fxRangeStep(1010, 1024).fadeOut();

        track[0].fxRangeStep(1990, 2048).fadeOut();
        track[0].fxRangeStep(2000, 2048).fadeOut();
        track[0].fxRangeStep(2001, 2048).fadeOut();

        track[0].fxRangeReset().saveToFile("track0.wav");
    }

    void genBassTrack() {

        cout << "genBassTrack" << endl;

        track[1].changeLengthStep(nsSong).fxRangeReset();

        for (double s = 2; s < nsSong; s += 4) {
            track[1].fxRangeStep(s, s + 3).mix(splBass);
        }


        double sstart = 0;
        double sinc = 1024 + 256;
        double send;
        do {
            double ev = sstart / nsSong;
            send = sstart + sinc;
            if (send >= nsSong) {
                send = nsSong;
            }
            track[1].fxRangeStep(sstart, send);
            track[1].fade(0.7 + 0.3 * ev, 0.99);
            sinc = sinc - 128;
            sstart = send;
        } while (send < nsSong);

        track[1].fxRangeStep(990, 1024 - 256).fadeOut();
        track[1].fxRangeStep(1000, 1024 - 256).fadeOut();
        track[1].fxRangeStep(1010, 1024 - 256).fadeOut();

        track[1].fxRangeStep(1990, 2048).fadeOut();
        track[1].fxRangeStep(2000, 2048).fadeOut();
        track[1].fxRangeStep(2001, 2048).fadeOut();

        track[1].fxRangeReset().saveToFile("track1.wav");
    }
};