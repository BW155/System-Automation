//
// Created by LarsLinux on 18-12-19.
//

#include "domObject.h"
#include "../timeKeeper.h"

domObject::domObject(webSocket *s, int i) {
    python = s;
    wemos = Socket();
    id = i;
}
domObject::domObject(webSocket *s, TimeClass *t, int i) {
    python = s;
    wemos = Socket();
    timeObj = t;
    id = i;
}

json domObject::toJson(char* jsonString) {
    json jsonObj;
    std::stringstream(jsonString)>>jsonObj;
    return jsonObj;
}
char* domObject::toCharArray(json jsonObj) {
    std::string temp = jsonObj.dump();
    char *result = new char[temp.length()+1];
    strcpy(result, temp.c_str());
    return result;
}
TimeClass* domObject::getTimePointer() {return timeObj;}
