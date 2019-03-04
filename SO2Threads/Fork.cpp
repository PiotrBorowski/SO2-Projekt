//
// Created by borowski on 03.03.19.
//

#include "Fork.h"

Fork::Fork(){

}

void Fork::Take() {
    _mutex.lock();
}

void Fork::PutDown() {
    _mutex.unlock();
}