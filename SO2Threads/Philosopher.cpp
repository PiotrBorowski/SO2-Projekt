//
// Created by borowski on 03.03.19.
//

#include "Philosopher.h"
#include <thread>
#include <cstdlib>

Philosopher::Philosopher(Fork* leftFork, Fork* rightFork)
{
    _leftFork = leftFork;
    _rightFork = rightFork;
    _name = "default";
}

Philosopher::Philosopher(Fork* leftFork, Fork* rightFork, std::string name) : Philosopher(leftFork, rightFork)
{
    _name = name;
}

void Philosopher::Think() {
    _state = "mysle";
    std::this_thread::sleep_for(std::chrono::seconds(1 + std::rand()%2 ));
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
    _state = "jem";
    std::this_thread::sleep_for(std::chrono::seconds(2 + std::rand()%2 ));
}

std::string Philosopher::GetName(){
    return _name;
}

std::string Philosopher::GetState() {
    return _state;
}
