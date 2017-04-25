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
    // paraname, setval, minval, maxval
    parameterGroup.setName(name);
    parameterGroup.add(nBeats.set("nBeats", 5, 0, 64));
    parameterGroup.add(stepSize.set("stepSize", 5, 1, 64));
    parameterGroup.add(offset.set("offset", 5, 0, 63));
    parameterGroup.add(subdivision.set("subdivision", 1, 1, 3));
}

//-----------------------------------------------------------------//

NoteController::NoteController(){}

void NoteController::setup(string name){
    parameterGroup.setName(name);
    parameterGroup.add(nBeats.set("nBeats", 5, 0, 64));
    parameterGroup.add(stepSize.set("stepSize", 5, 1, 64));
    parameterGroup.add(offset.set("offset", 5, 0, 63));
    parameterGroup.add(subdivision.set("subdivision", 0, 0, 2));
    parameterGroup.add(note.set("note", 0, 0, 11));
    parameterGroup.add(arpeggioType.set("arpeggiotype", 0, 0, 3));
}

//-----------------------------------------------------------------//