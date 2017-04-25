//
//  sequencer.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 04/11/2016.
//
//

#include "sequencer.hpp"

Sequencer::Sequencer(){
    synchronize_subdivisions = 1;
    stepSize         = 16;
    steps.resize(stepSize);
    
    /////////////
    // INIT   //
    ////////////
    
    for (auto step : steps) step = 0;
    trigger          = 0;
    tick             = 0;
    nBeats           = 0;
    stepSize         = 0;
    play             = false;


}

//--------------------------------------------------------------

Sequencer::~Sequencer(){}

//--------------------------------------------------------------

void Sequencer::setup(Controller* _controller){
    controller = _controller;
}

//--------------------------------------------------------------

//Pattern is where we set the size of the sequence, how many beats it's going to have
void Sequencer::pattern(int _beats, int _stepSize){
    stepSize = _stepSize;
    nBeats   = _beats;
    
    //we cant have more hits than the sequence is long
    if (nBeats >= stepSize) nBeats = stepSize;
    
    steps.clear();
    steps.resize(stepSize);
    
    //set our stepsequence to that of the algorithm
    steps = bjorklund<bool>(nBeats, stepSize);
}

//--------------------------------------------------------------

void Sequencer::pattern(int _beats, int _stepSize, int _offset){
    stepSize = _stepSize;
    nBeats   = _beats;
    offset   = _offset; //offset rhythm, i.e. choose at which hit you want to the pattern to start
    if (nBeats >= stepSize) nBeats = stepSize; //we cant have more hits than steps!
    steps.clear();
    steps.resize(stepSize);
    steps = bjorklund<bool>(nBeats, stepSize);
    //because we represent the pattern as a vector of booleans we can just rotate the elements of that vector to get another permutation of the rhythm
    //we do this "backwards" so that element 0 becomes element 1, instead of the last element in the vector
    rotate(steps.begin(), steps.end() - (offset % steps.size()), steps.end());
}

//--------------------------------------------------------------

//The Metronome object stores everything time and timing related
void Sequencer::setSubdivision(string _theCurrentSubdivision){
    theCurrentSubdivision = _theCurrentSubdivision;
    if(theCurrentSubdivision == "4thNote")  subdivision = Metronome::get().getNextPulse();
    if(theCurrentSubdivision == "8thNote")  subdivision = Metronome::get().getNextEigthNote();
    if(theCurrentSubdivision == "16thNote") subdivision = Metronome::get().getNextSixteenthNote();
}

//--------------------------------------------------------------

void Sequencer::playSequence(){
    //first time through we have to synchronize the different subdivisions, otherwise eigthnotes would start earlier than pulse, sixteenthnote notes before eigthNotes.
    
    if(synchronize_subdivisions==1){
        if(Metronome::get().sampleCount % Metronome::get().getNextPulse() == 0) //if we are ready for the next beat
        {
           
            if(steps[tick] == 1){ //if the current tick (beat) is 1, play the sample, else dont
                play = true;
                trigger = 1;
                synchronize_subdivisions=0;
            }
            
            play = false;
            tick = ++tick % stepSize; //increment tick, modulus stepsize to go back to beat 1 after end
        }
    }
    
    
    if(synchronize_subdivisions == 0){
        if(Metronome::get().sampleCount % subdivision == 0)
        {
            
            if(steps[tick] == 1){
                play = true;
                trigger = 1;
            }
            
            play = false;
            tick = ++tick % stepSize;
        }
    }
}



//--------------------------------------------------------------

void Sequencer::updateTempo(){
    setSubdivision(theCurrentSubdivision);
}


void Sequencer::run(){
    pattern(controller->nBeats, controller->stepSize, controller->offset);
    switch(controller->subdivision)
    {
        case 1 :
            setSubdivision("4thNote");
            break;
        case 2 :
            setSubdivision("8thNote");
            break;
        case 3 :
            setSubdivision("16thNote");
            break;
            deafult :
            setSubdivision("16thNote");
    }
    
}

//--------------------------------------------------------------

void Sequencer::getStatus(){
    // read steps
    for (auto const &step : steps) cout << step << endl;
    cout << " callback " << endl;
}

void Sequencer::callbackTest(int _n){
    cout << _n << endl;
}

//-----------------------------------------------------------
// ARPEGGIATOR
//-----------------------------------------------------------

void Arpeggiator::setup(NoteController* _controller, vector<double>& _notes){
    controller = _controller;
    notes.clear();
    notes.resize(_notes.size());
    notes = _notes;
    currentNote = 0; // init
    tick_Note   = 0; // init
     norgardNotes = norgard<int>(1, 100);
}

//--------------------------------------------------------------

void Arpeggiator::arpeggio(int _rootNote, int _arpeggiotype, int _octave){
    arp.clear();
    scale.clear();
    tonic   = 12 * _octave + _rootNote;
    switch(_arpeggiotype)
    {
        case 0 :
            third   = 4  + tonic;
            fifth   = 7  + tonic;
            octave  = 12 + tonic;
            arp.push_back(notes[tonic]);
            arp.push_back(notes[third]);
            arp.push_back(notes[fifth]);
            arp.push_back(notes[octave]);
            break;
        case 1 :
            third   = 3  + tonic;
            fifth   = 7  + tonic;
            octave  = 12 + tonic;
            arp.push_back(notes[tonic]);
            arp.push_back(notes[third]);
            arp.push_back(notes[fifth]);
            arp.push_back(notes[octave]);
            break;
        case 2 :
            arp.push_back(notes[tonic]);
            break;
        case 3 :
            for (int i = 0; i < 10; i++){
                // lydian scale
                octave = (12 * i) + _rootNote;
                scale.push_back(notes[octave]);
                scale.push_back(notes[octave+2]);
                scale.push_back(notes[octave+4]);
                scale.push_back(notes[octave+5]);
                scale.push_back(notes[octave+8]);
                scale.push_back(notes[octave+9]);
                scale.push_back(notes[octave+11]);
                int startingpoint = _octave * 7 + _rootNote;
                for (int i = 0; i < norgardNotes.size(); i++){
                    arp.push_back(scale[startingpoint + norgardNotes[i]]);
                }
            }
            break;
            deafult :
            arp.push_back(notes[tonic]);
    }

    

    
}

//--------------------------------------------------------------

void Arpeggiator::run(){
    pattern(controller->nBeats, controller->stepSize, controller->offset);
    
  //  arpeggio(controller->note, controller->arpeggioType);
    arpeggio(controller->note, controller->arpeggioType, 3); // rootnote, arpeggiotype, octave
    
    switch(controller->subdivision)
    {
        case 0 :
            setSubdivision("4thNote");
            break;
        case 1 :
            setSubdivision("8thNote");
            break;
        case 2 :
            setSubdivision("16thNote");
            break;
            deafult :
            setSubdivision("16thNote");
    }
    
}

//--------------------------------------------------------------

void Arpeggiator::registerOscillator(Callback _callback){
    callback = _callback;
}

//--------------------------------------------------------------

void Arpeggiator::incr(){
    // i don't want to start from the middle of the vector, but instead choose a point somewhere
    currentNote = arp[tick_Note];
    callback(currentNote, 0); // frequency, frequency modulation
    tick_Note   = ++ tick_Note % arp.size(  ); // assuming the norgard one is the one that goes out of bounds
    
    
}

//--------------------------------------------------------------