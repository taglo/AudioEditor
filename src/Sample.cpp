//#pragma once
//#include <cstdlib>
//#include <cstring>
//#include <stdlib.h>
#include "Sample.h"


/*
pour les filtres :
https://github.com/vinniefalco/DSPFilters

 */
int Sample::samplerate = 44100;
double Sample::tempo = 120;
int Sample::bufferLength = 44100 * 10;
double* Sample::bufferL = new double[441000];
double* Sample::bufferR = new double[441000];
string Sample::filePath = "F:\\sounds\\";

Sample::Sample() {
    Sample::length = 1;
    
    dataL = new double[1];
    dataR = new double[1];

    fxIStart = 0;
    fxIEnd = 1;

    samplerate = 44100;

    setConstant(0);
}

Sample::Sample(int length) {
    Sample::length = length;
    
    dataL = new double[length];
    dataR = new double[length];
    
    fxIStart = 0;
    fxIEnd = length;

    samplerate = 44100;

    setConstant(0);
}

Sample& Sample::init(int length) {

    Sample::length = length;
    
    dataL = new double[length];
    dataR = new double[length];
    
    fxIStart = 0;
    fxIEnd = length;

    samplerate = 44100;

    setConstant(0);
    
    return *this;
}
/*
Sample::Sample(double nStep) {
    //todo réutiliser le normal ?
    Sample::length = stepToInt(nStep);

    dataL = new double[length];

    fxIStart = 0;
    fxIEnd = length;

    samplerate = 44100;

    setConstant(0);
}
*/
Sample::Sample(const Sample& other) {
    Sample::length = other.length;
    Sample::samplerate = other.samplerate;
    
    dataL = new double[length];
    dataR = new double[length];
    fxIStart = 0;
    fxIEnd = length;
    for (int i = 0; i < length; i++) {
        dataL[i] = other.dataL[i];
        dataR[i] = other.dataR[i];
    }
}

Sample& Sample::operator=(const Sample& other) {
    //todo : utiliser constructeur
    
    Sample::length = other.length;
    Sample::samplerate = other.samplerate;
    
    dataL = new double[length];
    dataR = new double[length];
    
    fxIStart = other.fxIStart;
    fxIEnd = other.fxIEnd;
    for (int i = 0; i < length; i++) {
        dataL[i] = other.dataL[i];
        dataR[i] = other.dataR[i];
    }
    return *this;
}

Sample::~Sample() {
    delete[] dataL;
    delete[] dataR;
}


Sample& Sample::changeLengthStep(double step){
    changeLength(stepToInt(step));
    return *this;
}
/*
Sample& Sample::operator*(const double amplitude){
        Sample::amplify(amplitude);
        return *this;
}
 */

/**
 *  sample          ---------------
 *  newLength       |       |
 *  out             |-------|
 */
Sample& Sample::changeLength(int newLength) {
    //todo : regrouper
    //int copyLength = (newLength > length) ? length : newLength;

    if (newLength > length) {
        //allonge
        copyToBuffer(*this, 0, 0, length);

        delete[] dataL;
        dataL = new double[newLength];

        copyFromBuffer(*this, 0, 0, length);

        for (int i = length; i < newLength; i++) {
            dataL[i] = 0;
        }
    } else {
        //on raccourcis

        copyToBuffer(*this, 0, 0, newLength);

        delete[] dataL;
        dataL = new double[newLength];

        copyFromBuffer(*this, 0, 0, newLength);

        if (fxIStart < newLength) {
            fxIStart = 0;
            fxIEnd = length;
        } else if (fxIEnd < newLength) {
            fxIEnd = length;
        }
    }

    length = newLength;

    return *this;
}

Sample& Sample::mix(Sample& splIn, double amplitude) {
    /*
            on mixe sur la longueur de splIn.fxLength
            si �a d�passe : on allonge Sample
     */

    /*
    int jRead=splIn.fxIStart;
    int iMixEnd = fxIStart + splIn.fxLength();

    if (iMixEnd > length){
            changeLength(iMixEnd);
    }
     */
    int jRead, iMixEnd;
    prepareForSplIn(splIn, jRead, iMixEnd);

    for (int i = fxIStart; i < iMixEnd; i++) {
        Sample::dataL[i] += splIn.dataL[jRead++] * amplitude;
    }

    return *this;
}

