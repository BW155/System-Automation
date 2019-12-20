//
// Created by LarsLinux on 16-12-19.
//

#ifndef WALL_H
#define WALL_H

#include "../Socket/Socket.h"
#include "domObject.h"

class Socket;

class Wall: public domObject {
private:
    u_int8_t led;
    bool window;
    int dimmer;
    int LDR;
public:
    Wall(char*, webSocket*);
    char* wemosMessage();
    char* pythonMessage();
    void update();
};
#endif //WALL_H
