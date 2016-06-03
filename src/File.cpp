//#pragma once
#include <fstream>
#include "Sample.h"

struct RiffHeader {
    char RIFF[4] = {'R', 'I', 'F', 'F'}; // RIFF Header  
    int ChunkSize; // RIFF Chunk Size
    char WAVE[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
    char fmt[4] = {'f', 'm', 't', ' '}; // FMT header  
    int Subchunk1Size; // Size of the fmt chunk 
    short int AudioFormat; // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    short int NumOfChan; // Number of channels 1=Mono 2=Stereo  
    int SamplesPerSec; // Sampling Frequency in Hz 
    int bytesPerSec; // bytes per second */
    short int blockAlign; // 2=16-bit mono, 4=16-bit stereo
    short int bitsPerSample; // Number of bits per sample
    char Subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
    int Subchunk2Size; // Sampled data length
};

Sample& Sample::saveToFile(std::string filename) {

    float *dataF;

    RiffHeader header;

    header.ChunkSize = sizeof (RiffHeader) + fxLength()*4; // RIFF Chunk Size

    header.Subchunk1Size = 16;
    header.AudioFormat = 3;
    header.NumOfChan = 1;
    header.SamplesPerSec = Sample::samplerate;
    header.bytesPerSec = 4 * Sample::samplerate;
    header.blockAlign = 4;
    header.bitsPerSample = 32;

    header.Subchunk2Size = fxLength()*4;

    dataF = new float[fxLength()];

    for (int i = fxIStart; i < fxIEnd; i++) {
        dataF[i] = (float) data[i];
    }

    string fOut = filePath + filename;

    std::ofstream outfile(fOut, ofstream::binary);

    outfile.write(reinterpret_cast<char*> (&header), sizeof (RiffHeader));

    outfile.write((char*) dataF, fxLength() * sizeof (float));

    outfile.close();

    delete dataF;

    return *this;

}

Sample& Sample::loadFromFile(std::string filename) {

    float dataF;

    string fIn = filePath + filename;

    ifstream infile(fIn,ios::binary	);

    RiffHeader header;

    infile.read((char*) &header, sizeof (RiffHeader));

    fxIStart = 0;
    fxIEnd = header.Subchunk2Size / 4;

    changeLength(fxIEnd);

   // dataF = new float[fxIEnd];

    // infile.read((char*) &dataF,   fxIEnd * sizeof (float));

    for (int i = fxIStart; i < fxIEnd; i++) {
        infile.read((char*) &dataF, sizeof (float));

        data[i] = (double) dataF;
        
    }


    infile.close();

    //delete[] dataF;

    return *this;

}
