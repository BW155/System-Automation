//
// Created by LarsLinux on 16-12-19.
//

#ifndef SOCKET_BED_H
#define SOCKET_BED_H

#include "../Socket/Socket.h"
#include "domObject.h"


class lamp: public domObject {
private:
bool motionSensor;
bool led;


public:
lamp(char * IP, webSocket *s);
void stuurLamp();
};
#endif //SOCKET_BED_H
