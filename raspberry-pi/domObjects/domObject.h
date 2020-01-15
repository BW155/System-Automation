//
// Created by LarsLinux on 18-12-19.
//

#ifndef DOMOBJECT_H
#define DOMOBJECT_H

#include "../Socket/Socket.h"
#include "../Socket/webSocket.h"
#include "../json/json.hpp"
#include "../timeKeeper.h"

using json = nlohmann::json;

class domObject {
protected:
    Socket wemos;
    webSocket* python;
    TimeClass* timeObj;
public:
    int id;
    virtual void update() = 0;
    json toJson(char* jsonString);
    char* toCharArray(json jsonObj);
    domObject(webSocket *, int);
    domObject(webSocket *, TimeClass *, int);
    TimeClass *getTimePointer();
};
#endif //RASPBERRY_PI_DOMOBJECT_H
