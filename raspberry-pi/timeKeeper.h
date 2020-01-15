#include <time.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>


#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_

using namespace std;

class TimeClass{
    public:
        TimeClass(int, int, int, int);
        void autoIncreaseTime();
        void setTime(string, string, string, string);
        int*  getTime();
        int getTimeSeconds();
        string getTimeString();
    private:
        int minutes;
        int hours;
        int seconds;
        double timeMultiplier;
};

#endif