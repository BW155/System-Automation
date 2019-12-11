#ifndef TIME_H_
#define TIME_H_

class TimeClass{
    public:
        void autoIncreaseTime();
        void manualIncreaseTime();
        void manualDecreaseTime();

    private:
        int minutes;
        int hours;
        int seconds;
        int timeMultiplier;
};

#endif