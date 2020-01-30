//
// Created by LarsLinux on 16-12-19.
//

#ifndef BED_H
#define BED_H

#include "../Socket/Socket.h"
#include "domObject.h"

class Bed: public domObject {
private:
    bool led;
    int forceSensor;
    int updateForce;
    bool button;
    int counter;
    bool buttonPressed;
    int startTime;
    int startTimeLed;
    int startTimeAwake;
    bool ledTimerStarted;
public:
    Bed(const char*, webSocket*, TimeClass*);
    char* wemosMessage();
    json pythonMessage();
    void update();
};
#endif //SOCKET_BED_
