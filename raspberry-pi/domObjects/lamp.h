// Created by LarsLinux on 16-12-19.
//

#ifndef LAMP_H
#define LAMP_H

#include "../Socket/Socket.h"
#include "domObject.h"

class Lamp: public domObject {
private:
    bool led;
    bool motionSensor;
    int startTime;
    char* wemosMessage();
    json pythonMessage();
public:
    Lamp(const char* IP, webSocket *s, TimeClass *t);
    void stuurLamp();
    void update();
};

#endif //LAMP_H
