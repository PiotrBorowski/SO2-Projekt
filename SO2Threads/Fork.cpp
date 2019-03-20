//
// Created by borowski on 03.03.19.
//

#include "Fork.h"

Fork::Fork(int ownerId){
    _forkState = ForkState::dirty;
    _ownerId = ownerId;
}

void Fork::Take() {
    _mutex.lock();
    _isTaken = true;
}

void Fork::Use(){
    _forkState = ForkState::dirty;
}

void Fork::PutDown() {
    _mutex.unlock();
    _isTaken = false;
}

void Fork::CleanUp() {
    _forkState = ForkState::clean;
}