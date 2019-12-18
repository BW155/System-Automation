//
// Created by LarsLinux on 16-12-19.
//

#ifndef DOOR_H
#define DOOR_H

#include "../Socket/Socket.h"
#include "domObject.h"
#include "pillar.h"

class Socket;

class Door: public domObject{
private:
    int servo;
    bool buttonOutside;
    bool buttonInside;
    bool ledOutside;
    bool ledInside;
    domObject* pillar;
    char* wemosMessage(bool, bool, int);
    json pythonMessage();
public:
    Door(const char*, webSocket*);
    //void setPillarPointer(Pillar*);
    void update();

};
#endif //DOOR_H
