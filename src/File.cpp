//#pragma once
#include <fstream>
#include "Sample.h"

using namespace std;

Sample& Sample::saveToFile(std::string filename) {

    float *dataF;

    RiffHeader header;

    header.FileSize = sizeof (RiffHeader) + fxLength()*4 - 8;

    header.BlocSize = 16;
    header.AudioFormat = 3;
    header.NumOfChan = 2;
    header.Frequence = Sample::samplerate;
    header.bytesPerSec = header.NumOfChan * 4 * Sample::samplerate;
    header.BytePerBloc = 8;
    header.BitsPerSample = 32;

    header.DataSize = header.NumOfChan * fxLength()*4;

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

void Sample::debugWavFileHeader(RiffHeader header) {
    cout << "debugWavFileHeader" << endl;
    cout << "FileTypeBlocID : " << header.FileTypeBlocID << endl;
    cout << "FileSize : " << header.FileSize << endl;
    cout << "FileFormatID : " << header.FileFormatID << endl;
    cout << "FormatBlocID : " << header.FormatBlocID << endl;
    cout << "BlocSize : " << header.BlocSize << endl;
    cout << "AudioFormat : " << header.AudioFormat << endl;
    cout << "NumOfChan : " << header.NumOfChan << endl;
    cout << "Frequence : " << header.Frequence << endl;
    cout << "bytesPerSec : " << header.bytesPerSec << endl;
    cout << "BytePerBloc : " << header.BytePerBloc << endl;
    cout << "BitsPerSample : " << header.BitsPerSample << endl;
    cout << "DataBlocID : " << header.DataBlocID << endl;
    cout << "DataSize : " << header.DataSize << endl;
}

void Sample::loadWavFileHeader(ifstream &infile, RiffHeader &header){
    infile.read((char*) &header.FileTypeBlocID, sizeof (header.FileTypeBlocID));
    infile.read((char*) &header.FileSize, sizeof (header.FileSize));
    infile.read((char*) &header.FileFormatID, sizeof (header.FileFormatID));
    infile.read((char*) &header.FormatBlocID, sizeof (header.FormatBlocID));
    infile.read((char*) &header.BlocSize, sizeof (header.BlocSize));
    infile.read((char*) &header.AudioFormat, sizeof (header.AudioFormat));
    infile.read((char*) &header.NumOfChan, sizeof (header.NumOfChan));
    infile.read((char*) &header.Frequence, sizeof (header.Frequence));
    infile.read((char*) &header.bytesPerSec, sizeof (header.bytesPerSec));
    infile.read((char*) &header.BytePerBloc, sizeof (header.BytePerBloc));
    infile.read((char*) &header.BitsPerSample, sizeof (header.BitsPerSample));
    
    
    if(header.BlocSize >16 ){
        char tmp[1];
        for(int i=16;i<header.BlocSize;i++) {
            infile.read((char*) &tmp, sizeof (tmp));        
        }
    }
    
    infile.read((char*) &header.DataBlocID, sizeof (header.DataBlocID));
    infile.read((char*) &header.DataSize, sizeof (header.DataSize));
    
}
Sample& Sample::loadFromFile(std::string filename) {

    float dataF;

    //vérifie extension
    if (!(filename.substr(filename.find_last_of(".") + 1) == "wav")) {
        filename += ".wav";
    }
    
    string fIn = filePath + filename;

    ifstream infile(fIn, ios::binary);

    RiffHeader header;

    

    Sample::loadWavFileHeader(infile,header);
    
    //Sample::debugWavFileHeader(header);

    fxIStart = 0;

    //marche pas avec des fichiers qui n'ont pas exactement la même longueur de head, ex : adobe audition
    fxIEnd = header.DataSize / 8;


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
