//
//  sequencer.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 04/11/2016.
//
//

#include "sequencer.hpp"

typedef unsigned long long ull;

Sequencer::Sequencer(Metronome* _metronome):
metronome(_metronome)
{
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
    p = &Metronome::setSubdivision;
}

Sequencer::Sequencer(Metronome* _metronome, Controller *_controller):
metronome(_metronome), controller(_controller)
{
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
    p = &Metronome::setSubdivision;
}


/* EUCLIDEAN RHYTHM ALGORITHM, RETURNS A VECTOR OF BOOLS THAT IS USED AS INPUT FOR OUR STEPSEQUENCER*/
//modified from https://bitbucket.org/sjcastroe/bjorklunds-algorithm
vector<bool> Sequencer::bjorklund(int beats, int steps)
{
    vector<bool> x;
    x.push_back(true);
    vector<bool> y;
    y.push_back(false);
    int x_amount = beats;
    int y_amount = steps - beats;
    do
    {
        int x_temp = x_amount;
        int y_temp = y_amount;
        vector<bool> y_copy = y;
        if (x_temp >= y_temp)
        {
            x_amount = y_temp;
            y_amount = x_temp - y_temp;
            y = x;
        }
        else
        {
            x_amount = x_temp;
            y_amount = y_temp - x_temp;
        }
        for (int i = 0; i < y_copy.size(); i++){
            x.push_back(y_copy[i]);
        }
    } while (x_amount > 1 && y_amount > 1);
    vector<bool> r;
    for (int i =0; i < x_amount; i++){
        for (int i = 0; i < x.size(); i++) r.push_back(x[i]);
    }
    
    for (int i = 0; i < y_amount; i++){
        for (int i = 0; i < y.size(); i++) r.push_back(y[i]);
    }
    return r;
}

//Pattern is where we set the size of the sequence, how many beats it's going to have
void Sequencer::pattern(int _beats, int _stepSize){
    stepSize = _stepSize;
    nBeats   = _beats;
    
    //we cant have more hits than the sequence is long
    if (nBeats >= stepSize) nBeats = stepSize;
    
    steps.clear();
    steps.resize(stepSize);
    
    //set our stepsequence to that of the algorithm
    steps = bjorklund(nBeats, stepSize);
}
 


void Sequencer::pattern(int _beats, int _stepSize, int _offset){
    stepSize = _stepSize;
    nBeats   = _beats;
    offset   = _offset; //offset rhythm, i.e. choose at which hit you want to the pattern to start
    if (nBeats >= stepSize) nBeats = stepSize; //we cant have more hits than steps!
    steps.clear();
    steps.resize(stepSize);
    steps = bjorklund(nBeats, stepSize);
    
    //because we represent the pattern as a vector of booleans we can just rotate the elements of that vector to get another permutation of the rhythm
    //we do this "backwards" so that element 0 becomes element 1, instead of the last element in the vector
    rotate(steps.begin(), steps.end() - (offset % steps.size()), steps.end());
}


//The Metronome object stores everything time and timing related
void Sequencer::setSubdivision(string _theCurrentSubdivision){
    theCurrentSubdivision = _theCurrentSubdivision;
   // subdivision = p(char selection);
//    std::function<void(const Metronome&, ull)> fptr  = &Metronome::getNextPulse();
    if(theCurrentSubdivision == "4thNote")  subdivision = metronome->getNextPulse();
    if(theCurrentSubdivision == "8thNote")  subdivision = metronome->getNextEigthNote();
    if(theCurrentSubdivision == "16thNote") subdivision = metronome->getNextSixteenthNote();
}


void Sequencer::playSequence(){
    //first time through we have to synchronize the different subdivisions, otherwise eigthnotes would start earlier than pulse, sixteenthnote notes before eigthNotes.
    
    if(synchronize_subdivisions==1){
            if(metronome->sampleCount % metronome->getNextPulse() == 0) //if we are ready for the next beat
            {
                if(steps[tick] == 1){ //if the current tick (beat) is 1, play the sample, else dont
                    play = true;
                    trigger = 1;
                }
                play = false;
                tick = ++tick % stepSize; //increment tick, modulus stepsize to go back to beat 1 after end
            }
        }
    
    

    if(synchronize_subdivisions == 0){
    if(metronome->sampleCount % subdivision == 0)
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

void Sequencer::updateTempo(){
    setSubdivision(theCurrentSubdivision);
}

void Sequencer::run(){
    pattern(controller->nBeats, controller->stepSize, controller->offset);
}

