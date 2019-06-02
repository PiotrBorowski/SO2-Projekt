//
// Created by borowski on 29.05.19.
//

#include "Drug.h"


void Drug::Request(int id) {
    if(_ownerId != id) {
        if (_state == State::clean) {
            SetConditionVariable();
        }

        std::lock_guard<std::mutex> lock(_mutex);

        this->CleanUp();
        this->Take(id);
    }
}

void Drug::SetConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.wait(lock);
}

void Drug::UnlockConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.notify_all();
}

void Drug::CleanUp() {
    _state = State::clean;
}

void Drug::GetBack() {
    _state = State::dirty;
    _ownerId = -1;
    _mutex.unlock();
    UnlockConditionVariable();
}

void Drug::Take(int ownerId) {
    _ownerId = ownerId;
}

void Drug::Use() {
    _mutex.lock();
}

short Drug::GetOwnerId() {
    return _ownerId;
}

Drug::Drug(){
    _state = State::dirty;
}
