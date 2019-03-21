//
// Created by borowski on 03.03.19.
//

#include "Fork.h"

Fork::Fork(int ownerId){
    _forkState = ForkState::dirty;
    _ownerId = ownerId;
}

void Fork::Take(int ownerId) {
    _ownerId = ownerId;
    _isTaken = true;
}

void Fork::Use(){
    _mutex.lock();
    _forkState = ForkState::dirty;
}

void Fork::PutDown() {
    _mutex.unlock();
    _isTaken = false;
}

void Fork::CleanUp() {
    _forkState = ForkState::clean;
}

void Fork::Request(int id) {
    if(_forkState == ForkState::dirty){
        //mutexa dolozyc
        this->CleanUp();
        this->Take(id);
    }
    else{
        // czekaj az skonczy jesc
        //tutaj bedzie condition variable ktory zwolni sie gdy wlasciciel odłozy widelec
    }
}