//
//  sequencer.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 04/11/2016.
//
//

#ifndef sequencer_hpp
#define sequencer_hpp
typedef unsigned long long ull;

#include <stdio.h>
#include <array>
#include "ofMain.h"
#include "ofxMaxim.h"
#include "metronome.hpp"
#include "controller.hpp"


     //////////////////////////////////////////////////////////////////
    // tick keeps track of where we are in time                     //
   // stepSize is the length of the sequence (i.e. how many nHits) //
  // trigger is for triggering samples                            //
 // nBeats is how many hits we have in our sequence              //
//  offset offsets the rhythmic sequence                        //
/////////////////////////////////////////////////////////////////


class Sequencer {
public:
    vector<bool> steps; //the pattern of the stepsequencer
    ull subdivision;   //subdivision of sequencer
    string theCurrentSubdivision;
    int tick, stepSize, trigger, nBeats, offset;
    bool play;
    void playSequence();
    void pattern(int _beats, int _stepSize);
    void pattern(int _beats, int _stepSize, int _offset);
    void setSubdivision(string theCurrentSubdivisionIs);
    
    vector<bool> bjorklund(int b, int s);
    Sequencer(Metronome *_metronome);
    Sequencer(Metronome *_metronome, Controller *_controller);
    Metronome *metronome;
    Controller *controller;
    int synchronize_subdivisions;
    void updateTempo();
    void run();
    //ull (Metronome::*pt2function)(char selection)= NULL;
    ull (Metronome::*p) (char);
};

#endif /* sequencer_hpp */
