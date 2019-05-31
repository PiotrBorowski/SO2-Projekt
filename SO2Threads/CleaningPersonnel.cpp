//
// Created by borowski on 29.05.19.
//

#include <thread>
#include <cstdlib>
#include <unistd.h>
#include "CleaningPersonnel.h"

void CleaningPersonnel::CleanOperatingRoom(OperatingRoom *operatingRoom) {

    operatingRoom->Request(this->_id);
    operatingRoom->Use();
    _state = PersonelState::cleaningOR;

    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }
    operatingRoom->Exit();
}

void CleaningPersonnel::CleanCorridor() {
    _state = PersonelState::cleaningCorridor;
    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }
}

int CleaningPersonnel::GetId() {
    return _id;
}

PersonelState CleaningPersonnel::GetState() {
    return _state;
}

CleaningPersonnel::CleaningPersonnel(short id) {
    _id = id;
}

int CleaningPersonnel::GetProgress() {
    return _progress;
}
