//
// Created by Zep on 16-12-19.
//

#include "domObject.h"
#include "../Socket/Socket.h"
#include "../Socket/webSocket.h"
#include "../json/json.hpp"


#ifndef FRIDGE_H
#define FRIDGE_H

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
    int start_time;
public:
    void update() override;
    Fridge(const char * IP, webSocket *s, TimeClass *t);
};
#endif //SOCKET_BED_H