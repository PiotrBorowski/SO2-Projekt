#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <ncurses.h>

#include "Philosopher.h"
#include "Fork.h"

using namespace std;


vector<Philosopher*> philosophers;
int rows = 0;
int columns = 0;

void PhilosopherLifeCycle(Philosopher* philosopher, std::atomic<bool>& running)
{
    while(running){
        philosopher->Think();
        philosopher->PickupFork();
        philosopher->Eat();
        philosopher->PutDownFork();
    }
}

const int THREAD_NUMBER = 5;

int main()
{
    srand(time(NULL));

    initscr();
    refresh();
    getmaxyx(stdscr, rows, columns);
    printw("DINNING PHILOSOPHERS");


    thread threads[THREAD_NUMBER];

    for(int i = 0; i<THREAD_NUMBER; i++){
        std::string name("philosopher");
        philosophers.push_back(new Philosopher(new Fork(), new Fork(), name + std::to_string(i)));
    }

    std::atomic<bool> running{true};

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i] = thread(PhilosopherLifeCycle, philosophers[i], std::ref(running));
    }

    for(int i = 0; i<THREAD_NUMBER; i++){

        mvprintw(i+1,0,philosophers[i]->GetName().c_str());
    }


    int esc = 0;
    do{
        noecho();
        esc = getch();
    }
    while(esc != 27);

    running = false;

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i].join();
    }

    endwin();

    return 0;
}

