//
//  controller.cpp
//  808_kick
//
//  Created by gustaf svenungsson on 02/12/2016.
//
//

#include "controller.hpp"

Controller::Controller(){}

void Controller::setup(string name){
    parameterGroup.setName(name);
    parameterGroup.add(nBeats.set("nBeats", 5, 0, 64));
    parameterGroup.add(stepSize.set("stepSize", 5, 0, 64));
    parameterGroup.add(offset.set("offset", 5, 0, 63));
}

/*
 TO DO
 
- add controllers for bpm and subdivisions
- add some "listeners" maybe? make sure that the sliders max point are sensible, that they start with initial values of the sequencers themselves and and that nBeats - max cant be more than the current size of stepsize
 this would also mean that the max of offsize is always stepSize -1 
 
- add a seperate slider for volume - represented in db, tempo - represented in bpm and buttons for changing the subdivisions
 */