//
//  drawshape.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 30/11/2016.
//
//

#include "drawshape.hpp"

DrawShape::DrawShape(){}
//--------------------------------------------------------------


DrawShape::DrawShape(Sequencer *_sequencer, float _tx, float _ty): sequencer(_sequencer), tx(_tx), ty(_ty)
{}

//--------------------------------------------------------------
DrawShape::~DrawShape(){}

//--------------------------------------------------------------

void DrawShape::setup(){
    //radius of circle
    radius = 80;
    temp = 0;
}

//--------------------------------------------------------------

// turn into templated function with auto variable


void DrawShape::setup(Sequencer &_sequencer, float _tx, float _ty){
    sequencer = &_sequencer;
    tx = _tx;
    ty = _ty;
    
    //radius of circle
    radius = 80;
    temp = 0;
}
//--------------------------------------------------------------

//void DrawShape::setup(Arpeggiator *_sequencer, float _tx, float _ty){
//    sequencer = _sequencer;
//    tx = _tx;
//    ty = _ty;
//    
//    //radius of circle
//    radius = 80;
//    temp = 0;
//}
//--------------------------------------------------------------

void DrawShape::update(){
    //amount of points in our circle
      circle_resolution = sequencer->stepSize;
}

//--------------------------------------------------------------

void DrawShape::draw(){
    ofPushMatrix();
    ofTranslate(tx, ty); // move initital drawing postion to the center of the screen
    
    for( int i = 0; i < circle_resolution; i ++) {
        angle = TWO_PI/ circle_resolution*i;
        x = cos(angle) * radius;
        y = sin(angle) * radius;
        pos.set(x,y);
        
        //create a point for each step that is a hit. these are to connect the circles that are hits.
        if(sequencer->steps[i] == 1){
            points.push_back(ofVec2f(pos.x, pos.y));
        }
        ofPushStyle();
        
        //moving circle, timing not working properly, so to compensate

        //sequencer is ticking upp from 0-4
        temp = (sequencer->tick);
        
        temp = positive_modulo(temp-1, circle_resolution);
        
        if(temp == i){
            ofNoFill();
            ofDrawCircle(pos.x, pos.y, 50);
        }
        ofPopStyle();
        
        if(sequencer->steps[i] == 1) {
            ofFill();
            ofDrawCircle(pos.x, pos.y, 7);
        }else{
            ofDrawCircle(pos.x, pos.y, 2);
        }
    }
    
    drawLines();
    ofPopMatrix();
    points.clear(); // clear the vector
}

//--------------------------------------------------------------

void DrawShape::drawLines(){
    for( int i = 0; i < circle_resolution; i ++) {
        if ( i < points.size()-1){
            ofDrawLine(points[i].x, points[i].y, points[i+1].x, points[i+1].y);
        }else {
            ofDrawLine(points[points.size()-1].x, points[points.size()-1].y, points[0].x, points[0].y);
        }
    }
}

//--------------------------------------------------------------
//http://stackoverflow.com/questions/14997165/fastest-way-to-get-a-positive-modulo-in-c-c
int DrawShape::positive_modulo(int i, int n){
    return (i % n + n) % n;
}