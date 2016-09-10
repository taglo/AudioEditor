#pragma once
#ifndef SAMPLE_H
#define SAMPLE_H

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <string>
#include "helper/RbjFilter.h"
#include "helper/Delay.h"
#include "helper/Rng.h"
#include "helper/RiffHeader.h"

//#include "TestClass.h"


using namespace std;

class Sample {
public:

    double *dataL;
    double *dataR;
    int length;
    int fxIStart;
    int fxIEnd;

    static int samplerate;
    static double tempo;
    static string filePath;



    Sample();
    Sample(int length);
    //Sample(double nStep);
    Sample(const Sample& other);
    Sample& operator=(const Sample& other);

    Sample& init(int length);



    class TestInner;
    TestInner* test;

    //void init(int length);

    Sample& fxRange(int iStart, int iEnd);
    Sample& fxRangeStep(double stepStart = 0, double stepEnd = 0);



    Sample& fxRangeReset();
    Sample& fxRangeCheck();

    int fxLength();

    Sample& setConstant(double cst = 0);
    Sample& setConstantDynamic(double cstStart = 1, double cstEnd = 0);
    Sample& addConstant(double cst = 0);
    Sample& addConstantDynamic(double cstStart = 1, double cstEnd = 0);
    Sample& changeLength(int newLength);
    Sample& changeLengthStep(double step);

    //Edit
    Sample& copy(Sample& splIn);
    Sample& cut(Sample& splIn);
    Sample& cut();
    Sample& reverse();

    Sample& amplify(double amplitudeL, double amplitudeR);

    Sample& swapChannel();

    //File
    Sample& saveToFile(string filename);
    Sample& loadFromFile(string filename);

    Sample& normalize(double amplitude = 1);
    Sample& normalizeRmsW(double dbNorm = -6, int lntRms = 2048);

    //normalizeRmsW
    Sample& fade(double ampStart, double ampEnd);
    Sample& fadeStereo(double ampStartL, double ampEndL, double ampStartR, double ampEndR);

    Sample& fadeIn();
    Sample& fadeOut();
    Sample& fadeAntiClick(int fadeLength = 100);

    //Generator
    Sample& genSine(double f = 440.0, double phase = 0.5, double ampL = 1, double ampR = 1);

    Sample& genSineFEnv(double f, Sample& fEnv, double fAmp, double phase, double ampL = 1, double ampR = 1);

    Sample& genSineSplFM(Sample& splIn, double f = 440.0, double phase = 0.5, double amplitude = 1, double fmAmp = 0.10);
    Sample& genSaw(double f = 440.0, double phase = 0.5, double ampL = 1.0, double ampR = 1.0);
    Sample& genSuperSaw(double fq, int nSaw, int seed, double detune, double ampMax1Saw);

    Sample& genSquare(double fq = 440.0, double phase = 0.5, double amplitude = 1, double width = 0.5);

    Sample& genWhiteNoise(double amplitude, int seed);
    Sample& genPinkNoise(double amplitude = 1);
    Sample& genBrownNoise(double amplitude = 1, double intensity = 0.1);

    Sample& genPulse(double fq, double phase, double amplitude);

    Sample& genWaveForm(Sample& splWf, double f = 110, double phase = 0, double ampL = 1, double ampR = 1);
    Sample& genWaveFormEnv(Sample& splWf, Sample& splEnv, double f = 110, double fmAmp = 55, double phase = 0, double amplitude = 1);

    Sample& addEnvExp(double vStart, double vEnd, double speed);

    
    
    //analysis
    Sample& extractEnvelope_old(int halfLifeLength);
    Sample& extractEnvelope(int oneToZeroLength);
    Sample& extractEnvelopeNoFilter(int oneToZeroLength);
    
    
    //Effect
    Sample& clip(double maxValue = 1, double minValue = -1);
    Sample& distoWaveShape(Sample& splWS, double ampL, double ampR);

    Sample& strech(Sample & splOut);

    Sample& delay(int length, double dry, double feedback);


    Sample& filterLowPass(double f = 220, double q = 1, int nPass = 1);
    Sample& filterLowPassFEnv(double f, Sample& fEnv, double fAmp, double q, int nPass);

    Sample& filterBandPass(double f = 220, double q = 1, int nPass = 1);
    Sample& filterBandPassFEnv(double f, Sample& fEnv, double fAmp, double q, int nPass);

    Sample& filterHiPass(double f = 220, double q = 1, int nPass = 1);
    Sample& filterHiPassFEnv(double f, Sample& fEnv, double fAmp, double q, int nPass);

    Sample& filterNotch(double f = 220, double q = 1, int nPass = 1);
    Sample& filterNotchEnv(double f, Sample& fEnv, double fAmp, double q, int nPass);

    Sample& filterAllPass(double f, double q, int nPass);
    Sample& filterAllPassEnv(double f, Sample& fEnv, double fAmp, double q, int nPass);


    void maxAmplitude(double &maxL, double &maxR);
    void maxRmsW(double &maxL, double &maxR, int lntRms);
    void avgRms(double &rmsL, double &rmsR);
    
    Sample& mix(Sample& splIn, double ampL = 1, double ampR = 1);
    Sample& modulate(Sample& splIn);

    Sample& mixChannel(double ampLToL,double ampLToR,double ampRToL,double ampRToR);
    
    //util
    static int stepToInt(double step);
    static double intToStep(int lnt);

    static double midiNoteToFq(double midi_note);
    static double fqtoMidiNote(double fq);

    static double dbToLin(double db);
    static double linToDb(double lin);

    ~Sample();

private:
    static int bufferLength;
    static double *bufferL;
    static double *bufferR;

    //Buffer
    void copyToBuffer(Sample splIn, int iIn, int iBuffer, int copyLength);
    void copyFromBuffer(Sample& splOut, int iOut, int iBuffer, int copyLength);
    void setBufferMinLength(int minLength);
    Sample& prepareForSplIn(Sample& splIn, int& jRead, int& iMixEnd);

    void getSampleForHermite(double iRead, int iMin, int iMax, double *dataIn, double& x, double& y0, double& y1, double& y2, double& y3);
    double hermite1(double x, double y0, double y1, double y2, double y3);
    double hermite4(double frac_pos, double xm1, double x0, double x1, double x2);

    double distoWS(double val, double *WS, double rl, double rc);

    Sample& filterRbj(int type, double f = 220, double q = 1, int nPass = 1);


    void debugWavFileHeader(RiffHeader header);
    void loadWavFileHeader(ifstream &infile, RiffHeader &header);
    
    Sample& filterUtlRBJ(int type, double f, double q, int nPass);
    Sample& filterUtlRBJFEnv(int type, double f, Sample& fEnv, double fAmp, double q, int nPass);


};

#endif //#ifndef SAMPLE_H