#pragma once

class Sample {
public:

    double *data;
    int length;
    int fxIStart;
    int fxIEnd;

    static int samplerate;
    static double tempo;


    Sample(int length = 0);
    Sample(const Sample& other);
    Sample& operator=(const Sample& other);

    //void init(int length);

    Sample& fxRange(int iStart, int iEnd); //todo : fxRangeInStep, class SoundEdit

    Sample& fxRangeReset();
    Sample& fxRangeCheck();
    int fxLength();

    Sample& setConstant(double cst);
    Sample& changeLength(int newLength);

    //Edit
    Sample& copy(Sample& splOut);
    Sample& cut(Sample& splOut);
    Sample& cut();

    Sample& amplify(double amplitude);

    //File
    Sample& saveToFile(const char* filename);


    Sample& normalize(double amplitude = 1);
    Sample& fade(double ampStart, double ampEnd);
    Sample& fadeIn();
    Sample& fadeOut();
    Sample& fadeAntiClick(int fadeLength = 100);

    //Generator
    Sample& genSine(double f = 440.0, double phase = 0.5, double amplitude = 1);
    Sample& genSineSplFM(Sample& splIn, double f = 440.0, double phase = 0.5, double amplitude = 1, double fmAmp = 0.10);
    Sample& genSaw(double f = 440.0, double phase = 0.5, double amplitude = 1);
    Sample& genSquare(double fq = 440.0, double phase = 0.5, double amplitude = 1, double width=0.5);

    Sample& genWhiteNoise(double amplitude = 1);
    Sample& genPinkNoise(double amplitude = 1);
    Sample& genBrownNoise(double amplitude = 1, double intensity = 0.1);

    //Effect
    Sample& clip(double maxValue = 1, double minValue = -1);

    double maxAmplitude();

    Sample& mix(Sample& splIn, double amplitude = 1);

    ~Sample();

private:
    static int bufferLength;
    static double *buffer;
    //Buffer
    void copyToBuffer(double *dataIn, int iIn, int iBuffer, int copyLength);
    void copyFromBuffer(double *dataOut, int iOut, int iBuffer, int copyLength);
    void setBufferMinLength(int minLength);
    Sample& prepareForSplIn(Sample& splIn, int& jRead, int& iMixEnd);


};
