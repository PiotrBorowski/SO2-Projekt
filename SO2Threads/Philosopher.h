//
// Created by borowski on 03.03.19.
//

#ifndef SO2_PROJEKT_PHILOSOPHER_H
#define SO2_PROJEKT_PHILOSOPHER_H


#include "Fork.h"

enum State
{
    eating,
    thinking
};

class Philosopher {
public:
    Philosopher(Fork* leftFork, Fork* rightFork);
    Philosopher(Fork* leftFork, Fork* rightFork, std::string name);
    ~Philosopher();
    std::string GetName();
    State GetState();
    int GetProgress();
    void Eat();
    void Think();

private:
    void PickupForks();
    void PutDownForks();

    Fork* _leftFork;
    Fork* _rightFork;
    std::string _name;
    State _state;
    int _progress;
};


#endif //SO2_PROJEKT_PHILOSOPHER_H
