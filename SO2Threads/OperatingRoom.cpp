//
// Created by borowski on 29.05.19.
//

#include <mutex>
#include "OperatingRoom.h"

void OperatingRoom::Request(int id) {
    if(_ownerId != id) {
        if (_state == State::clean) {
            SetConditionVariable();
        }

        std::lock_guard<std::mutex> lock(_mutex);

        this->CleanUp();
        this->Take(id);
    }
}


void OperatingRoom::SetConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.wait(lock);
}

void OperatingRoom::UnlockConditionVariable() {
    std::unique_lock<std::mutex> lock(_conditionMutex);
    _condition_variable.notify_all();
}

void OperatingRoom::CleanUp() {
    _state = State::clean;
}

void OperatingRoom::Exit() {
    _state = State::dirty;
    _ownerId = -1;
    _mutex.unlock();
    UnlockConditionVariable();
}

void OperatingRoom::Take(int ownerId) {
    _ownerId = ownerId;
}

void OperatingRoom::Use() {
    _mutex.lock();
}

short OperatingRoom::GetOwnerId() {
    return _ownerId;
}

OperatingRoom::OperatingRoom() {
    _state = State::dirty;
}
