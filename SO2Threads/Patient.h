//
// Created by borowski on 29.05.19.
//

#ifndef SO2_PROJEKT_PATIENT_H
#define SO2_PROJEKT_PATIENT_H


#include "Doctor.h"
#include "Nurse.h"
#include "Drug.h"
#include "OperatingRoom.h"

enum Action{
    None,
    VisitDoctor,
    TakeDrug,
    UndergoOperation
};

class Patient {

public:
    Patient(short id);

    Action VisitDoctor(Doctor* doctor);

    void TakeDrug(Nurse * nurse, Drug * drug);
    void UndergoOperation(Doctor * doctor, Nurse * nurse, OperatingRoom * operatingRoom);
    int GetId();
    int GetProgress();
    Action GetState();
    Action GetNextState();

private:
    short _progress;
    short _id;
    Action _state = Action::None;
    Action _nextState = Action::None;

};


#endif //SO2_PROJEKT_PATIENT_H
