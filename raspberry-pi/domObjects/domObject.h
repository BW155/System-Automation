//
// Created by LarsLinux on 18-12-19.
//

#ifndef RASPBERRY_PI_DOMOBJECT_H
#define RASPBERRY_PI_DOMOBJECT_H

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
//    virtual char* wemosMessage() = 0;
//    virtual char* pythonMessage() = 0;
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
