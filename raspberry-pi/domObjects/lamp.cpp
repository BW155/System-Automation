//
// Created by Ramon
//
#include "lamp.h"
#include "../json/json.hpp"

using json = nlohmann::json;

// constructor for lamp
Lamp::Lamp(const char * IP, webSocket *w, TimeClass *t): domObject(w, t, 3){
    startTime = 0;
    led = false;
    motionSensor = false;
    Socket temp(3,IP);
    domObject::wemos = temp;
}

// Communicates with webserver and wemos, updates sensors and actuators accordingly
void Lamp::update(){

    string log;

    // increase the time object
    domObject::timeObj->autoIncreaseTime();

    // char*'s for storing result and message
    char * message;
    char * result;

    // json for storing results in json format
    json jsonResult;

    // check if a message has been received
    if(python->sendMessage(3)){
        // receive result, change to json
        result = python->receiveActuators(3);
        jsonResult = toJson(result);
        // update actuator
        led = jsonResult["actuators"]["led"] == 1 && !domObject::timeObj->isNight();
        log += "led = ";
        log += to_string(led);
        log += " | ";
    }

    result = nullptr;
    // make message for wemos and receive sensors
    message = wemosMessage();

    // send to wemos and receive sensors
    result = wemos.sendReceive(message);

    // check if wemos didnt send an empty message
    if (result == nullptr) {
        cout<<"error receiving"<<endl;
    }
    else {
        // change to json, update attribute
        jsonResult = toJson(result);
        if (jsonResult["error"] != "NoDataReceived") {
            motionSensor = jsonResult["sensors"]["motionSensor"] == 1;
            if (motionSensor) {
                log += "beweging bij lamp | ";
            }
        }
    }

    // update lamp
    updateActuators(&log);

    //send all sensors and actuators to webserver
    if (!python->sendMessage(3)) {
        python->sendAll(3, pythonMessage());
    } else {
        // receive result, change to json
        result = python->receiveActuators(3);
        jsonResult = toJson(result);
        // update actuator
        led = jsonResult["actuators"]["led"] == 1 && !domObject::timeObj->isNight();
        log += "led = ";
        log += to_string(led);
        log += " | ";
    }

    logToFile(domObject::timeObj, log);
}

// make message for wemos
char * Lamp::wemosMessage(){
    json message = {
            {"id", 3},
            {"actuators",{
                           {"led",led}
                   }
            }
    };
    return toCharArray(message);
}

// make message for webserver
json Lamp::pythonMessage(){
    json message = {
            {"actuators", {
                {"led",led}
                     }},
            {"sensors" , {
                 {"motionSensor",motionSensor}
                   }
                    }
    };
    return message;
}

// function to control lamp
void Lamp::updateActuators(string *log){

    //Current time in seconds
    int currentTime = domObject::timeObj->getTimeSeconds();

    // turn led on on motionsensor, when there is no movement, turn off after 5 sec
    if (motionSensor && domObject::timeObj->isNight()) {
        led = true;
        startTime = currentTime;
        *log += "led = 1 | ";
    } else if(currentTime - startTime > 300 && domObject::timeObj->isNight()){
            led = false;
            *log += "led = 0 | ";
    }
}

