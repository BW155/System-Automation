#include <time.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <strings.h>
#include <stdlib.h>


#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_

class TimeClass{
    public:
        void autoIncreaseTime();
        void setTime();
        int  getTime(int);
        void initTimeValues();
    private:
        int minutes;
        int hours;
        int seconds;
        int timeMultiplier;
};

#endif