#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <ncurses.h>
#include <mutex>
#include <unistd.h>
#include "Philosopher.h"
#include "Fork.h"

using namespace std;


vector<Philosopher*> philosophers;
vector<Fork*> forks;
const int THREAD_NUMBER = 5;

void PhilosopherLifeCycle(Philosopher* philosopher, std::atomic<bool>& running)
{
    while(running)
    {
        philosopher->Think();
        philosopher->Eat();
    }
}

void Display(std::atomic<bool>& displaying)
{
    while(displaying)
    {
        clear();
        for(int i = 0; i<THREAD_NUMBER; i++){
            mvprintw(i+1,0,philosophers[i]->GetName().c_str());

            switch(philosophers[i]->GetState())
            {
                case State::eating:
                    mvprintw(i+1,15,"eating");
                    break;
                case State::thinking:
                    mvprintw(i+1,15,"thinking");
                    break;
            }

            mvprintw(i+1,40,std::to_string(philosophers[i]->GetProgress()).c_str());
        }
        refresh();

        usleep(10000);
    }
}


int main()
{
    srand(time(NULL));

    initscr();
    refresh();

    thread threads[THREAD_NUMBER];

    for(int i = 0; i<THREAD_NUMBER-1; i++){
            forks.push_back(new Fork(i));
    }

    //ostatni widelec nalezy takze do pierwszego filozofa
    forks.push_back(new Fork(0));


    for(int i = 0; i<THREAD_NUMBER-1; i++){
            philosophers.push_back(new Philosopher(forks[i+1], forks[i], i));
    }
    // ostatnie filozof ma dostep do widelca pierwszego i ostatniego
    philosophers.push_back(new Philosopher(forks[0], forks[THREAD_NUMBER-1], THREAD_NUMBER-1));


    std::atomic<bool> running{true};

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i] = thread(PhilosopherLifeCycle, philosophers[i], std::ref(running));
        usleep(1000000);
    }

    std::atomic<bool> displaying{true};

    std::thread displayThread(Display,std::ref(displaying));

    int esc = 0;
    do{
        noecho();
        esc = getch();
    }
    while(esc != 27);

    running = false;
    displaying = false;

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i].join();
    }
    displayThread.join();

    for(int i = 0; i<THREAD_NUMBER; i++){
        delete philosophers[i];
    }

    endwin();

    return 0;
}

