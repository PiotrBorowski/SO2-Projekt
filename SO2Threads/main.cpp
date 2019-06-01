#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <ncurses.h>
#include <mutex>
#include <unistd.h>
#include "Patient.h"
#include "CleaningPersonnel.h"

using namespace std;


vector<CleaningPersonnel*> cleaningPersonnel;
vector<Patient*> patients;
vector<Nurse*> nurses;
vector<Drug*> drugs;
vector<Doctor*> doctors;
OperatingRoom* operatingRoom = new OperatingRoom();

std::mutex displayMutex;

const int THREAD_NUMBER_PERSONNEL = 3;
const int THREAD_NUMBER_PATIENT = 5;
const int NURSES_NUMBER = 6;
const int DOCTORS_NUMBER = 4;
const int DRUGS_NUMBER = 5;


void PatientLifeCycle(Patient* patient, std::atomic<bool>& running)
{
    //TODO: dobieranie doktorow

    while (running)
    {
        Doctor* doctor = doctors[std::rand() % doctors.size()];

        Action result;

        do{
            doctor = doctors[std::rand() % doctors.size()];
            result = patient->VisitDoctor(doctor);
        } while(result == Action::VisitDoctor);


        switch(result)
        {
            case Action::TakeDrug:
                //podanie leku u pielegniarki
                patient->TakeDrug(nurses[std::rand() % nurses.size()], drugs[std::rand() % drugs.size()]);
                break;

            case Action::UndergoOperation:
                //poddanie sie operacji
                patient->UndergoOperation(doctor, nurses[std::rand() % nurses.size()], operatingRoom);
                break;
        }
    }
}

void CleaningPersonnelLifeCycle(CleaningPersonnel* cleaningPersonnel, OperatingRoom* operatingRoom, std::atomic<bool>& running)
{
    while(running)
    {
        cleaningPersonnel->CleanCorridor();
        cleaningPersonnel->CleanOperatingRoom(operatingRoom);
    }
}

void Display(std::atomic<bool>& displaying)
{
    while(displaying)
    {
        int end;
        clear();
        displayMutex.lock();
        mvprintw(0, 10, std::to_string(operatingRoom->GetOwnerId()).c_str());
        for(int i = 0; i<THREAD_NUMBER_PERSONNEL; i++){
            mvprintw(i+1,0, std::to_string(cleaningPersonnel[i]->GetId()).c_str());

            switch(cleaningPersonnel[i]->GetState())
            {
                case PersonelState::cleaningOR :
                    attron(COLOR_PAIR(2));
                    mvprintw(i+1,15,"cleaning OPERATING ROOM");
                    attroff(COLOR_PAIR(2));
                    break;
                case PersonelState::cleaningCorridor:
                    attron(COLOR_PAIR(1));
                    mvprintw(i+1,15,"cleaning Corridor");
                    attroff(COLOR_PAIR(1));
                    break;
            }
            mvprintw(i+1,40,std::to_string(cleaningPersonnel[i]->GetProgress()).c_str());
            end = i + 2;
        }

        for(int i = 0; i<THREAD_NUMBER_PATIENT; i++){
            mvprintw(end + i+1,0, std::to_string(patients[i]->GetId()).c_str());

            switch(patients[i]->GetState())
            {
                case Action::VisitDoctor :
                    attron(COLOR_PAIR(2));
                    mvprintw(end + i+1,15,"Visiting Doctor");
                    attroff(COLOR_PAIR(2));
                    break;
                case Action::UndergoOperation :
                    attron(COLOR_PAIR(4));
                    mvprintw(end + i+1,15,"Getting operated");
                    attroff(COLOR_PAIR(4));
                    break;
                case Action::TakeDrug :
                    attron(COLOR_PAIR(3));
                    mvprintw(end + i+1,15,"Taking drug");
                    attroff(COLOR_PAIR(3));
                    break;
                case Action::None:
                    attron(COLOR_PAIR(1));
                    mvprintw(end + i+1,15,"Nothing");
                    attroff(COLOR_PAIR(1));
                    break;
            }

            switch(patients[i]->GetNextState())
            {
                case Action::VisitDoctor :
                    attron(COLOR_PAIR(2));
                    mvprintw(end + i+1,40,"Visiting Doctor");
                    attroff(COLOR_PAIR(2));
                    break;
                case Action::UndergoOperation :
                    attron(COLOR_PAIR(4));
                    mvprintw(end + i+1,40,"Getting operated");
                    attroff(COLOR_PAIR(4));
                    break;
                case Action::TakeDrug :
                    attron(COLOR_PAIR(3));
                    mvprintw(end + i+1,40,"Taking drug");
                    attroff(COLOR_PAIR(3));
                    break;
                case Action::None:
                    attron(COLOR_PAIR(1));
                    mvprintw(end + i+1,40,"Nothing");
                    attroff(COLOR_PAIR(1));
                    break;
            }

            mvprintw(end + i+1,33,std::to_string(patients[i]->GetProgress()).c_str());
        }
        end = THREAD_NUMBER_PATIENT + THREAD_NUMBER_PATIENT + 1;

        mvprintw(end ,0, "Doctors (ownerId)");

        for(int i = 0; i<DOCTORS_NUMBER; i++){
            mvprintw(end+ 1 + i,0, std::to_string(doctors[i]->GetOwnerId()).c_str());

        }

        end += DOCTORS_NUMBER + 1;

        mvprintw(end ,0, "Nurses (ownerId)");

        for(int i = 0; i<NURSES_NUMBER; i++){
            mvprintw(end + 1 + i,0, std::to_string(nurses[i]->GetOwnerId()).c_str());

        }

//
//            mvprintw(THREAD_NUMBER+2,   0,  "Forks");
//            mvprintw(THREAD_NUMBER+2,   15,  "Owner");
//            mvprintw(THREAD_NUMBER+2,   30,  "State");
//            mvprintw(THREAD_NUMBER+2,   45,  "is taken?");
//            mvprintw(THREAD_NUMBER+3+i, 0,  std::to_string(i).c_str());
//            mvprintw(THREAD_NUMBER+3+i, 15, std::to_string(forks[i]->GetOwnerId()).c_str());
//
//            switch(forks[i]->GetState())
//            {
//                case ForkState::dirty:
//                    attron(COLOR_PAIR(3));
//                    mvprintw(THREAD_NUMBER+3+i, 30, forks[i]->GetStateString().c_str());
//                    attron(COLOR_PAIR(3));
//                    break;
//                case ForkState::clean:
//                    attron(COLOR_PAIR(4));
//                    mvprintw(THREAD_NUMBER+3+i, 30, forks[i]->GetStateString().c_str());
//                    attron(COLOR_PAIR(4));
//                    break;
//                default:
//                    break;
//            }
//
//            if(forks[i]->GetIsTaken())
//            {
//                attron(COLOR_PAIR(2));
//                mvprintw(THREAD_NUMBER+3+i, 45, "yes");
//                attroff(COLOR_PAIR(2));
//            }
//            else{
//                attron(COLOR_PAIR(1));
//                mvprintw(THREAD_NUMBER+3+i, 45, "no");
//                attroff(COLOR_PAIR(1));
//            }
        displayMutex.unlock();
        refresh();

        usleep(10000);
    }
}


