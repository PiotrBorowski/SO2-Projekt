#include <iostream>
#include <thread>
#include <vector>
#include "Philosopher.h"
#include "Fork.h"

using namespace std;


vector<Philosopher*> philosophers;


void PhilosopherLifeCycle(Philosopher* philosopher)
{
    printf("mysle\n");
    philosopher->Think();
    philosopher->PickupFork();
    printf("jem\n");
    philosopher->Eat();
    philosopher->PutDownFork();
}

const int THREAD_NUMBER = 5;

int main()
{
    thread threads[THREAD_NUMBER];

    for(int i = 0; i<THREAD_NUMBER; i++){
        philosophers.push_back(new Philosopher(new Fork(), new Fork()));
    }

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i] = thread(PhilosopherLifeCycle, philosophers[i]);
    }

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i].join();
    }
    
    return 0;
}

