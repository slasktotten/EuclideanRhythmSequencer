//
//  metronome.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 25/11/2016.
//
//

#include "metronome.hpp"
#include "sequencer.hpp"

Metronome::Metronome(int _sampleRate): sampleRate(_sampleRate){
    
    //need to change 120 to bpm variable
    //https://forum.openframeworks.cc/t/accurate-sequencing/3404/3 idea for formula taken comes from here
    lengthOfOneBeatInSamples = (float)sampleRate*60.f/(60);
    
    /////////////
    // INIT   //
    ////////////
    
    sampleCount = 0;
    pulse = 0;
    eigthNote = 0;
    sixteenthNote = 0;
    
}

Metronome::~Metronome(){

}

//timing for quarter notes, this is your base pulse
ull Metronome::getNextPulse(){
    pulse = &lengthOfOneBeatInSamples;
    return *pulse;
}

//timing for eigthnotes, they are twice as fast quarter notes
ull Metronome::getNextEigthNote(){
    eigthNote = &lengthOfOneBeatInSamples;
    return *eigthNote/2;
}

//timing for sixteenthNotes, twice as fast as eigth notes
ull Metronome::getNextSixteenthNote(){
    sixteenthNote = &lengthOfOneBeatInSamples;
    return *sixteenthNote/4;
}

void Metronome::setTempo(int _bpm){
    
    // set new tempo
    lengthOfOneBeatInSamples = (float)sampleRate*60.f/(_bpm);
    
    // update sequencers
    for(auto & sequencer: sequencers){
        sequencer->updateTempo();
    }
    
}

////////////////////////////////////////////////////
//to have an accurate metronome we count         //
//how many samples that've sent to the soundcard//
/////////////////////////////////////////////////


//turns into an integer function

/*
 int Metronome::sampleCount(){
 return sampleCount+1;
 }
 */

void Metronome::getNextSample(){
    sampleCount++;
}

void Metronome::registerSequencerListeners(vector<Sequencer*> _sequencers){
    sequencers = _sequencers;
    for(auto sequencer : sequencers){
        cout << sequencer << endl;
    }
}

void Metronome::getSequencerStatus(){
    for(auto sequencer : sequencers){
        cout << sequencer->subdivision << endl;
    }
}
