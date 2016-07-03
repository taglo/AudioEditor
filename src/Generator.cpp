#include "Sample.h"

Sample& Sample::genSine(double fq, double phase, double ampL, double ampR) {
    /*
    Variables:
    ip = phase of the first output sample in radians
    w = freq*pi / samplerate
    b1 = 2.0 * cos(w)

    Init:
    y1=sin(ip-w)
    y2=sin(ip-2*w)

    Loop:
    y0 = b1*y1 - y2
    y2 = y1
    y1 = y0
     */
    //http://www.musicdsp.org/archive.php?classid=1#9

    double y0, y1, y2, b1, w;
    phase *= 2 * M_PI;

    //phase += M_PI;
    w = fq * 2 * M_PI / samplerate;
    b1 = 2 * cos(w);
    y1 = sin(phase - w);
    y2 = sin(phase - 2 * w);

    for (int i = fxIStart; i < fxIEnd; i++) {
        y0 = b1 * y1 - y2;
        y2 = y1;
        y1 = y0;

        Sample::dataL[i] += y0 * ampL;
        Sample::dataR[i] += y0 * ampR;

    }

    return *this;
}

Sample& Sample::genSineFEnv(double f, Sample& fEnv, double fAmp, double phase, double amplitude) {


    int jRead = fEnv.fxIStart;


    phase *= 2 * M_PI;

    double phaseInc = f * 2 * M_PI / samplerate;
    double phaseF = fAmp * 2 * M_PI / samplerate;

    for (int i = fxIStart; i < fxIEnd; i++) {
        dataL[i] += sin(phase) * amplitude;
        phase += phaseInc + phaseF * fEnv.dataL[jRead++];
    }
    return *this;
}

Sample& Sample::genSineSplFM(Sample& splIn, double f, double phase, double amplitude, double fmAmp) {
    int jRead, iMixEnd;
    prepareForSplIn(splIn, jRead, iMixEnd);

    phase *= 2 * M_PI;
    fmAmp *= 2 * M_PI;
    double phaseInc = f * 2 * M_PI / samplerate;

    for (int i = fxIStart; i < iMixEnd; i++) {
        Sample::dataL[i] += sin(phase + splIn.dataL[jRead++] * fmAmp) * amplitude;
        phase += phaseInc;
    }
    return *this;
}

Sample& Sample::genSaw(double fq, double phase, double amplitude) {

    double phaseInc = fq * 2 / samplerate;
    phase *= 2;
    //phase -= 1;

    for (int i = fxIStart; i < fxIEnd; i++) {
        Sample::dataL[i] += phase * amplitude;
        phase += phaseInc;
        if (phase > 1) {
            phase -= 2;
        }
    }
    return *this;
}

Sample& Sample::genPulse(double fq, double phase, double amplitude) {

    double phaseInc = fq * 2 / samplerate;

    phase *= 2;
    //phase -= 1;

    for (int i = fxIStart; i < fxIEnd; i++) {

        phase += phaseInc;
        if (phase > 1) {
            Sample::dataL[i] += amplitude;
            phase -= 2;
        }
    }
    return *this;
}

Sample& Sample::genSquare(double fq, double phase, double amplitude, double width) {

    double phaseInc = fq / samplerate;
    //phase = (phase-0.5)*2;

    double mAmplitude = -amplitude;

    //double mWidth = (width -0.5)*2;

    for (int i = fxIStart; i < fxIEnd; i++) {

        if (phase < width) {
            Sample::dataL[i] += amplitude;
        } else {
            Sample::dataL[i] += mAmplitude;
        }
        phase += phaseInc;
        if (phase > 1) {
            phase -= 1;
        }
    }
    return *this;
}

//http://www.firstpr.com.au/dsp/pink-noise/

Sample& Sample::genWhiteNoise(double amplitude,int seed) {

    double lower_bound = -amplitude;
    double upper_bound = amplitude;

    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::mt19937_64 re(seed);

    for (int i = fxIStart; i < fxIEnd; i++) {
        Sample::dataL[i] += unif(re);
    }
    return *this;
}

