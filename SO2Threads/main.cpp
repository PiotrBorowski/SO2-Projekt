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

const int THREAD_NUMBER_PERSONNEL = 2;
const int THREAD_NUMBER_PATIENT = 8;
const int NURSES_NUMBER = 4;
const int DOCTORS_NUMBER = 7;
const int DRUGS_NUMBER = 5;


void PatientLifeCycle(Patient* patient, std::atomic<bool>& running)
{
    while (running)
    {
        Doctor* doctor;

        Action result;

        do{
            int index = std::rand() % doctors.size();
            patient->SetDoctorId(index);
            doctor = doctors[index];
            result = patient->VisitDoctor(doctor);
        } while(result == Action::VisitDoctor);


int nurseId;
        switch(result)
        {
            case Action::TakeDrug:
                //podanie leku u pielegniarki
                nurseId = std::rand() % nurses.size();
                patient->SetNurseId(nurseId);
                patient->TakeDrug(nurses[nurseId], drugs[std::rand() % drugs.size()]);
                break;

            case Action::UndergoOperation:
                //poddanie sie operacji
                nurseId = std::rand() % nurses.size();
                patient->SetNurseId(nurseId);
                patient->UndergoOperation(doctor, nurses[nurseId], operatingRoom);
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
        mvprintw(0, 0, "Operating room:");
        mvprintw(0, 33, std::to_string(operatingRoom->GetOwnerId()).c_str());
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

        mvprintw(end, 0, "Patients:");
        for(int i = 0; i<THREAD_NUMBER_PATIENT; i++){
            mvprintw(end + i+1,0, std::to_string(patients[i]->GetId()).c_str());

            std::string doctorString = "Visiting Doctor";
            std::string operatedString = "Being operated";

            switch(patients[i]->GetState())
            {
                case Action::VisitDoctor :
                    attron(COLOR_PAIR(2));

                    mvprintw(end + i+1,15,  doctorString.append(std::to_string(patients[i]->GetDoctorId())).c_str());

                    attroff(COLOR_PAIR(2));
                    break;
                case Action::UndergoOperation :
                    attron(COLOR_PAIR(4));
                    mvprintw(end + i+1,15, operatedString.append(std::to_string(patients[i]->GetDoctorId())).c_str());

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
                    mvprintw(end + i+1,40,"Being operated");
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

        end += NURSES_NUMBER + 1;

        mvprintw(end ,0, "Drugs (ownerId)");

        for(int i = 0; i<DRUGS_NUMBER; i++){
            mvprintw(end + 1 + i,0, std::to_string(drugs[i]->GetOwnerId()).c_str());
        }

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

    for(int i = 0; i<THREAD_NUMBER_PATIENT; i++){
        delete patients[i];
    }

    for(int i = 0; i<THREAD_NUMBER_PERSONNEL; i++){
        delete cleaningPersonnel[i];
    }

    endwin();

    return 0;
}

