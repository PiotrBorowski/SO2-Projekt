//
// Created by borowski on 29.05.19.
//

#include "Nurse.h"

void Nurse::Request(int id) {
    if(_ownerId != id) {
        if (_state == State::clean) {
            SetConditionVariable();
        }

        std::lock_guard<std::mutex> lock(_mutex);

        this->CleanUp();
        this->Take(id);
    }
}

void Nurse::SetConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.wait(lock);
}

void Nurse::UnlockConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.notify_one();
}

void Nurse::CleanUp() {
    _state = State::clean;
}

void Nurse::Bye() {
    _state = State::dirty;
    _ownerId = -1;
    _mutex.unlock();
    UnlockConditionVariable();
}

void Nurse::Take(int ownerId) {
    _ownerId = ownerId;
}

void Nurse::Use() {
    _mutex.lock();
}

short Nurse::GetOwnerId() {
    return _ownerId;
}

Nurse::Nurse(){
    _state = State::dirty;
}
