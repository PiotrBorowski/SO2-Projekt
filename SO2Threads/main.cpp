#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <ncurses.h>
#include <mutex>
#include "Philosopher.h"
#include "Fork.h"

using namespace std;


vector<Philosopher*> philosophers;
std::mutex displayMutex;
int rows = 0;
int columns = 0;
const int THREAD_NUMBER = 5;

void PhilosopherLifeCycle(Philosopher* philosopher, std::atomic<bool>& running)
{
    while(running){
        philosopher->Think();
        philosopher->PickupFork();
        philosopher->Eat();
        philosopher->PutDownFork();
    }
}

void Display(std::atomic<bool>& displaying){
    while(displaying){
        displayMutex.lock();
        clear();
        for(int i = 0; i<THREAD_NUMBER; i++){
            mvprintw(i+1,0,philosophers[i]->GetName().c_str());
            mvprintw(i+1,15,philosophers[i]->GetState().c_str());
        }
        refresh();
        displayMutex.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}


int main()
{
    srand(time(NULL));

    initscr();
    refresh();
    getmaxyx(stdscr, rows, columns);

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

