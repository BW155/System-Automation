//
// Created by LarsLinux on 16-12-19.
//

#ifndef WALL_H
#define WALL_H

#include "../Socket/Socket.h"
#include "domObject.h"

class Wall: public domObject {
private:
    u_int16_t led;
    bool window;
    int dimmer;
    int LDR;
public:
    Wall(const char*, webSocket*, TimeClass *);
    char* wemosMessage();
    json pythonMessage();
    void update();
};
#endif //WALL_H
