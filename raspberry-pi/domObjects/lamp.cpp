// Created by LarsLinux on 16-12-19.
//
#include "lamp.h"
#include "../json/json.hpp"

using json = nlohmann::json;

Lamp::Lamp(const char * IP, webSocket *w, TimeClass *t): domObject(w, t, 3){
    startTime = 0;
    led = false;
    motionSensor = false;
    Socket temp(3,IP);
    domObject::wemos = temp;
}


void Lamp::update(){
    char * message;
    char * result;
    json jsonResult;

    stuurLamp();
    if(python->sendMessage(3)){
        result = python->receiveActuators(3);
        jsonResult = toJson(result);
        led = jsonResult["actuators"]["led"] == 1;
    }
    message = wemosMessage();
    result = wemos.sendReceive(message);
    jsonResult = toJson(result);
    
    motionSensor = jsonResult["sensors"]["motionSensor"] == 1;

    python->sendAll(3, pythonMessage());

//    toLogFile();
}

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

void Lamp::stuurLamp(){
    int currentTime;
    domObject::timeObj->autoIncreaseTime();
    currentTime = domObject::timeObj->getTimeSeconds();
    if (motionSensor){
        led = true;
        startTime = currentTime;

    }
    if(!motionSensor){
        if((currentTime - startTime) > (300)){  //5 minuten (5 x 60)
            led = false;
        }
    }
}

void Lamp::toLogFile() {
    //log
    ofstream myfile;
    myfile.open("log.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << domObject::timeObj->getTimeString() << "Lamp: " << pythonMessage() << endl;
        if  (myfile.bad()) {
            cout<<"write failed"<<endl;
        }

    }
    else {
        cout<<"file not found"<<endl;
    }
    myfile.close();
}