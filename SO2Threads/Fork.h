//
// Created by borowski on 03.03.19.
//

#ifndef SO2_PROJEKT_FORK_H
#define SO2_PROJEKT_FORK_H
#include <mutex>
#include <condition_variable>

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
    void Request(int id);

private:
    void SetConditionVariable();
    void UnlockConditionVariable();

    std::mutex _mutex;
    std::mutex _conditionMutex;
    std::condition_variable _condition_variable;
    bool _isTaken = false;
    ForkState _forkState;
    int _ownerId;
};


#endif //SO2_PROJEKT_FORK_H
