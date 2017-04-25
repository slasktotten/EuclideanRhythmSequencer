//
//  metronome.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 25/11/2016.
//
//

#ifndef metronome_hpp
#define metronome_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofThread.h"
#include <thread>
#include <memory>



class Sequencer; //forward decleration
typedef std::shared_ptr<Sequencer> sharedptr;
typedef unsigned long long ull;


class Metronome : public ofThread {
private:
    static Metronome *theMetronome;
    Metronome();
public:
    ~Metronome();
    static Metronome &get();
    ull lengthOfOneBeatInSamples;
    int sampleCount;
    ull getNextPulse();
    ull getNextEigthNote();
    ull getNextSixteenthNote();
    ull setSubdivision(char selection);
    ull *pulse, *eigthNote, *sixteenthNote;
    void getNextSample();
    void setTempo(int _bpm);
    void updateSubdivisions();
    void registerSequencerListeners(vector<sharedptr> _sequencers);
    void getSequencerStatus();
 
    //vector<Sequencer *> sequencers;
    vector<std::shared_ptr<Sequencer>> sequencers;
    
    // just have metronome class signal for the subdivisions maybe?
    
    // thread code goes here //
//    
//    long bpm;
//    long ms;
//    
//    bool trigger0;
//    bool trigger1;
//    bool trigger2;
//    
//    int threadCount = 0;
//    int prevCount   = 0;
//    
//    
//    void start(){
//        bpm = 20;
//        trigger0 = false;
//        trigger1 = false;
//        trigger2 = false;
//        startThread();
//    
//      
//    }
//    
//    void stop(){
//        stopThread();
//    }
//    
//   //   ms = 60000/bpm;
//    void threadedFunction(){
//        while(isThreadRunning())
//        {
//            if(lock())
//            {
//               // unique_lock<std::mutex> lock(mutex);
//                threadCount++;
//                trigger0 = true;
//                trigger1 = true;
//                trigger2 = true;
//                unlock();
//                sleep(150);
//            }
//        }
//    }
//    
//    
//    
//    int getCount()
//    {
//        unique_lock<std::mutex> lock(mutex);
//        return threadCount;
//    }
//    
//    bool getTrigger0()
//    {
//        unique_lock<std::mutex> lock(mutex);
//        return trigger0;
//    }
//    
//    bool getTrigger1()
//    {
//        unique_lock<std::mutex> lock(mutex);
//        return trigger1;
//    }
//    
//    bool getTrigger2()
//    {
//        unique_lock<std::mutex> lock(mutex);
//        return trigger2;
//    }
//    
//  void resetTriggers()  {
//     // unique_lock<std::mutex> lock(mutex);
//        trigger0 = false;
//        trigger1 = false;
//        trigger2 = false;
//    }
    
    
};



/*
 i will be having a thread that wakes up and goes to sleep
 because im not just continiously counting something as in frames sent i need to be more specific
 
 we can be infinitely specific so make the thread count up every 32nd note
 this means that 
 every single tick = 32nd note
 every 2nd    tick = 16th note
 every 4th    tick = 8th  note
 every 8th    tick = 4th  note
 
 this means 
 threadCount % pulse
 if (threadCount % subdivision ==0)
 */


#endif /* metronome_hpp */
