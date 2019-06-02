//
// Created by borowski on 29.05.19.
//

#ifndef SO2_PROJEKT_DRUG_H
#define SO2_PROJEKT_DRUG_H


#include "OperatingRoom.h"

class Drug {
public:
    Drug();
    void Request(int id);
    void GetBack();
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


#endif //SO2_PROJEKT_DRUG_H