Sample& Sample::fxRange(int iStart, int iEnd) {
    fxIStart = iStart;
    fxIEnd = iEnd;
    return *this;
}

Sample& Sample::fxRangeStep(double stepStart, double stepEnd) {
    fxIStart = stepToInt(stepStart);
    fxIEnd = stepToInt(stepEnd);

    return *this;
}

int Sample::stepToInt(double step) {
    
    return (int) ((240 / tempo)*((double) samplerate) *(step / 16));
}

Sample& Sample::fxRangeReset() {
    fxIStart = 0;
    fxIEnd = length;
    return *this;
}

Sample& Sample::fxRangeCheck() {

    if (fxIStart < fxIEnd) {
        int iTmp = fxIStart;
        fxIStart = fxIEnd;
        fxIEnd = iTmp;
    }
    if (fxIEnd > length) {
        fxIEnd = length;
    }

    return *this;
}

int Sample::fxLength() {
    return fxIEnd - fxIStart;
}

Sample& Sample::setConstant(double cst) {

    for (int i = fxIStart; i < fxIEnd; i++) {
        dataL[i] = cst;
    }
    return *this;
}

Sample& Sample::setConstantDynamic(double cstStart, double cstEnd) {

    double cstInc = (cstEnd - cstStart) / ((double) fxLength());
    double cst = cstStart;

    for (int i = fxIStart; i < fxIEnd; i++) {
        dataL[i] = cst;
        cst += cstInc;
    }
    return *this;
}

Sample& Sample::addConstant(double cst) {

    for (int i = fxIStart; i < fxIEnd; i++) {
        dataL[i] += cst;
    }
    return *this;
}

Sample& Sample::amplify(double amplitude) {
    for (int i = fxIStart; i < fxIEnd; i++) {
        dataL[i] *= amplitude;
    }
    return *this;
}

Sample& Sample::fade(double ampStart, double ampEnd) {
    if (fxLength() > 0) {
        ampEnd = (ampEnd - ampStart) / ((double) fxLength());

        for (int i = fxIStart; i < fxIEnd; i++) {
            dataL[i] *= ampStart;
            ampStart += ampEnd;
        }
    }
    return *this;
}

Sample& Sample::fadeIn() {
    fade(0, 1);
    return *this;
}

Sample& Sample::fadeOut() {
    fade(1, 0);
    return *this;
}

Sample& Sample::fadeAntiClick(int fadeLength) {
    int iFxS = fxIStart, iFxE = fxIEnd;

    fxIStart = iFxS - fadeLength;
    if (fxIStart < 0) fxIStart = 0;
    fxIEnd = iFxS;
    fadeOut();

    fxIStart = iFxS;
    fxIEnd = iFxS + fadeLength;
    if (fxIStart > length) fxIStart = length;
    fadeIn();

    fxIStart = iFxE - fadeLength;
    if (fxIStart < 0) fxIStart = 0;
    fxIEnd = iFxE;
    fadeOut();

    fxIStart = iFxE;
    fxIEnd = iFxE + fadeLength;
    if (fxIEnd > length) fxIEnd = length;
    fadeIn();

    fxIStart = iFxS;
    fxIEnd = iFxE;

    return *this;
}

double Sample::maxAmplitude() {
    double ampMax = 0;
    for (int i = fxIStart; i < fxIEnd; i++) {
        if (dataL[i] > ampMax) {
            ampMax = dataL[i];
        } else if ((-dataL[i]) > ampMax) {
            ampMax = -dataL[i];
        }
    }
    return ampMax;
}

Sample& Sample::normalize(double amplitude) {
    double ampMax = maxAmplitude();
    if (ampMax > 0) {
        amplify(amplitude / ampMax);
    }
    return *this;
}
