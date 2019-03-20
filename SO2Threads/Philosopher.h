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
    Philosopher(Fork* leftFork, Fork* rightFork, int id);
    ~Philosopher();

    std::string GetName();
    State GetState();
    int GetProgress();
    int GetId();

    void Eat();
    void Think();

private:
    void PickupForks();
    void PutDownForks();

    Fork* _leftFork;
    Fork* _rightFork;
    State _state;
    int _progress;
    int _id;
};


#endif //SO2_PROJEKT_PHILOSOPHER_H
