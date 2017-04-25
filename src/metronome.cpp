//
//  metronome.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 25/11/2016.
//
//

#include "metronome.hpp"
#include "sequencer.hpp"

Metronome *Metronome::theMetronome = nullptr;

Metronome &Metronome::get(){
    if(theMetronome == nullptr){
        theMetronome = new Metronome();
    }
    return *theMetronome;
}


// default constructor
Metronome::Metronome(){
    
    /////////////
    // INIT   //
    ////////////
    
    sampleCount = 0;
    pulse = 0;
    eigthNote = 0;
    sixteenthNote = 0;
    
    // https://forum.openframeworks.cc/t/accurate-sequencing/3404/3 idea for formula taken comes from here
    
    lengthOfOneBeatInSamples = (float)44100*60.f/(160);
}

// destructor
Metronome::~Metronome(){}

//// timing for quarter notes, this is your base pulse
ull Metronome::getNextPulse(){
    pulse = &lengthOfOneBeatInSamples;
    return *pulse;
}

// timing for quarter notes, this is your base pulse
//ull Metronome::getNextPulse(){
//    pulse = &lengthOfOneBeatInSamples;
//    return 8;
//}

// timing for eigthnotes, they are twice as fast quarter notes
ull Metronome::getNextEigthNote(){
    eigthNote = &lengthOfOneBeatInSamples;
    return *eigthNote/2;
}

//ull Metronome::getNextEigthNote(){
//    eigthNote = &lengthOfOneBeatInSamples;
//    return 4;
//}

// timing for sixteenthNotes, twice as fast as eigth notes
ull Metronome::getNextSixteenthNote(){
    sixteenthNote = &lengthOfOneBeatInSamples;
    return *sixteenthNote/4;
}

//ull Metronome::getNextSixteenthNote(){
//    sixteenthNote = &lengthOfOneBeatInSamples;
//    return 2;
//}

void Metronome::setTempo(int _bpm){
    // set new tempo
    lengthOfOneBeatInSamples = (float)44100*60.f/(_bpm);
    
    // update sequencers
    for(auto & sequencer: sequencers){
        sequencer->updateTempo();
    }
    
}

////////////////////////////////////////////////////
//to have an accurate metronome we count         //
//how many samples that've sent to the soundcard//
/////////////////////////////////////////////////


void Metronome::getNextSample(){
    sampleCount++;
}

void Metronome::registerSequencerListeners(vector<sharedptr> _sequencers){
    sequencers = _sequencers;
}






