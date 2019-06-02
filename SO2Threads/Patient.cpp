//
// Created by borowski on 29.05.19.
//

#include "Patient.h"
#include <thread>
#include <cstdlib>
#include <unistd.h>

void Patient::TakeDrug(Nurse *nurse, Drug *drug) {
    nurse->Request(this->_id);
    nurse->Use();
    drug->Request(this->_id);
    drug->Use();

    _state = Action::TakeDrug;
    _nextState = Action::VisitDoctor;


    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }

    nurse->Bye();
    drug->GetBack();
    _state = Action::None;
}

void Patient::UndergoOperation(Doctor *doctor, Nurse *nurse, OperatingRoom *operatingRoom) {
    doctor->Request(this->_id);
    doctor->Use();

    nurse->Request(this->_id);
    nurse->Use();

    operatingRoom->Request(this->_id);
    operatingRoom->Use();


    _state = Action::UndergoOperation;
    _nextState = Action::VisitDoctor;

    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }

    doctor->Bye();
    nurse->Bye();
    operatingRoom->Exit();
    _state = Action::None;
}

Action Patient::VisitDoctor(Doctor *doctor) {
    doctor->Request(this->_id);
    doctor->Use();
    _state = Action::VisitDoctor;
    _nextState = None;

    short roll = std::rand() % 100;

    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }

    doctor->Bye();
    _state = Action::None;

    if(roll < 33){
        _nextState = Action::VisitDoctor;
        return Action::VisitDoctor;
    }
    else if (roll < 80){
        _nextState = Action::TakeDrug;
        return Action::TakeDrug;
    }
    else{
        _nextState = Action::UndergoOperation;
        return Action::UndergoOperation;
    }
}

Patient::Patient(short id) {
    _id = id;
}

short Patient::GetId() {
    return _id;
}

int Patient::GetProgress() {
    return _progress;
}

Action Patient::GetState() {
    return _state;
}

Action Patient::GetNextState() {
    return _nextState;
}

short Patient::GetNurseId() {
    return nurseId;
}

short Patient::GetDoctorId() {
    return doctorId;
}

void Patient::SetNurseId(short id) {
    nurseId = id;
}

void Patient::SetDoctorId(short id) {
    doctorId = id;
}
