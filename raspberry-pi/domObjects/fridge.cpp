//
// Created by Zep
//

#define doorIsOpen 0
#define doorIsClosed 1

#include "fridge.h"
#include "../json/json.hpp"
#include <fstream>

using json = nlohmann::json;

// constructor for fridge
Fridge::Fridge(const char * IP, webSocket *w, TimeClass *t) : domObject(w, t, 6){
    cooling = false;
    thermometer1 = 0;
    thermometer2 = 0;
    openClose = 0 ;
    state = false;
    startTime = 0;
    Socket temp(6,IP);
    domObject::wemos = temp;
}

// Communicates with webserver and wemos, updates sensors and actuators accordingly
void Fridge::update(){

    string log;

    // char* for storing result and message
    char *result;

    // json for storing results in json format
    json jsonResult;

    // int for storing time
    int currentTime;

    // increase the time object
    domObject::timeObj->autoIncreaseTime();

    //Current time in seconds
    currentTime = domObject::timeObj->getTimeSeconds();

    // send message to wemos and receive sensors
    result = wemos.sendReceive(wemosMessage());

    // check if wemos didnt send an empty message
    if (result == nullptr) {
        cout<<"error receiving"<<endl;
    }
    else {
        // change to json, update attributes
        jsonResult = toJson(result);
        if (jsonResult["error"] != "NoDataReceived") {
            updateAttributes(jsonResult, &log);
        }
    }

    // Cool when fridge is closed
    if (openClose == doorIsClosed){
        startTime = currentTime;
        cooling = true;
    }

    // when the fridge is opened for 5 seconds, stop cooling and send notification
    if((currentTime-startTime) > (5 * 60)){
        cooling = false;
        json message = {
                {"type", 4},
                {"id", 4}
        };
        python->sendNotification(toCharArray(message));
        log += "koelkast uit | ";

    }

    //send all sensors and actuators to webserver
    python->sendAll(6,pythonMessage());

    logToFile(domObject::timeObj, log);
}

// make message for wemos
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

// make message for webserver
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

// function to update attributes
void Fridge::updateAttributes(json result, string *log){
    thermometer1 = result["sensors"]["thermometer1"];
    thermometer2 = result["sensors"]["thermometer2"];
    if (openClose != result["sensors"]["openClose"]) {
        if (result["sensors"]["openClose"] == 1) {
            *log += "deur is open | ";
        }
        else {
            *log += "deur is dicht | ";
        }
    }
    openClose = result["sensors"]["openClose"] == 1;

}