int main()
{
    srand(time(NULL));

    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    refresh();





    thread threadsPersonnel[THREAD_NUMBER_PERSONNEL];
    thread threadsPatients[THREAD_NUMBER_PATIENT];
















    //pierwszy i drugi widelec jest dla filozofa0
//    forks.push_back(new Fork(0));
//    for(int i = 0; i<THREAD_NUMBER-1; i++){
//            forks.push_back(new Fork(i));
//    }
//
//    for(int i = 0; i<THREAD_NUMBER-1; i++){
//            philosophers.push_back(new Philosopher(forks[i+1], forks[i], i));
//    }
    // ostatnie filozof ma dostep do widelca pierwszego i ostatniego
   // philosophers.push_back(new Philosopher(forks[0], forks[THREAD_NUMBER-1], THREAD_NUMBER-1));


    std::atomic<bool> running{true};

//    for(int i = 0; i<THREAD_NUMBER; i++){
//        threads[i] = thread(PhilosopherLifeCycle, philosophers[i], std::ref(running));
//    }

    for(int i = 0; i<DOCTORS_NUMBER; i++){
        doctors.push_back(new Doctor());
    }

    for(int i = 0; i<NURSES_NUMBER; i++){
        nurses.push_back(new Nurse());
    }

    for(int i = 0; i<DRUGS_NUMBER; i++){
        drugs.push_back(new Drug());
    }

    for(int i = 0; i<THREAD_NUMBER_PATIENT; i++){
        Patient* patient = new Patient(i+1);
        patients.push_back(patient);
        threadsPatients[i] = thread(PatientLifeCycle, patient, std::ref(running));
    }


    for(int i = 0; i<THREAD_NUMBER_PERSONNEL; i++){
        CleaningPersonnel* personnel = new CleaningPersonnel(100 + i+1);
        cleaningPersonnel.push_back(personnel);
        threadsPersonnel[i] = thread(CleaningPersonnelLifeCycle, personnel, operatingRoom, std::ref(running));
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

    for(int i = 0; i<THREAD_NUMBER_PERSONNEL; i++){
        threadsPersonnel[i].join();
    }

    for(int i = 0; i<THREAD_NUMBER_PATIENT; i++){
        threadsPatients[i].join();
    }

    displayThread.join();

//    for(int i = 0; i<THREAD_NUMBER; i++){
//        delete philosophers[i];
//    }

    endwin();

    return 0;
}

