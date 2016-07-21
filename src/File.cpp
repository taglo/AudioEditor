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
    header.NumOfChan = 2;
    header.SamplesPerSec = Sample::samplerate;
    header.bytesPerSec = header.NumOfChan * 4 * Sample::samplerate;
    header.blockAlign = 4;
    header.bitsPerSample = 32;

    header.Subchunk2Size = header.NumOfChan * fxLength()*4;

    //vérifie extension
    if (!(filename.substr(filename.find_last_of(".") + 1) == "wav")) {
        filename += ".wav";
    }

    dataF = new float[header.NumOfChan * fxLength()];

    int j = 0;
    for (int i = fxIStart; i < fxIEnd; i++) {
        dataF[j++] = (float) dataL[i];
        dataF[j++] = (float) dataR[i];
    }

    string fOut = filePath + filename;

    std::ofstream outfile(fOut, ofstream::binary);

    outfile.write(reinterpret_cast<char*> (&header), sizeof (RiffHeader));

    outfile.write((char*) dataF, 2 * fxLength() * sizeof (float));

    outfile.close();

    delete dataF;

    return *this;

}

Sample& Sample::loadFromFile(std::string filename) {

    float dataF;

    string fIn = filePath + filename;

    ifstream infile(fIn, ios::binary);

    RiffHeader header;

    infile.read((char*) &header, sizeof (RiffHeader));

    fxIStart = 0;
    fxIEnd = header.Subchunk2Size / 8;


    init(fxIEnd);

    // dataF = new float[fxIEnd];

    // infile.read((char*) &dataF,   fxIEnd * sizeof (float));

    for (int i = fxIStart; i < fxIEnd; i++) {
        infile.read((char*) &dataF, sizeof (float));
        dataL[i] = (double) dataF;

        infile.read((char*) &dataF, sizeof (float));
        dataR[i] = (double) dataF;

    }


    infile.close();

    //delete[] dataF;

    return *this;

}
