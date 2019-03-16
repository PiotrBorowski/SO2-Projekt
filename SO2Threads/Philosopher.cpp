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
    _name = "default";
    _progress = 0;
}

Philosopher::Philosopher(Fork* leftFork, Fork* rightFork, std::string name) : Philosopher(leftFork, rightFork)
{
    _name = name;
}

void Philosopher::Think() {
    _state = State::thinking;
    _progress = 0;
    for (int i = 0; i < 10; ++i) {
        _progress++;
        usleep(300000 + std::rand() % 100000);
    }
}

void Philosopher::PutDownFork() {
    _leftFork->PutDown();
    _rightFork->PutDown();
}

void Philosopher::PickupFork() {

    _leftFork->Take();
    _rightFork->Take();
}

void Philosopher::Eat() {
    _state = State::eating;
    _progress = 0;
    for (int i = 0; i < 10; ++i) {
        _progress++;
        usleep(300000 + std::rand() % 100000);
    }
}

std::string Philosopher::GetName(){
    return _name;
}

State Philosopher::GetState() {
    return _state;
}

int Philosopher::GetProgress() {
    return _progress;
}
