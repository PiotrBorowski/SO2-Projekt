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
const int THREAD_NUMBER = 5;

void PhilosopherLifeCycle(Philosopher* philosopher, std::atomic<bool>& running)
{
    while(running)
    {
        philosopher->Think();
        philosopher->PickupFork();
        philosopher->Eat();
        philosopher->PutDownFork();
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

    for(int i = 0; i<THREAD_NUMBER; i++){
        std::string name("philosopher");
        philosophers.push_back(new Philosopher(new Fork(), new Fork(), name + std::to_string(i)));
    }


    std::atomic<bool> running{true};

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i] = thread(PhilosopherLifeCycle, philosophers[i], std::ref(running));
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

    endwin();

    return 0;
}

