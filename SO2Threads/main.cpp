#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

#include "Philosopher.h"
#include "Fork.h"

using namespace std;


vector<Philosopher*> philosophers;


void PhilosopherLifeCycle(Philosopher* philosopher, std::atomic<bool>& running)
{
    while(running){
        std::cout << philosopher->GetName() + ": mysle\n";
        philosopher->Think();
        philosopher->PickupFork();
        std::cout << philosopher->GetName() + ": jem\n";
        philosopher->Eat();
        philosopher->PutDownFork();
    }
}

const int THREAD_NUMBER = 5;

int main()
{
    srand(time(NULL));

    thread threads[THREAD_NUMBER];

    for(int i = 0; i<THREAD_NUMBER; i++){
        std::string name("philosopher");
        philosophers.push_back(new Philosopher(new Fork(), new Fork(), name + std::to_string(i)));
    }

    std::atomic<bool> running{true};

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i] = thread(PhilosopherLifeCycle, philosophers[i], std::ref(running));
    }


    char esc = 0;
    do{
        esc = getchar();
    }
    while(esc != 'e');

    running = false;

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i].join();
    }
    
    return 0;
}

