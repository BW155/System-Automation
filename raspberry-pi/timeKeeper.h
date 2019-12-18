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
        TimeClass(int, int, int, int);
        void autoIncreaseTime();
        void setTime(std::string, std::string, std::string, std::string);
        int*  getTime();
    private:
        int minutes;
        int hours;
        int seconds;
        double timeMultiplier;
};

#endif