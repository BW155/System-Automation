//
// Created by LarsLinux on 16-12-19.
//

#ifndef DOOR_H
#define DOOR_H

#include "../Socket/Socket.h"
#include "domObject.h"
#include "pillar.h"

class Door: public domObject{
private:
    int servo;
    bool buttonOutside;
    bool buttonInside;
    bool ledOutside;
    bool ledInside;
    Pillar* pillar;
    char* wemosMessage();
    json pythonMessage();
    void toLogFile();
public:
    Door(const char*, webSocket*, TimeClass*);
    void setPillarPointer(Pillar*);
    void update();

};
#endif //DOOR_H