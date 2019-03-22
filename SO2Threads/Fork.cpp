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
    //_mutex.lock();
}

void Fork::PutDown() {
    _isTaken = false;
    _forkState = ForkState::dirty;
    //_mutex.unlock();
    UnlockConditionVariable();
}

void Fork::CleanUp() {
    _forkState = ForkState::clean;
}

void Fork::SetConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.wait(lock);
}

void Fork::UnlockConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.notify_all();
}

void Fork::Request(int id) {
    while(_ownerId != id){
        if(_forkState == ForkState::clean){
            SetConditionVariable();
        }
        else{
            std::lock_guard<std::mutex> lock(_mutex);

            this->CleanUp();
            this->Take(id);
        }
    }

}