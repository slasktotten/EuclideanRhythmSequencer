//
//  drawshape.hpp
//  808_kick
//
//  Created by gustaf svenungsson on 30/11/2016.
//
//

#ifndef drawshape_hpp
#define drawshape_hpp

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"
#include "sequencer.hpp"


class DrawShape{
public:
    void drawLines();
    void setup();
    void setup(Sequencer *_sequencer, float _tx, float _ty);
    void draw();
    void run();
    void clear();
    void update();
    int  circle_resolution;
    int  radius;
    DrawShape();
    DrawShape(Sequencer *_sequencer, float _tx, float _ty);
    ~DrawShape();
    Sequencer *sequencer;
    ofVec2f pos;
    ofVec2f prev_pos;
    vector<ofVec2f> points;
    vector<int> ticks;
    float x, y, angle;
    float tx, ty;
    int temp;
    
    
    /* 
     positive modulo
     because c++ doesnt positive modulus.
     obvs
     */
    inline int positive_modulo(int i, int n);
};

#endif /* drawshape_hpp */
