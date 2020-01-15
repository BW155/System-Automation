//
// Created by LarsLinux on 16-12-19.
//

#ifndef PILLAR_H
#define PILLAR_H

#include "../Socket/Socket.h"
#include "domObject.h"

class Pillar : public domObject{
private:
    int gassensor;
    bool button;
    bool led;
    bool buzzer;
    Socket socket;
    void toLogFile();
public:
    Pillar(const char*, webSocket*);
    bool get_buzzer();
    char* wemosMessage();
    json pythonMessage();
    void update() override;
};
#endif //SOCKET_BED_H
