//
// Created by borowski on 29.05.19.
//

#ifndef SO2_PROJEKT_DOCTOR_H
#define SO2_PROJEKT_DOCTOR_H


#include "OperatingRoom.h"

class Doctor {
public:
    Doctor();
    void Request(int id);
    void Bye();
    void Use();
    short GetOwnerId();
private:
    bool _isBusy;
    short _ownerId;
    State _state;

    std::mutex _mutex;
    std::mutex _conditionMutex;
    std::condition_variable _condition_variable;

    void SetConditionVariable();
    void UnlockConditionVariable();
    void Take(int ownerId);
    void CleanUp();
};


#endif //SO2_PROJEKT_DOCTOR_H
