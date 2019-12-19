//
// Created by Zep on 16-12-19.
//

#ifndef SOCKET_BED_H
#define SOCKET_BED_H


#include "domObject.h"
#include "../Socket/Socket.h"
#include "../Socket/webSocket.h"
#include "json/json.hpp"

class fridge : public domObject{
private:
    bool cooling;
    int thermometer1;
    int thermometer2;
    int openClose;
    fridge(char * IP, webSocket *s);
    char* wemosMessage(bool cooling);
public:
    void update() override;
};
#endif //SOCKET_BED_H
