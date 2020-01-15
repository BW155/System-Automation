//
// Created by Zep on 16-12-19.
//

#define doorIsOpen 0
#define doorIsClosed 1

#include "fridge.h"
#include "../json/json.hpp"
#include <fstream>

using json = nlohmann::json;

Fridge::Fridge(const char * IP, webSocket *w, TimeClass *t) : domObject(w, t, 6){
    cooling = false;
    thermometer1 = 0;
    thermometer2 = 0;
    openClose = 0 ;
    state = false;
    startTime = 0;

    Socket temp(6,"Fridge",IP);
    domObject::wemos = temp;
}

void Fridge::update(){
    //Logic for the fridge
    char *result;
    json jsonResult;
    int currentTime;

    domObject::timeObj->autoIncreaseTime();

    //Ask for current time in seconds
    currentTime = domObject::timeObj->getTimeSeconds();

    result = wemos.sendReceive(wemosMessage());
    jsonResult = toJson(result);
    updateAttributes(jsonResult);

    if (openClose == doorIsClosed){
        startTime = currentTime;
        cooling = true;
    }

    if((currentTime-startTime) > (5 * 60)){
        cooling = false;
        json message = {
                {"type", 4},
                {"id", 4}
        };
        python->sendNotification(toCharArray(message));

    }

    toLogFile();
}

char* Fridge::wemosMessage(){
    json message = {
            {"id",6},
            {"actuators", {
                          {"cooling", cooling}
                  }
            }
    };
    return toCharArray(message);
}

json Fridge::pythonMessage() {
    json message = {
            {"actuators", {
                           {"cooling", cooling}
                   }
            },
            {"sensors", {
                           {"thermometer1", thermometer1},
                           {"thermometer2", thermometer2},
                           {"openClose", openClose}
                   }
            }
    };
    return message;
}

void Fridge::updateAttributes(json result){
    thermometer1 = result["sensors"]["thermometer1"];
    thermometer2 = result["sensors"]["thermometer2"];
    openClose = result["sensors"]["openClose"] == 1;
    python->sendAll(6,pythonMessage());
}

void Fridge::toLogFile() {
    //log
    ofstream myfile;
    myfile.open("log.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << domObject::timeObj->getTimeString() << "Fridge: " << pythonMessage() << endl;
        if  (myfile.bad()) {
            cout<<"write failed"<<endl;
        }

    }
    else {
        cout<<"file not found"<<endl;
    }
    myfile.close();
}