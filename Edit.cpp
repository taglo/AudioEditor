//#pragma once
#include "Sample.h"


Sample& Sample::copy(Sample& splOut){

	splOut.length = fxLength();

	splOut.data = new double[splOut.length];

	int j = 0;
	for (int i = fxIStart; i < fxIEnd; i++)
	{
		splOut.data[j++] = data[i];
	}
	splOut.fxRangeReset();

	return *this;
}

Sample& Sample::cut(){

	//vérif longueur buffer avant de faire les 2

	int newLength = fxIStart + length - fxIEnd;
	setBufferMinLength(newLength);

	copyToBuffer(data, 0, 0, fxIStart);
	copyToBuffer(data, fxIEnd, fxIStart, length - fxIEnd);

	length = newLength;
	data = new double[length];

	copyFromBuffer(data, 0, 0, length);

	fxRangeReset();

	return *this;
}
Sample& Sample::cut(Sample& splOut){

	copy(splOut);
	cut();

	return *this;
}