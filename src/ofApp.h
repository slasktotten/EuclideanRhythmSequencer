#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "Oscilllator.hpp"
#include "Instrument.hpp"
#include "delay.hpp"
#include "sequencer.hpp"
#include "reverb.hpp"
#include "metronome.hpp"
#include "ofxGui.h"
#include "drawshape.hpp"
#include "controller.hpp"
typedef unsigned long long ull;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        ofApp();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void drawLines();
        void audioOut(float * output, int bufferSize, int nChannels);
      float amp;
      float dB;
      int bufferSize;
      int nBeats;
      int bpm;
const int sampleRate = 44100;
      double mixedSignal[2];
      double fm_freq, offset;
      double sampleOutput;
    
    inline float AmplitudeTodB(float amplitude);
    inline float dBToAmplitude(float dB);
    
    ofxPanel gui;
    ofParameterGroup parameterGroup;
    vector<Controller> controller;
    
    ofSoundStream soundStream;
    Metronome     metronome;
    
    vector<Carrier>    c;
    vector<FM>         fm;
    vector<Sequencer>  sequencer;
    vector<maxiSample> sample;
    vector<DrawShape> drawshape;

    //void carrierUpdate();
    // void carrierOutput();
    //    maxiMix       mix;
    //    maxiDyn       comp;
    //    maxiFilter    lowpass;
    //    Instrument    instr;
    //    myDelay       delay;
    //    Reverb        reverb; //not working
};


//add oscillator when a key is pressed. make sure the note corresponds to correct key input, i.e. c.push_back(); this means i have to move frequency and other things to the constructor

//3 ocillator subtractive synth

//am, filter