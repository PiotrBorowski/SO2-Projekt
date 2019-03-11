//
// Created by borowski on 03.03.19.
//

#ifndef SO2_PROJEKT_PHILOSOPHER_H
#define SO2_PROJEKT_PHILOSOPHER_H


#include "Fork.h"

class Philosopher {
public:
    Philosopher(Fork* leftFork, Fork* rightFork);
    Philosopher(Fork* leftFork, Fork* rightFork, std::string name);

    std::string GetName();
    std::string GetState();
    int GetProgress();
    void Eat();
    void Think();
    void PickupFork();
    void PutDownFork();
private:
    Fork* _leftFork;
    Fork* _rightFork;
    std::string _name;
    std::string _state = "nic";
    int _progress;
};


#endif //SO2_PROJEKT_PHILOSOPHER_H
