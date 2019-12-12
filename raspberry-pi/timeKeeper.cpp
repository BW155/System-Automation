#include "timeKeeper.h"

using namespace std;


void TimeClass::initTimeValues(){
    minutes = 0;
    hours = 0;
    seconds = 0;
    
    //Increase every seconds with 15 minutes of simulation time
    timeMultiplier = 20;
}

void TimeClass::autoIncreaseTime(){
    time_t curTime, prevTime;
    double diff_t;

    curTime = time(NULL);

    diff_t = difftime(curTime,prevTime);

    //Prevent huge diff_t value first time
    if(diff_t > 0 && diff_t < 1000){
        if(minutes >= 60){
            if(hours >= 23){
                hours = 0;
            }else{
                hours++;
            }
            minutes = 0;
        }

        //Debug purposes
        
        cout << "hours: "  << hours   << endl;
        cout << "Minutes: "<< minutes << endl;
        cout << "seconds: "<< seconds << endl;
        cout << " " << endl;


        minutes += diff_t * timeMultiplier;
    }
    
    //Seconds since january first 1970
    prevTime = curTime;
}

//Moet nog geschreven worden. Het doel is om evt voor test purposes time zelf aan te passen
void TimeClass::manualIncreaseTime(){

}

void TimeClass::manualDecreaseTime(){

}