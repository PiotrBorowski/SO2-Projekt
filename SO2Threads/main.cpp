#include <iostream>
#include <thread>
#include <vector>
#include "Philosopher.h"
#include "Fork.h"

using namespace std;


vector<Philosopher*> philosophers;


void PhilosopherLifeCycle(Philosopher* philosopher)
{
    std::cout << philosopher->GetName() + ": mysle\n";
    philosopher->Think();
    philosopher->PickupFork();
    std::cout << philosopher->GetName() + ": jem\n";
    philosopher->Eat();
    philosopher->PutDownFork();
}

const int THREAD_NUMBER = 5;

int main()
{
    thread threads[THREAD_NUMBER];

    for(int i = 0; i<THREAD_NUMBER; i++){
        std::string name("philosopher");
        philosophers.push_back(new Philosopher(new Fork(), new Fork(), name + std::to_string(i)));
    }

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i] = thread(PhilosopherLifeCycle, philosophers[i]);
    }

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i].join();
    }
    
    return 0;
}

