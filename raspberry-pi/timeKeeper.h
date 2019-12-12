#include <time.h>
#include <iostream>
#include <stdlib.h>


#ifndef TIMEKEEPER_H_
#define TIMEKEEPER_H_

class TimeClass{
    public:
        void autoIncreaseTime();
        void manualIncreaseTime();
        void manualDecreaseTime();
        void initTimeValues();
    private:
        int minutes;
        int hours;
        int seconds;
        int timeMultiplier;
};

#endif