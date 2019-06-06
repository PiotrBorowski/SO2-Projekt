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
    UndergoOperation,
    Home
};

class Patient {

public:
    Patient(short id);

    Action VisitDoctor(Doctor* doctor);

    void TakeDrug(Nurse * nurse, Drug * drug);
    void UndergoOperation(Doctor * doctor, Nurse * nurse, OperatingRoom * operatingRoom);
    void GoHome();

    short GetId();
    int GetProgress();
    short GetDoctorId();
    short GetNurseId();
    short GetDrugId();
    void SetDoctorId(short id);
    void SetNurseId(short id);
    void SetDrugId(short id);
    Action GetState();
    Action GetNextState();

private:
    short _progress;
    short _id;
    Action _state = Action::None;
    Action _nextState = Action::VisitDoctor;
    short doctorId, nurseId, drugId;

};


#endif //SO2_PROJEKT_PATIENT_H
