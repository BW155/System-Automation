//
// Created by LarsLinux on 18-12-19.
//

#include "domObject.h"

domObject::domObject(webSocket *s) {
    python = s;
    wemos = Socket();
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
