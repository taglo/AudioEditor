
#define _USE_MATH_DEFINES
#include <cmath>
#include "Sample.h"


Sample& Sample::genSine(double fq, double phase, double amplitude)
{
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

	double y0, y1, y2, b1,w;
	phase *= 2 * M_PI;

	//phase += M_PI;
	w = fq * 2 * M_PI / samplerate;
	b1 = 2 * cos(w);
	y1 = sin(phase - w);
	y2 = sin(phase - 2*w);

	for (int i = fxIStart; i<fxIEnd; i++)
	{
		y0 = b1*y1 - y2;
		y2 = y1;
		y1 = y0;

		Sample::data[i] += y0 * amplitude;

	}

	return *this;
}

Sample& Sample::genSineSplFM(Sample& splIn, double f, double phase, double amplitude, double fmAmp)
{
	int jRead, iMixEnd;
	prepareForSplIn(splIn, jRead, iMixEnd);

	phase *= 2 * M_PI;
	fmAmp *= 2 * M_PI;
	double phaseInc = f * 2 * M_PI / samplerate;

	for (int i = fxIStart; i<iMixEnd; i++)
	{
		Sample::data[i] += sin(phase+splIn.data[jRead++]*fmAmp) * amplitude;
		phase += phaseInc;
	}
	return *this;
}


Sample& Sample::genSaw(double fq, double phase, double amplitude)
{

	double phaseInc = fq * 2 / samplerate;
	phase *= 2;
	//phase -= 1;

	for (int i = fxIStart; i<fxIEnd; i++)
	{
		Sample::data[i] += phase * amplitude;
		phase += phaseInc;
		if (phase>1)
		{
			phase -= 2;
		}
	}
	return *this;
}