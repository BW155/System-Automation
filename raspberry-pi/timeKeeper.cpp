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
    time_t curTime;
    static time_t prevTime;
    double diff_t;

    time(&curTime);

    if(prevTime != 0 )
        diff_t = difftime(curTime,prevTime);

    //Prevent huge diff_t value first time
    if(diff_t > 0 ){
        if(minutes >= 60){
            if(hours >= 23){
                hours = 0;
            }else{
                hours++;    
            }
            //Calculates the difference above 60 and resets minutes to this value
            int diff = minutes - 60;
            minutes = diff;
        }

        //Debug purposes
        cout << "hours: "  << hours   << endl;
        cout << "Minutes: "<< minutes << endl;
        cout << "seconds: "<< seconds << endl;
        cout << " " << endl;


        minutes += diff_t * timeMultiplier;
        //Seconds since january first 1970
    }
    prevTime = curTime;
}

void TimeClass::setTime(string TimeMultiplier, string Hours, string Minutes, string Seconds){
    //Cur means remain current value of given variable.
    if(TimeMultiplier == "cur" || Hours == "cur" || Minutes == "cur" || Seconds == "cur"){
        //Do nothing
    }
    if(TimeMultiplier != "cur")
        timeMultiplier = stoi(TimeMultiplier);
    if(Hours != "cur")
        hours   = stoi(Hours);
    if(Minutes != "cur")
        minutes = stoi(Minutes);
    if(Seconds != "cur")
        seconds = stoi(Seconds);

}

int* TimeClass::getTime(){
    static int arr[3];
    arr[0] = hours;
    arr[1] = minutes;
    arr[2] = seconds;

    return arr;
}