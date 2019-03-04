//
// Created by borowski on 03.03.19.
//

#include "Philosopher.h"
#include<thread>

Philosopher::Philosopher(Fork* leftFork, Fork* rightFork)
{
    _leftFork = leftFork;
    _rightFork = rightFork;
    _name = "default";
}

Philosopher::Philosopher(Fork* leftFork, Fork* rightFork, std::string name)
{
    _leftFork = leftFork;
    _rightFork = rightFork;
    _name = name;
}

void Philosopher::Think() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Philosopher::PutDownFork() {
    _leftFork->Take();
    _rightFork->Take();
}

void Philosopher::PickupFork() {
    _leftFork->PutDown();
    _rightFork->PutDown();
}

void Philosopher::Eat() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

std::string Philosopher::GetName(){
    return _name;
}
