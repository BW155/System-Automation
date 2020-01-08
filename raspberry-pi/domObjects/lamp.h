// Created by LarsLinux on 16-12-19.
//

#ifndef RASPBERRY_PI_BED_H
#define RASPBERRY_PI_BED_H

#include "../Socket/Socket.h"
#include "domObject.h"
#include "../timeKeeper.h"


class Lamp: public domObject {
public:
    Lamp(const char* IP, webSocket *s, TimeClass *t);
    void stuurLamp();
    void update();


private:
    bool led;
    bool motionSensor;
    Socket socket;
    int startTime;
    char* wemosMessage();
    json pythonMessage();
};


#endif //RASPBERRY_PI_BED_H