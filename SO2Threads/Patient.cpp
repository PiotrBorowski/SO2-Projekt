//
// Created by borowski on 29.05.19.
//

#include "Patient.h"
#include <thread>
#include <cstdlib>
#include <unistd.h>

void Patient::TakeDrug(Nurse *nurse, Drug *drug) {
    _state = Action::TakeDrug;

    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }
}

void Patient::UndergoOperation(Doctor *doctor, Nurse *nurse, OperatingRoom *operatingRoom) {
    _state = Action::UndergoOperation;

    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }
}

Action Patient::VisitDoctor(Doctor *doctor) {
    _state = Action::VisitDoctor;

    short roll = std::rand() % 100;

    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }

    if(roll < 40){
        return Action::VisitDoctor;
    }
    else if (roll < 70){
        return Action::TakeDrug;
    }
    else{
        return Action::UndergoOperation;
    }
}
