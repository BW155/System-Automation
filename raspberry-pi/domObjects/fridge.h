//
// Created by Zep on 16-12-19.
//

#ifndef FRIDGE_H
#define FRIDGE_H

#include "../Socket/Socket.h"
#include "domObject.h"

class Fridge : public domObject{
private:
    bool cooling;
    int thermometer1;
    int thermometer2;
    int openClose;
    char* wemosMessage();
    json pythonMessage();
    void updateAttributes(json);
    bool state;
    int startTime;
    void toLogFile();
public:
    void update() override;
    Fridge(const char*, webSocket*, TimeClass*);
};
#endif //SOCKET_BED_H