//
// Created by borowski on 29.05.19.
//

#include "Doctor.h"

void Doctor::Request(int id) {
    if(_ownerId != id) {
        if (_state == State::clean) {
            SetConditionVariable();
        }

        std::lock_guard<std::mutex> lock(_mutex);

        this->CleanUp();
        this->Take(id);
    }
}


void Doctor::SetConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.wait(lock);
}

void Doctor::UnlockConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.notify_one();
}

void Doctor::CleanUp() {
    _state = State::clean;
}

void Doctor::Bye() {
    _state = State::dirty;
    _ownerId = -1;
    _mutex.unlock();
    UnlockConditionVariable();
}

void Doctor::Take(int ownerId) {
    _ownerId = ownerId;
}

void Doctor::Use() {
    _mutex.lock();
}

short Doctor::GetOwnerId() {
    return _ownerId;
}

Doctor::Doctor() {
    _state = State::dirty;
    _ownerId = -1;
}