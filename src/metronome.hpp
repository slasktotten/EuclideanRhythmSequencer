//
//  metronome.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 25/11/2016.
//
//

#ifndef metronome_hpp
#define metronome_hpp
typedef unsigned long long ull;

#include <stdio.h>
#include "ofMain.h"


class Metronome {
public:
    Metronome(int _sampleRate);
    int sampleRate;
    ull lengthOfOneBeatInSamples;
    int sampleCount;
    ull getNextPulse();
    ull getNextEigthNote();
    ull getNextSixteenthNote();
    ull setSubdivision(char selection);
    ull *pulse, *eigthNote, *sixteenthNote;
    ull qrtNote, eiNote, sixNote;
    void getNextSample();
    void setTempo(int _bpm);
    void updateSubdivisions();
};


#endif /* metronome_hpp */
