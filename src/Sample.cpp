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
double* Sample::buffer = new double[441000];

Sample::Sample(int length) {
    Sample::length = length;
    data = new double[length];

    fxIStart = 0;
    fxIEnd = length;

    samplerate = 44100;

    setConstant(0);
}

Sample::Sample(const Sample& other) {
    Sample::length = other.length;
    Sample::samplerate = other.samplerate;
    data = new double[length];
    fxIStart = 0;
    fxIEnd = length;
    for (int i = 0; i < length; i++) {
        data[i] = other.data[i];
    }
}

Sample& Sample::operator=(const Sample& other) {
    //todo : utiliser constructeur
    Sample::length = other.length;
    Sample::samplerate = other.samplerate;
    data = new double[length];
    fxIStart = other.fxIStart;
    fxIEnd = other.fxIEnd;
    for (int i = 0; i < length; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

Sample::~Sample() {
    delete[] data;
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
        copyToBuffer(data, 0, 0, length);

        delete[] data;
        data = new double[newLength];

        copyFromBuffer(data, 0, 0, length);

        for (int i = length; i < newLength; i++) {
            data[i] = 0;
        }
    } else {
        //on raccourcis

        copyToBuffer(data, 0, 0, newLength);

        delete[] data;
        data = new double[newLength];

        copyFromBuffer(data, 0, 0, newLength);

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
        Sample::data[i] += splIn.data[jRead++] * amplitude;
    }

    return *this;
}

Sample& Sample::fxRange(int iStart, int iEnd) {
    fxIStart = iStart;
    fxIEnd = iEnd;
    return *this;
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

Sample& Sample::setConstant(double cst = 0) {

    for (int i = fxIStart; i < fxIEnd; i++) {
        data[i] = cst;
    }
    return *this;
}

Sample& Sample::amplify(double amplitude) {
    for (int i = fxIStart; i < fxIEnd; i++) {
        data[i] *= amplitude;
    }
    return *this;
}

Sample& Sample::fade(double ampStart, double ampEnd) {
    if (fxLength() > 0) {
        ampEnd = (ampEnd - ampStart) / ((double) fxLength());

        for (int i = fxIStart; i < fxIEnd; i++) {
            data[i] *= ampStart;
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
    if (fxIStart > length) fxIStart = length;
    fadeIn();

    fxIStart = iFxS;
    fxIEnd = iFxE;

    return *this;
}

double Sample::maxAmplitude() {
    double ampMax = 0;
    for (int i = fxIStart; i < fxIEnd; i++) {
        if (data[i] > ampMax) {
            ampMax = data[i];
        } else if ((-data[i]) > ampMax) {
            ampMax = -data[i];
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
