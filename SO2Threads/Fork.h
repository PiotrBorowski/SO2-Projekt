//
// Created by borowski on 03.03.19.
//

#ifndef SO2_PROJEKT_FORK_H
#define SO2_PROJEKT_FORK_H
#include <mutex>

enum ForkState{
    clean,
    dirty
};


class Fork {
public:
    Fork(int ownerId);
    void Take(int ownerId);
    void Use();
    void PutDown();
    void CleanUp();

private:
    std::mutex _mutex;
    bool _isTaken = false;
    ForkState _forkState;
    int _ownerId;
};


#endif //SO2_PROJEKT_FORK_H
