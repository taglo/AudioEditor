/* 
 * File:   RiffHeader.h
 * Author: tglo
 *
 * Created on 14 août 2016, 10:17
 */
#pragma once
#ifndef RIFFHEADER_H
#define	RIFFHEADER_H





/*
 [Bloc de déclaration d'un fichier au format WAVE]
   FileTypeBlocID  (4 octets) : Constante «RIFF»  (0x52,0x49,0x46,0x46)
   FileSize        (4 octets) : Taille du fichier moins 8 octets
   FileFormatID    (4 octets) : Format = «WAVE»  (0x57,0x41,0x56,0x45)

[Bloc décrivant le format audio]
   FormatBlocID    (4 octets) : Identifiant «fmt »  (0x66,0x6D, 0x74,0x20)
   BlocSize        (4 octets) : Nombre d'octets du bloc - 16  (0x10)

   AudioFormat     (2 octets) : Format du stockage dans le fichier (1: PCM, ...)
   NbrCanaux       (2 octets) : Nombre de canaux (de 1 à 6, cf. ci-dessous)
   Frequence       (4 octets) : Fréquence d'échantillonnage (en hertz) [Valeurs standardisées : 11025, 22050, 44100 et éventuellement 48000 et 96000]
   BytePerSec      (4 octets) : Nombre d'octets à lire par seconde (i.e., Frequence * BytePerBloc).
   BytePerBloc     (2 octets) : Nombre d'octets par bloc d'échantillonnage (i.e., tous canaux confondus : NbrCanaux * BitsPerSample/8).
   BitsPerSample   (2 octets) : Nombre de bits utilisés pour le codage de chaque échantillon (8, 16, 24)

[Bloc des données]
   DataBlocID      (4 octets) : Constante «data»  (0x64,0x61,0x74,0x61)
   DataSize        (4 octets) : Nombre d'octets des données (i.e. "Data[]", i.e. taille_du_fichier - taille_de_l'entête  (qui fait 44 octets normalement).
   DATAS[] : [Octets du Sample 1 du Canal 1] [Octets du Sample 1 du Canal 2] [Octets du Sample 2 du Canal 1] [Octets du Sample 2 du Canal 2]

 * Les Canaux :
      1 pour mono,
      2 pour stéréo
      3 pour gauche, droit et centre
      4 pour face gauche, face droit, arrière gauche, arrière droit
      5 pour gauche, centre, droit, surround (ambiant)
      6 pour centre gauche, gauche, centre, centre droit, droit, surround (ambiant)

NOTES IMPORTANTES :  Les octets des mots sont stockés sous la forme  (i.e., en "little endian")
[87654321][16..9][24..17] [8..1][16..9][24..17] [...
 */
struct RiffHeader {
    char FileTypeBlocID[4] = {'R', 'I', 'F', 'F'}; // RIFF Header  
    //FileTypeBlocID  (4 octets) : Constante «RIFF»  (0x52,0x49,0x46,0x46)


    int FileSize; // RIFF Chunk Size
    //FileSize        (4 octets) : Taille du fichier moins 8 octets

    char FileFormatID[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
    //FileFormatID    (4 octets) : Format = «WAVE»  (0x57,0x41,0x56,0x45)

    char FormatBlocID[4] = {'f', 'm', 't', ' '}; // FMT header  
    //FormatBlocID    (4 octets) : Identifiant «fmt »  (0x66,0x6D, 0x74,0x20)

    /**BlocSize        (4 octets) : Nombre d'octets du bloc - 16  (0x10)*/
    int BlocSize; // Size of the fmt chunk 


    short int AudioFormat; // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    //AudioFormat     (2 octets) : Format du stockage dans le fichier (1: PCM, ...)

    short int NumOfChan; // Number of channels 1=Mono 2=Stereo  
    //NbrCanaux       (2 octets) : Nombre de canaux (de 1 à 6, cf. ci-dessous)

    int Frequence; // Sampling Frequency in Hz 
    //Frequence       (4 octets) : Fréquence d'échantillonnage (en hertz) [Valeurs standardisées : 11025, 22050, 44100 et éventuellement 48000 et 96000]

    int bytesPerSec; // bytes per second */
    //BytePerSec      (4 octets) : Nombre d'octets à lire par seconde (i.e., Frequence * BytePerBloc).

    short int BytePerBloc; // 2=16-bit mono, 4=16-bit stereo
    //BytePerBloc     (2 octets) : Nombre d'octets par bloc d'échantillonnage (i.e., tous canaux confondus : NbrCanaux * BitsPerSample/8).

    short int BitsPerSample; // Number of bits per sample
    //BitsPerSample   (2 octets) : Nombre de bits utilisés pour le codage de chaque échantillon (8, 16, 24)

    /** DataBlocID      (4 octets) : Constante «data»  (0x64,0x61,0x74,0x61)
     */
    char DataBlocID[4] = {'d', 'a', 't', 'a'}; // "data"  string

    /** DataSize        (4 octets) : Nombre d'octets des données (i.e. "Data[]", i.e. taille_du_fichier - taille_de_l'entête  (qui fait 44 octets normalement). */
    int DataSize; // Sampled data length
};

#endif	/* RIFFHEADER_H */