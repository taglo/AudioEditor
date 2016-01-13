#pragma once
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
    char Subchunk2ID[4] = {'d', 'a', 't', 'a'};
    ; // "data"  string
    int Subchunk2Size; // Sampled data length
};

Sample& Sample::saveToFile(const char* filename) {

    float *dataF;



    RiffHeader header;
    // header.RIFF = 'RIFF'; // RIFF Header  
    header.ChunkSize = sizeof (RiffHeader) + fxLength()*4; // RIFF Chunk Size
    // header.WAVE = 'WAVE'; // WAVE Header
    // header.fmt = 'fmt '; // FMT header  
    header.Subchunk1Size = 16; // Size of the fmt chun
    header.AudioFormat = 3; // Audio format 1=PCM,6
    header.NumOfChan = 1; // Number of channels 1
    header.SamplesPerSec = Sample::samplerate; // Sampling Frequency i
    header.bytesPerSec = 4 * Sample::samplerate; // bytes per second */
    header.blockAlign = 4; // 2=16-bit mono, 4=16-
    header.bitsPerSample = 32; // Number of bits per s
    //header.Subchunk2ID ='data'; // "data"  string
    header.Subchunk2Size = fxLength()*4; // Sampled data length

    dataF = new float[fxLength()];

    for (int i = fxIStart; i < fxIEnd; i++) {
        dataF[i] = (float) data[i];
    }

    std::ofstream outfile(filename, std::ofstream::binary);

    outfile.write(reinterpret_cast<char*> (&header), sizeof (RiffHeader));

    outfile.write((char*) dataF, fxLength() * sizeof (float));

    outfile.close();

    delete dataF;

    return *this;

}

