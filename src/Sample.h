#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <random>
#include <ctime>
#include <string>
#include "helper/rbjFilter.h"
#include "helper/Delay.h"
#include "helper/Rng.h"

using namespace std;

class Sample {
public:

    double *data;
    int length;
    int fxIStart;
    int fxIEnd;

    static int samplerate;
    static double tempo;
    static string filePath;

    Sample();
    Sample(int length);
    Sample(double nStep);
    Sample(const Sample& other);
    Sample& operator=(const Sample& other);

    //void init(int length);

    Sample& fxRange(int iStart, int iEnd);
    Sample& fxRangeStep(double stepStart = 0, double stepEnd = 0);



    Sample& fxRangeReset();
    Sample& fxRangeCheck();

    int fxLength();

    Sample& setConstant(double cst = 0);
    Sample& setConstantDynamic(double cstStart = 1, double cstEnd = 0);
    Sample& addConstant(double cst = 0);
    Sample& changeLength(int newLength);
    Sample& changeLengthStep(double step);

    //Edit
    Sample& copy(Sample& splOut);
    Sample& cut(Sample& splOut);
    Sample& cut();
    Sample& reverse();

    Sample& amplify(double amplitude);

    //File
    Sample& saveToFile(string filename);
    Sample& loadFromFile(string filename);

    Sample& normalize(double amplitude = 1);
    Sample& fade(double ampStart, double ampEnd);
    Sample& fadeIn();
    Sample& fadeOut();
    Sample& fadeAntiClick(int fadeLength = 100);

    //Generator
    Sample& genSine(double f = 440.0, double phase = 0.5, double amplitude = 1);
    Sample& genSineFEnv(double f, Sample& fEnv, double fAmp, double phase, double amplitude);
    Sample& genSineSplFM(Sample& splIn, double f = 440.0, double phase = 0.5, double amplitude = 1, double fmAmp = 0.10);
    Sample& genSaw(double f = 440.0, double phase = 0.5, double amplitude = 1);
    Sample& genSquare(double fq = 440.0, double phase = 0.5, double amplitude = 1, double width = 0.5);

    Sample& genWhiteNoise(double amplitude, int seed);
    Sample& genPinkNoise(double amplitude = 1);
    Sample& genBrownNoise(double amplitude = 1, double intensity = 0.1);

    Sample& genPulse(double fq, double phase, double amplitude);

    Sample& genWaveform(Sample& splWf, double f = 110, double phase = 0, double amplitude = 1);
    Sample& genWaveformEnv(Sample& splWf, Sample& splEnv, double f = 110, double fmAmp = 55, double phase = 0, double amplitude = 1);

    //Effect
    Sample& clip(double maxValue = 1, double minValue = -1);

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

    double maxAmplitude();

    Sample & mix(Sample& splIn, double amplitude = 1);



    ~Sample();

private:
    static int bufferLength;
    static double *buffer;
    //Buffer
    void copyToBuffer(double *dataIn, int iIn, int iBuffer, int copyLength);
    void copyFromBuffer(double *dataOut, int iOut, int iBuffer, int copyLength);
    void setBufferMinLength(int minLength);
    Sample& prepareForSplIn(Sample& splIn, int& jRead, int& iMixEnd);

    void getSampleForHermite(double iRead, int iMin, int iMax, double *dataIn, double& x, double& y0, double& y1, double& y2, double& y3);
    double hermite1(double x, double y0, double y1, double y2, double y3);


    Sample& filterRbj(int type, double f = 220, double q = 1, int nPass = 1);
    //util
    int stepToInt(double step);


    Sample& filterUtlRBJ(int type, double f, double q, int nPass);
    Sample& filterUtlRBJFEnv(int type, double f, Sample& fEnv, double fAmp, double q, int nPass);


};
