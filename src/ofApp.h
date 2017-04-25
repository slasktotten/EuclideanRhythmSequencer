#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "Oscilllator.hpp"
#include "delay.hpp"
#include "sequencer.hpp"
#include "metronome.hpp"
#include "ofxGui.h"
#include "drawshape.hpp"
#include "controller.hpp"

typedef unsigned long long ull;
typedef std::shared_ptr<NoteController> derivedptr;

using namespace std::placeholders; // use for std::bind parameters readability

struct Notes{
    vector<double> frequencyVector;
    convert mtof;
    const int nMidiValues = 127;
    Notes() {
        for (int i = 0; i <= nMidiValues; i++){
            frequencyVector.push_back(mtof.mtof(i));
        }
    }
};



class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void exit();
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
    void audioOut(float * output, int bufferSize, int nChannels);
    
    float amp;
    float dB;
    int bpm;
    double mixedSignal[2];
    
    const int sampleRate = 44100; // const instead of a #define
    const int bufferSize = 256;
    inline float AmplitudeTodB(float *_amplitude);
    inline float dBToAmplitude(float *_dB);

    Notes notes;
    
    ofxPanel gui;
    ofParameterGroup parameterGroup;
    
    ofSoundStream soundStream;
   
    vector<std::unique_ptr<DrawShape>> ptr_drawshape;
    vector<std::shared_ptr<Arpeggiator>> arpeggiator;
    vector<std::shared_ptr<Sequencer>> sample_sequencer;
    
    
    vector<Controller *> ptr_controller;
// make some kind of listener, so that nBeats cant be larger than nSize
    
    
    vector<maxiSample> sample;
    vector<Carrier>    c;
    vector<FM>         fm;
    
    double sampleOutput();
    void carrierUpdate();
    double carrierOutput();
    
    double sampleout;
    double finalOutput;
    double carrierout;
    
    std::function<void(double, double)> cb;
    
    


        maxiMix       mix;
        myDelay       delay;
    //    maxiDyn       comp;
    //    maxiFilter    lowpass;
    //    Instrument    instr;
    //    Reverb        reverb; //not working
};
