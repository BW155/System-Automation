//
// Created by LarsLinux on 16-12-19.
//

#ifndef SOCKET_BED_H
#define SOCKET_BED_H

#include "../Socket/Socket.h"
#include <iostream>
#include <string>
#include "../json/json.hpp"
#include "../Socket/webSocket.h"
#include "domObject.h"
using namespace std;

class door;

class Pillar : public domObject{
private:
    int gassensor;
    bool button;
    bool led;
    bool buzzer;
    Socket socket;
public:
    Pillar(char*, webSocket*);
    bool get_buzzer();
    virtual char* wemosMessage(json){};
    virtual char* pythonMessage(bool, bool){};
    virtual void update();
};
#endif //SOCKET_BED_H
