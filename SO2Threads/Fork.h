//
// Created by borowski on 03.03.19.
//

#ifndef SO2_PROJEKT_FORK_H
#define SO2_PROJEKT_FORK_H
#include <mutex>


class Fork {
public:
    void Use();
private:
    std::mutex _mutex;
};


#endif //SO2_PROJEKT_FORK_H
