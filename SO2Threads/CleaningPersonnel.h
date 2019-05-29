//
// Created by borowski on 29.05.19.
//

#ifndef SO2_PROJEKT_CLEANINGPERSONNEL_H
#define SO2_PROJEKT_CLEANINGPERSONNEL_H


#include "OperatingRoom.h"

class CleaningPersonnel {
public:
    void CleanOperatingRoom(OperatingRoom * operatingRoom);
    void CleanCorridor();
private:
    short _progress;
    short _id;
};


#endif //SO2_PROJEKT_CLEANINGPERSONNEL_H
