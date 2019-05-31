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
    doctor->Request(this->_id);
    doctor->Use();

//    nurse->Request(this->_id);
//    nurse->Use();

    operatingRoom->Request(this->_id);
    operatingRoom->Use();

    _state = Action::UndergoOperation;

    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }

    doctor->Bye();
//    nurse->Bye();
    operatingRoom->Exit();
}

Action Patient::VisitDoctor(Doctor *doctor) {
    doctor->Request(this->_id);
    doctor->Use();
    _state = Action::VisitDoctor;

    short roll = std::rand() % 100;

    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }

    doctor->Bye();

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

Patient::Patient(short id) {
    _id = id;
}

int Patient::GetId() {
    return _id;
}

int Patient::GetProgress() {
    return _progress;
}

Action Patient::GetState() {
    return _state;
}
