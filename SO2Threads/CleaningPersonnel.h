//
// Created by borowski on 29.05.19.
//

#ifndef SO2_PROJEKT_CLEANINGPERSONNEL_H
#define SO2_PROJEKT_CLEANINGPERSONNEL_H


#include "OperatingRoom.h"

enum PersonelState {
    cleaningOR,
    cleaningCorridor
};

class CleaningPersonnel {
public:
    CleaningPersonnel(short id);
    void CleanOperatingRoom(OperatingRoom * operatingRoom);
    void CleanCorridor();
    int GetId();
    int GetProgress();
    PersonelState GetState();
private:
    short _progress;
    short _id;
    PersonelState _state;
};


#endif //SO2_PROJEKT_CLEANINGPERSONNEL_H
