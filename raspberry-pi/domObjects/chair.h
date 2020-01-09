//
// Created by LarsLinux on 16-12-19.
//

#ifndef CHAIR_H
#define CHAIR_H

#include "domObject.h"
#include "../Socket/webSocket.h"
#include "../Socket/Socket.h"

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
    char* wemosMessage();
    json pythonMessage();
    void updateAttributes(json result);
public:
    void update();
    Chair(const char * IP, webSocket *s, TimeClass *t);

};
#endif //CHAIR_H
