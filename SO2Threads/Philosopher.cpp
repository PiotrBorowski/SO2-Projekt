//
// Created by borowski on 03.03.19.
//

#include "Philosopher.h"
#include <thread>
#include <cstdlib>
#include <unistd.h>


Philosopher::Philosopher(Fork* leftFork, Fork* rightFork)
{
    _leftFork = leftFork;
    _rightFork = rightFork;
    _progress = 0;
}

Philosopher::Philosopher(Fork* leftFork, Fork* rightFork, int id) : Philosopher(leftFork, rightFork)
{
    _id = id;
}

Philosopher::~Philosopher() {
    delete _leftFork;
    delete _rightFork;
}

void Philosopher::Think() {
    _state = State::thinking;
    _progress = 0;
    for (int i = 0; i < 10; ++i) {
        _progress++;
        usleep(300000 + std::rand() % 100000);
    }
}

void Philosopher::PutDownForks() {
    _leftFork->PutDown();
    _rightFork->PutDown();
}

void Philosopher::PickupForks() {

    _leftFork->Take(_id);
    _rightFork->Take(_id);
}

void Philosopher::Eat() {

    PickupForks();


    _state = State::eating;
    _progress = 0;
    for (int i = 0; i < 10; ++i) {
        _progress++;
        usleep(300000 + std::rand() % 100000);
    }

    PutDownForks();
}

std::string Philosopher::GetName(){
    return "philosopher" + std::to_string(_id);
}

State Philosopher::GetState() {
    return _state;
}

int Philosopher::GetProgress() {
    return _progress;
}

int Philosopher::GetId() {
    return _id;
}
