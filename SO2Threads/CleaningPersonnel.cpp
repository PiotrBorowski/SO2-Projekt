//
// Created by borowski on 29.05.19.
//

#include <thread>
#include <cstdlib>
#include <unistd.h>
#include "CleaningPersonnel.h"

void CleaningPersonnel::CleanOperatingRoom(OperatingRoom *operatingRoom) {

    operatingRoom->Request(this->_id);
    _state = PersonelState::cleaningOR;

    _progress = 10;
    for (int i = 0; i < 10; ++i) {
        _progress--;
        usleep(300000 + std::rand() % 100000);
    }

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
