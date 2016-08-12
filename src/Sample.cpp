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

    delete[] dataL;
    delete[] dataR;

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

Sample& Sample::changeLengthStep(double step) {
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

        delete[] dataR;
        dataR = new double[newLength];

        copyFromBuffer(*this, 0, 0, length);

        for (int i = length; i < newLength; i++) {
            dataL[i] = 0;
            dataR[i] = 0;
        }
    } else {
        //on raccourcis

        copyToBuffer(*this, 0, 0, newLength);

        delete[] dataL;
        dataL = new double[newLength];

        delete[] dataR;
        dataR = new double[newLength];

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

Sample& Sample::mix(Sample& splIn, double ampL, double ampR) {
    /*
            on mixe sur la longueur de splIn.fxLength
            si ça dépasse : on allonge Sample
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
        dataL[i] += splIn.dataL[jRead] * ampL;
        dataR[i] += splIn.dataR[jRead++] * ampR;
    }

    return *this;
}

Sample& Sample::modulate(Sample& splIn) {
    /*
            on module sur la longueur de splIn.fxLength
            si ça dépasse : on allonge Sample
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
        dataL[i] = dataL[i] * splIn.dataL[jRead];
        dataR[i] = dataR[i] * splIn.dataR[jRead++];
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

double Sample::midiNoteToFq(double midi_note) {
    return 440.0 * pow(2.0, (midi_note - 69.0) / 12.0);
}

double Sample::fqtoMidiNote(double fq) {
    return 69.0 + 12.0 * log2(fq / 440.0);
}

double Sample::dbToLin(double db) {
    return pow(10.0, db / 20.0);
}

double Sample::linToDb(double lin) {
    return 20.0 * log(lin) / log(10.0);
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
        dataR[i] = cst;
    }
    return *this;
}

Sample& Sample::setConstantDynamic(double cstStart, double cstEnd) {

    double cstInc = (cstEnd - cstStart) / ((double) fxLength());
    double cst = cstStart;

    for (int i = fxIStart; i < fxIEnd; i++) {
        dataL[i] = cst;
        dataR[i] = cst;
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

Sample& Sample::addConstantDynamic(double cstStart, double cstEnd) {

    double cstInc = (cstEnd - cstStart) / ((double) fxLength());
    double cst = cstStart;

    for (int i = fxIStart; i < fxIEnd; i++) {
        dataL[i] += cst;
        dataR[i] += cst;
        cst += cstInc;
    }
    return *this;
}

Sample& Sample::amplify(double amplitudeL, double amplitudeR) {
    for (int i = fxIStart; i < fxIEnd; i++) {
        dataL[i] *= amplitudeL;
        dataR[i] *= amplitudeR;
    }
    return *this;
}

Sample& Sample::swapChannel() {
    for (int i = fxIStart; i < fxIEnd; i++) {
        double bf = dataL[i];
        dataL[i] = dataR[i];
        dataR[i] = bf;
    }
    return *this;
}
//swapChannel

Sample& Sample::fade(double ampStart, double ampEnd) {
    if (fxLength() > 0) {
        ampEnd = (ampEnd - ampStart) / ((double) fxLength());

        for (int i = fxIStart; i < fxIEnd; i++) {
            dataL[i] *= ampStart;
            dataR[i] *= ampStart;

            ampStart += ampEnd;
        }
    }
    return *this;
}

Sample& Sample::fadeStereo(double ampStartL, double ampEndL, double ampStartR, double ampEndR) {
    if (fxLength() > 0) {
        double dLen = (double) fxLength();

        ampEndL = (ampEndL - ampStartL) / dLen;
        ampEndR = (ampEndR - ampStartR) / dLen;

        for (int i = fxIStart; i < fxIEnd; i++) {
            dataL[i] *= ampStartL;
            dataR[i] *= ampStartR;

            ampStartL += ampEndL;
            ampStartR += ampEndR;
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

void Sample::maxAmplitude(double &maxL, double &maxR) {
    maxL = 0;
    maxR = 0;

    for (int i = fxIStart; i < fxIEnd; i++) {
        if (dataL[i] > maxL) {
            maxL = dataL[i];
        } else if ((-dataL[i]) > maxL) {
            maxL = -dataL[i];
        }

        if (dataR[i] > maxR) {
            maxR = dataR[i];
        } else if ((-dataR[i]) > maxR) {
            maxR = -dataR[i];
        }
    }

}

void Sample::maxRmsW(double &maxL, double &maxR, int lntRms) {

    double sSumL = 0, sSumR = 0;

    Sample buf(lntRms);

    maxL = 0;
    maxR = 0;

    for (int i = fxIStart; i < fxIEnd; i++) {

        sSumL -= buf.dataL[buf.fxIStart];
        sSumR -= buf.dataR[buf.fxIStart];

        buf.dataL[buf.fxIStart] += dataL[i] * dataL[i];
        buf.dataR[buf.fxIStart] += dataR[i] * dataR[i];

        sSumL += buf.dataL[buf.fxIStart];
        sSumR += buf.dataR[buf.fxIStart];

        if (sSumL > maxL) maxL = sSumL;
        if (sSumR > maxR) maxR = sSumR;
        buf.fxIStart = (buf.fxIStart + 1) % buf.fxIEnd;
    }

    maxL = sqrt(maxL / (double) lntRms);
    maxR = sqrt(maxR / (double) lntRms);

}

Sample& Sample::normalizeRmsW(double dbNorm, int lntRms) {

    double maxL, maxR;

    maxRmsW(maxL, maxR, lntRms);

    double amplitude = dbToLin(dbNorm);

    if (maxL > 0 && maxR > 0) {
        amplify(amplitude / maxL, amplitude / maxR);
    }
    return *this;
}

Sample& Sample::normalize(double amplitude) {

    double maxL, maxR;

    maxAmplitude(maxL, maxR);

    if (maxL > 0 && maxR > 0) {
        amplify(amplitude / maxL, amplitude / maxR);
    }
    return *this;
}
