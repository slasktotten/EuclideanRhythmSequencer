#include "ofApp.h"
/*
 speed of modulation - frequency of modulator
the amount of the modulation (how many hertz above and below the frequency of your carrier signal the audible signal will swing) is determined by the amplitude of the modulator.
 //maybe arpeggiator is a child of sequencer??? make different kinds of sequencer? traditional, euclidean, arpeggiator
 //use euclidean pattern inside delay maybe?
 //effects such as reverb, delay etc should deffo be structs!
 */

//https://www.youtube.com/watch?v=vwigqSwYNaQ Introduction to Euclidean Rhythms. The program is using this algorithm to generate the rhythms

//--------------------------------------------------------------
ofApp::ofApp():
metronome(sampleRate)
{}
//--------------------------------------------------------------
void ofApp::setup(){
    //    c.push_back(Carrier(30,  0, 0));
    //    c.push_back(Carrier(50,  0, 0));
    //    c.push_back(Carrier(100, 0, 0));
    //    amp = 1.0f / c.size();
    
    //    for (auto &carrier : c){
    //        carrier.setAmp(amp);
    //        carrier.setEnv(10, 500, 100, 600);
    //    }
    //
    //    fm.push_back(FM());
    //    fm.push_back(FM());
    //    fm.push_back(FM());
    //
    //    for (auto &modulator : fm){
    //        modulator.setAmp(amp);
    //        modulator.setEnv(10, 500, 100, 600);
    //    }
    
    //----------------------------------------------------------
    // GUI setup
    //----------------------------------------------------------
    controller.push_back(Controller());
    controller.push_back(Controller());
    controller.push_back(Controller());
    controller[0].setup("bassdrum");
    controller[1].setup("snare");
    controller[2].setup("hi-hat");
    parameterGroup.setName("setup");
    parameterGroup.add(controller[0].parameterGroup);
    parameterGroup.add(controller[1].parameterGroup);
    parameterGroup.add(controller[2].parameterGroup);
    gui.setup(parameterGroup);
    
    //----------------------------------------------------------
    // Audio setup
    //----------------------------------------------------------
    dB = 0; 
    bpm = 120;
    bufferSize = 256;
    sample.resize(3);
    
    //----------------------------------------------------------
    // Sample setup
    //----------------------------------------------------------

    sample[0].load("data/bd.wav");
    sample[1].load("data/snr.wav");
    sample[2].load("data/hh.wav");
    
    //----------------------------------------------------------
    // Sequencer setup
    //----------------------------------------------------------
    
    //create our sequencer objects, each takes a reference to metronome which is what keeps track of and increments time
   for (int i = 0; i < sample.size(); i++) sequencer.push_back(Sequencer(&metronome, &controller[i]));
    
    //set the subdivisions we want for our sequencers
    sequencer[0].setSubdivision("4thNote");
    sequencer[1].setSubdivision("4thNote");
    sequencer[2].setSubdivision("16thNote");
    
    //nBeats, stepSize, offset
    sequencer[0].pattern(2, 6, 0);
    sequencer[1].pattern(2, 4, 1);
    sequencer[2].pattern(4, 4);
    
    for (auto &s : sample) s.setPosition(1.0);
    
    //----------------------------------------------------------
    // Draw shapes
    //----------------------------------------------------------
    for (int i = 0; i < sequencer.size(); i++) drawshape.push_back(DrawShape(&sequencer[i], 250*(i+1), ofGetHeight()/2));
    for (auto &shape : drawshape) shape.setup();
    

    //----------------------------------------------------------
    // Soundstream setup
    //----------------------------------------------------------
    //output, input, samplerate, buffersize, number of buffers, two per channel is recommended
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);
  }

//--------------------------------------------------------------
void ofApp::update(){
    //-----------------------------------------------------------
    // update the shapes resolution
    //-----------------------------------------------------------
    for (auto &shape : drawshape) shape.update();
    
    //-----------------------------------------------------------
    // Update the sequencers
    //-----------------------------------------------------------
              for (auto &seq : sequencer) seq.run();

  
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    for (auto &shape : drawshape) shape.draw();
    gui.draw();
    cout << drawshape[0].temp << endl;
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels)
{
    for (int i = 0; i < bufferSize; i++){
        sampleOutput = 0;
        metronome.getNextSample();
        for (int i = 0; i < sequencer.size(); i++){
            sequencer[i].playSequence();
            if (sequencer[i].trigger == 1){
                sample[i].trigger();
                sequencer[i].trigger = 0;
                sequencer[i].synchronize_subdivisions = 0;
            }
        }
        for (auto &s : sample) sampleOutput += s.playOnce();
        sampleOutput *= dBToAmplitude(dB);
        output[i*nChannels]     = sampleOutput;
        output[i*nChannels + 1] = sampleOutput;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
     ///////////////////////////
    //   Test Interactions   //
   ///////////////////////////
    
    //change volume - dB
    if (key == 's') ++dB;
    if (key == 'a') --dB;
    
    //change bpm
    /*a little buggy but works*/
    if (key == 'q'){
          --bpm;
        metronome.setTempo(bpm);
        for (int i = 0; i < sequencer.size(); i++) sequencer[i].updateTempo();
    }
    if (key == 'w'){
        ++bpm;
        metronome.setTempo(bpm);
        for (int i = 0; i < sequencer.size(); i++) sequencer[i].updateTempo();
    }
}


//--------------------------------------------------------------
//https://www.youtube.com/watch?v=Vjm--AqG04Y&t=588s
float ofApp::AmplitudeTodB(float amplitude){
    return 20.0f * log10(amplitude);
}

float ofApp::dBToAmplitude(float dB){
    return pow(10.0f, dB/20.0f);
}

//--------------------------------------------------------------
















//--------------------------------------------------------------
void ofApp::keyReleased(int key){}

//--------------------------------------------------------------

//void ofApp::carrierUpdate(){
    //    for (int i = 0; i < sequencer.size(); i++){
    //        if (sequencer[i].play)  c[i].on();
    //        if (!sequencer[i].play) c[i].off();
    //    }
    //    c[0].setFreq(40,  fm[0].signal("sine", offset, fm_freq));
    //    c[1].setFreq(50,  fm[1].signal("sine", offset, fm_freq));
    //    c[2].setFreq(75,  fm[2].signal("sine", offset, fm_freq));
//}
//--------------------------------------------------------------
//void ofApp::carrierOutput(){
    //         for (auto &carrier : c) signal +=
    //    carrier.signal("sine");
    //            sig = delay.slapback(signal);
    //            mix.stereo(sig, mixedSignal, 0.5);
    //            sampleOut = sample[2].playOnce();
    //            output[i * nChannels] = sampleOut;
    //            output[i * nChannels + 1] = output[0];
    //            output[i * nChannels] =    mixedSignal[0];
    //            output[i * nChannels + 1] = mixedSignal[1];
//}

//--------------------------------------------------------------

void ofApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