Sample& Sample::genBrownNoise(double amplitude, double intensity) {

    double lower_bound = -intensity;
    double upper_bound = intensity;
    double bn = 0, cbn;

    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
    std::mt19937_64 re((std::time(0)));

    for (int i = fxIStart; i < fxIEnd; i++) {
        cbn = unif(re);

        bn += cbn;
        if (bn > amplitude || (bn < -amplitude)) {
            bn -= cbn;
        }
        Sample::dataL[i] += bn;
    }
    return *this;
}

int inline CTZ(int num) {
    int i = 0;
    while (((num >> i)&1) == 0 && i<sizeof (int)) i++;
    return i;
}

//Sample& fEnv, double fmAmp,

Sample& Sample::genWaveformEnv(Sample& splWf, Sample& splEnv, double f, double fmAmp, double phase, double amplitude) {

    double y0 = 0, y1 = 0, y2 = 0, y3 = 0;

    //double pitch = ((double) fxLength()) / ((double) splOut.fxLength());

    double jRead = (double) splWf.fxIStart;
    double period = (double) splWf.fxLength();

    double pitch = period / (((double) samplerate) / f);
    double pitchAmp = period / (((double) samplerate) / fmAmp);

    jRead += period*phase;
    int iRead = 0, iEnv = splEnv.fxIStart;

    for (int i = fxIStart; i < fxIEnd; i++) {

        y3 = y2;
        y2 = y1;
        y1 = y0;

        iRead = (int) jRead;
        y0 = splWf.dataL[iRead];

        dataL[i] += hermite1(jRead - (double) iRead, y0, y1, y2, y3) * amplitude;

        jRead += pitch + pitchAmp * splEnv.dataL[iEnv];

        if (jRead > splWf.fxIEnd) {
            jRead -= period;
        }
        iEnv++;
    }

    return *this;
}

Sample& Sample::genWaveform(Sample& splWf, double f, double phase, double amplitude) {

    double y0 = 0, y1 = 0, y2 = 0, y3 = 0;

    //double pitch = ((double) fxLength()) / ((double) splOut.fxLength());

    double jRead = (double) splWf.fxIStart;
    double period = (double) splWf.fxLength();

    double pitch = period / (((double) samplerate) / f);

    jRead += period*phase;
    int iRead = 0;

    for (int i = fxIStart; i < fxIEnd; i++) {

        y3 = y2;
        y2 = y1;
        y1 = y0;

        iRead = (int) jRead;
        y0 = splWf.dataL[iRead];

        dataL[i] += hermite1(jRead - (double) iRead, y0, y1, y2, y3) * amplitude;

        jRead += pitch;

        if (jRead > splWf.fxIEnd) {
            jRead -= period;
        }

    }

    return *this;
}

Sample& Sample::genPinkNoise(double amplitude) {

    int count = 1;

    int nOperator = 8;
    int nOperator1 = nOperator - 1;

    double pinkStore[nOperator];
    double pink = 0;
    int k;

    std::uniform_real_distribution<double> unif(-amplitude, amplitude);
    std::mt19937_64 re((std::time(0)));

    for (int i = 0; i < nOperator; i++) {
        pinkStore[i] = 0; // unif(re);
        //pink += pinkStore[i];

    }
    for (int i = fxIStart; i < fxIEnd; i++) {

        k = CTZ(count);
        k = k&nOperator1;


        pink -= pinkStore[k];

        pinkStore[k] = unif(re);
        pink += pinkStore[k];

        Sample::dataL[i] += (pink + unif(re)) / 16;

        /*
        cbn = unif(re);

        bn += cbn;
        if (bn > amplitude || (bn < -amplitude)) {
            bn -= cbn ;
        }
        Sample::data[i] += bn;
         */

        count++;
    }
    return *this;
}


