/* 
 * File:   Sound.h
 * Author: tglo
 *
 * Created on 5 septembre 2016, 18:08
 * 
 * 
 */



#ifndef SOUND_H
#define	SOUND_H

#include "../Sample.h"
#include <string>

class Sound : public Sample 
{
    public:
        Sound();  
        
        string info;
        bool estRythmique;
        bool estTon;
        std::vector<int> midi_note;
        
    private:
};

#endif	/* SOUND_H */

