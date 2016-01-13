#pragma once
#include <fstream>
#include "Sample.h"


Sample& Sample::saveToFile(const char* filename){

	float *dataF;

	dataF = new float[length];
	for (int i = 0; i < length; i++)
	{
		dataF[i] = (float) data[i];
	}

	std::ofstream outfile(filename, std::ofstream::binary);
	outfile.write((char*)dataF, length*sizeof(float));
	outfile.close();

	delete dataF;

	return *this;

}