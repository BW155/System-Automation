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
private:
    Socket wemos;
    webSocket* python;
    virtual char* wemosMessage() = 0;
    //virtual char* pythonMessage() = 0;
    TimeClass* timeObj;
    
public:
    virtual void update() = 0;
    json toJson(char* jsonString);
    char* toCharArray(json jsonObj);
    domObject(webSocket *s);
    virtual TimeClass* getTimePointer();
};
#endif //RASPBERRY_PI_DOMOBJECT_H
