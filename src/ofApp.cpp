#include "ofApp.h"
/*
 speed of modulation - frequency of modulator
the amount of the modulation (how many hertz above and below the frequency of your carrier signal the audible signal will swing) is determined by the amplitude of the modulator.
 */

//https://www.youtube.com/watch?v=vwigqSwYNaQ Introduction to Euclidean Rhythms. The program is using this algorithm to generate the rhythms

/*
 
 MIDIVALUES :
 C   C#  D   D#  E   F   F#  G   G#  A   A#   B
 0   1   2   3   4   5   6   7   8   9   10   11
 12  13  14  15  16  17  18  19  20  21  22   23
 24  25  26  27  28  29  30  31  32  33  34   35
 36  37  38  39  40  41  42  43  44  45  46   47
 48  49  50  51  52  53  54  55  56  57  58   59
 60  61  62  63  64  65  66  67  68  69  70   71
 72  73  74  75  76  77  78  79  80  81  82   83
 84  85  86  87  88  89  90  91  92  93  94   95
 96  97  98  99  100 101 102 103 104 105 106  107
 108 109 110 111 112 113 114 115 116 117 118  119
 120 121 122 123 124 125 126 127 128 129 130  131
 
 */



//--------------------------------------------------------------
void ofApp::setup(){
    //----------------------------------------------------------
    // Carrier setup
    //----------------------------------------------------------
        c.push_back(Carrier(0,  0, 0));
        c.push_back(Carrier(0,  0, 0));
        c.push_back(Carrier(0, 0, 0));
        amp = 1.0f / c.size();
    
        for (auto &carrier : c){
            carrier.setAmp(amp);
            carrier.setEnv(10, 500, 100, 600);
            fm.push_back(FM());
        }
    
        for (auto &modulator : fm){
            modulator.setAmp(amp);
            modulator.setEnv(10, 500, 100, 600);
        }
    
    //----------------------------------------------------------
    // Sample setup
    //----------------------------------------------------------
    sample.resize(3);
    sample[0].load("data/bd.wav");
    sample[1].load("data/snr.wav");
    sample[2].load("data/hh.wav");
    for (auto &s : sample) s.setPosition(1.0);
    
    
    //----------------------------------------------------------
    // GUI setup
    //----------------------------------------------------------
     for (int i = 0; i < sample.size(); i++){
     ptr_controller.emplace_back(new Controller());
     }
     
     for (int i = 0; i < c.size(); i++){
     ptr_controller.emplace_back(new NoteController());
     }
    
    ptr_controller[0]->setup("bassdrum");
    ptr_controller[1]->setup("snare");
    ptr_controller[2]->setup("hi-hat");
    ptr_controller[3]->setup("oscillator1");
    ptr_controller[4]->setup("oscillator2");
    ptr_controller[5]->setup("oscillator3");
    parameterGroup.setName("setup");
    
    for (int i = 0; i < ptr_controller.size(); i++){
        parameterGroup.add(ptr_controller[i]->parameterGroup);
    }
    
    gui.setup(parameterGroup);
    
    //----------------------------------------------------------
    // Audio setup
    //----------------------------------------------------------
    dB = 0; 
    bpm = 200;
    
    //----------------------------------------------------------
    // Sequencer setup
    //----------------------------------------------------------
    for (int i = 0; i < sample.size(); i++){
        sample_sequencer.emplace_back(new Sequencer());
        sample_sequencer[i]->setup(ptr_controller[i]);
    }
    
    //----------------------------------------------------------
    // Arpeggiator setup
    //----------------------------------------------------------
       for (int i = 0; i < c.size(); i++){
           arpeggiator.emplace_back(new Arpeggiator());
           // use dynamic_cast to get access to functions unique to child class
        arpeggiator[i]->setup(dynamic_cast<NoteController *>(ptr_controller[i+sample.size()]), notes.frequencyVector);
    }
    
    //-----------------------------------------------------------
    // Register Sequencer Listeners in Metronome object
    //-----------------------------------------------------------
    vector<std::shared_ptr<Sequencer>> temp_ptr;
    for (int i = 0; i < sample_sequencer.size(); i++){
        temp_ptr.emplace_back(sample_sequencer[i]);
    }
    
    for (int i = 0; i < arpeggiator.size(); i++){
        temp_ptr.emplace_back(arpeggiator[i]);
    }
    
    Metronome::get().registerSequencerListeners(temp_ptr);
    
    
    //-----------------------------------------------------------
    // Register Carrier function in Arpeggio
    //-----------------------------------------------------------
    //   http://www.boost.org/doc/libs/1_50_0/libs/bind/bind.html#err_overloaded
    
    for (int i = 0; i < c.size(); i++){
        // register the callable function inside the arpeggiator. cast it to get access to the child class
        cb = std::bind( static_cast<void (Carrier::*)( double, double )>(&Carrier::setFreq) , &c[i], _1, _2);
        arpeggiator[i]->registerOscillator(cb);
    }
    
    //----------------------------------------------------------
    // Setup DrawShape
    //----------------------------------------------------------
    int y = ofGetHeight()/4;
    for (int i = 0; i < sample.size(); i++){
        ptr_drawshape.emplace_back(new DrawShape());
        // pass a constant reference instead
        ptr_drawshape[i]->setup(*sample_sequencer[i], 250*(i+1), y); // rewrite to be passed by reference
    }
    
    for (int i = 0; i < c.size(); i++){
        ptr_drawshape.emplace_back(new DrawShape());
        // pass a constant reference instead
        ptr_drawshape[sample.size()+i]->setup(*arpeggiator[i], 250*(i+1), y * 3); // rewrite to be passed by reference
    }
    
    //----------------------------------------------------------
    // Soundstream setup
    //----------------------------------------------------------
    soundStream.setup(this, 2, 0, sampleRate, bufferSize, 4);

  }

