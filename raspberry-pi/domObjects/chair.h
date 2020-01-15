//
// Created by LarsLinux on 16-12-19.
//

#ifndef CHAIR_H
#define CHAIR_H

#include "../Socket/Socket.h"
#include "domObject.h"

class Chair : public domObject {
private:
    bool led;
    int forceSensor,start_time_30min_check,start_time_max_massage;
    int start_timeOut;
    bool vibrator, button, timeOut;
    int startTimeMedication;
    int updateForce;
    int counter;
    int startTime;
    int lastNotification;
    char* wemosMessage();
    json pythonMessage();
    void updateAttributes(json result);
    void toLogFile();
public:
    void update();
    Chair(const char*, webSocket*, TimeClass*);

};
#endif //CHAIR_H
