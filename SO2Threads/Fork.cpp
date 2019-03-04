//
// Created by borowski on 03.03.19.
//

#include "Fork.h"

void Fork::Use() {
    _mutex.lock();
    printf("zablokowany");
    _mutex.unlock();
}