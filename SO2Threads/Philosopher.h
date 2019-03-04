//
// Created by borowski on 03.03.19.
//

#ifndef SO2_PROJEKT_PHILOSOPHER_H
#define SO2_PROJEKT_PHILOSOPHER_H


#include "Fork.h"

class Philosopher {
public:
    Philosopher(Fork* leftFork, Fork* rightFork);
    void Eat();
    void Think();
    void PickupFork();
    void PutDownFork();
private:
    Fork* _leftFork;
    Fork* _rightFork;
};


#endif //SO2_PROJEKT_PHILOSOPHER_H
