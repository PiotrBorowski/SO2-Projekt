#include <iostream>
#include <thread>

using namespace std;

void print(){
    printf("z innego watku");
}

const int THREAD_NUMBER = 5;

int main()
{
    thread threads[THREAD_NUMBER];

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i] = thread(print);
    }

    for(int i = 0; i<THREAD_NUMBER; i++){
        threads[i].join();
    }
    
    return 0;
}
