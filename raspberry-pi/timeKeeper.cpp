#include "timeKeeper.h"

using namespace std;

TimeClass::TimeClass(int t, int h, int m, int s){
    timeMultiplier = t;
    hours = h;
    minutes = m;
    seconds = s;
}

void TimeClass::autoIncreaseTime(){
    time_t curTime;
    static time_t prevTime;
    double diff_t;

    time(&curTime);

    //Calculate time difference between current time and previous time.
    if(prevTime != 0 )
        diff_t = difftime(curTime,prevTime);

    minutes += diff_t * timeMultiplier;
    
    if(diff_t > 0 ){
            if(minutes >= 120){
                //Calculates the amount of hours as minutes
                int temp = minutes/60;
                hours += temp;
                minutes -= temp * 60;

                if(hours >= 23)
                    hours = 0;
            }
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