//
//  sequencer.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 04/11/2016.
//
//

#ifndef sequencer_hpp
#define sequencer_hpp
#include <stdio.h>
#include <array>
#include "ofMain.h"
#include "ofxMaxim.h"
#include "metronome.hpp"
#include "controller.hpp"
#include "bjorklund.h"
#include "norgard.h"
typedef std::function<void (double, double)> Callback;
typedef shared_ptr<Controller> s_ctrl;
typedef shared_ptr<NoteController> s_Nctrl;

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
   virtual void setup(Controller *_controller);
        Sequencer();
    Sequencer(Controller *_controller);
    ~Sequencer();
    Controller *controller;
  
    int synchronize_subdivisions;
    void updateTempo();
    void run();
    void getStatus();
    void callbackTest(int _n);
};

class Arpeggiator : public Sequencer{
    
public:
    void registerOscillator(Callback _callback);
    void arpeggio(int _rootNote, int _arpeggiotype, int _octave);
    
    
    vector<double> arp;
    vector<double> notes;
    vector<int> norgardNotes;
    vector<int> scale;
    
    double currentNote;
    void setup(NoteController *_controller,vector<double>& _notes);

    void run();
    Callback callback;
   NoteController *controller;

    int tonic;
    int third;
    int fifth;
    int octave;
    int checkForIllegalValue(int _valueToCheck, int maxValue);
    int tick_Note;
    
    // new nogard code //
    int nTonic;
    int nOctave;
    
    
    void incr();
    
};

#endif /* sequencer_hpp */
