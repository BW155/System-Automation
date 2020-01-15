//
// Created by Lars
//

#include "domObject.h"
#include "../timeKeeper.h"

// constructor for bbject without use of time
domObject::domObject(webSocket *s, int i) {
    python = s;
    wemos = Socket();
    id = i;
}

// constructor for object with use of time
domObject::domObject(webSocket *s, TimeClass *t, int i) {
    python = s;
    wemos = Socket();
    timeObj = t;
    id = i;
}

// function to create json from char *
json domObject::toJson(char* jsonString) {
    json jsonObj;
    std::stringstream(jsonString)>>jsonObj;
    return jsonObj;
}

// function to create char * from json
char* domObject::toCharArray(json jsonObj) {
    std::string temp = jsonObj.dump();
    char *result = new char[temp.length()+1];
    strcpy(result, temp.c_str());
    return result;
}

// function to get time pointer
TimeClass* domObject::getTimePointer() {return timeObj;}