//--------------------------------------------------------------
void ofApp::update(){
    //-----------------------------------------------------------
    // update the shapes resolution
    //-----------------------------------------------------------
    for (const auto &ptr : ptr_drawshape) ptr->update();
    
    //-----------------------------------------------------------
    // Update the arpeggiators
    //-----------------------------------------------------------
    for (const auto &ptr : arpeggiator) ptr->run();

    
    //-----------------------------------------------------------
    // Update the sequencers
    //-----------------------------------------------------------
    for (const auto &ptr : sample_sequencer) ptr->run();
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    for (const auto &ptr: ptr_drawshape) ptr->draw();
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels)
{
    for (int i = 0; i < bufferSize; i++){

        Metronome::get().getNextSample();
        finalOutput = (sampleOutput()+ carrierOutput()) * dBToAmplitude(&dB);
        finalOutput = finalOutput * 0.6;

        output[i*nChannels]     = finalOutput;
        output[i*nChannels + 1] = finalOutput;
    }

}

//--------------------------------------------------------------
//https://www.youtube.com/watch?v=Vjm--AqG04Y&t=588s
float ofApp::AmplitudeTodB(float *_amplitude){
    return 20.0f * log10(*_amplitude);
}

float ofApp::dBToAmplitude(float *_dB){
    return pow(10.0f, *_dB/20.0f);
}

//--------------------------------------------------------------
double ofApp::sampleOutput(){
  sampleout = 0;
    for (int j = 0; j < sample.size(); j++){
        sample_sequencer[j]->playSequence();
        if (sample_sequencer[j]->trigger == 1){
            sample[j].trigger();
            sample_sequencer[j]->trigger = 0;
            sample_sequencer[j]->synchronize_subdivisions = 0;
        }
    }
    for (auto &s : sample) sampleout += s.playOnce();
    return sampleout;
    
}

//--------------------------------------------------------------
void ofApp::carrierUpdate(){
    for (int i = 0; i < c.size(); i++){
        arpeggiator[i]->playSequence();
        if (arpeggiator[i]->trigger == 1){
            c[i].on();
            arpeggiator[i]->incr();
        }
        if (arpeggiator[i]->trigger == 0) c[i].off();
        arpeggiator[i]->trigger=0;
    }
}

//--------------------------------------------------------------
double ofApp::carrierOutput(){
    carrierUpdate();
    carrierout = 0;
    for (auto &carrier : c) carrierout += carrier.signal("sine");
    return carrierout;
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    // when exiting we want to stop the soundStream. Otherwise the app will try to access the audiothread after we've deleted objects inside it
    // ask in lesson why this is so? shouldnt exit stop the audiothread?
    
    soundStream.stop();
    
    for(auto &ptr: ptr_controller){
        delete ptr;    // delete what ptr points to
        ptr = nullptr; // point ptr at 0
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
    
    //change tempo - bpm
    /*a little buggy but works*/
    if (key == 'q'){
        --bpm;
        Metronome::get().setTempo(bpm);
    }
    if (key == 'w'){
        ++bpm;
        Metronome::get().setTempo(bpm);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){}
