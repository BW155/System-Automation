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
    if(diff_t > 0 ){
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

void TimeClass::setTime(){

}

int TimeClass::getTime(int x){
    if(x == 0)
        return seconds;
    if(x == 1)
        return hours;

    return 0;
}