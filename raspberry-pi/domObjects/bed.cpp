//
// Created by LarsLinux on 16-12-19.
//
#include "bed.h"
#include "../json/json.hpp"

using json = nlohmann::json;

Bed::Bed(const char* IP, webSocket* w, TimeClass *t): domObject(w,t){
    led = false;
    forceSensor = 0;
    updateForce = 0;
    button = false;
    startTime = 0;
    startTimeLed = 0;
    buttonPressed = false;
    ledTimerStarted = false;
    Socket temp(5, "wall", IP);
    domObject::wemos = temp;
}


void Bed::update(){
    char* result;
    char* message;
    json pythonResult;
    json wemosResult;

    domObject::timeObj->autoIncreaseTime();

    //ontvang van interface
    if(python->sendMessage(1)){
        result = python->receiveActuators(1);
        pythonResult = toJson(result);
        if (!(buttonPressed && led)) {
            led = pythonResult["actuators"]["led"] == 1;

        }
    }

    //wemos
    message = wemosMessage();
    result = wemos.sendReceive(message);
    wemosResult = toJson(result);

    if (wemosResult["sensors"]["button"] && !buttonPressed) {
        led = true;
        buttonPressed = true;
    }
    else if (wemosResult["sensors"]["button"] && led){
        led = false;
        buttonPressed = false;
    }

    forceSensor = updateForce;
    updateForce = wemosResult["sensors"]["forceSensor"];
    int currentTime = domObject::timeObj->getTime()[0]*3600 + domObject::timeObj->getTime()[1]*60 + domObject::timeObj->getTime()[2];

    if (updateForce - forceSensor > 300) {
        counter++;
        if (counter == 1) {
            startTime = domObject::timeObj->getTime()[0]*3600 + domObject::timeObj->getTime()[1]*60 + domObject::timeObj->getTime()[2];
        }
        startTimeWakker = currentTime;
    }
    if (currentTime - startTime > 300) {
        counter = 0;
        startTime = currentTime;
    }
    else if (counter >= 5) {
        cout<<"epsoilepsieboy"<<endl;
        counter = 0;
        startTime = currentTime;
    }

    if (led && !ledTimerStarted) {
        startTimeLed = currentTime;
        ledTimerStarted = true;
    }

    if (currentTime-startTimeLed > 600) {
        led = false;
        buttonPressed = false;
        startTimeLed = currentTime;
        ledTimerStarted = false;
    }

    if (forceSensor - updateForce > 600 && currentTime - startTimeWakker > 480) {
        cout<<"HIJ IS WAKKER MOTHERFUCKER"<<endl;
        startTimeWakker = currentTime;
    }

    //verstuur naar interface
    json Mes = pythonMessage();
    python->sendAll(1, Mes);
    usleep(200000);
}

char* Bed::wemosMessage(){
    json message = {
            {"id", 1},
            {"actuators", {
                           {"led", led}
                   }
            }
    };
    return toCharArray(message);
}

json Bed::pythonMessage(){
    json message = {
            {"actuators", {
                            {"led", led}
                          }
            },
            {"sensors",{
                        {"forceSensor", forceSensor},
                        {"button", button}
                    }
            }
    };
    return message;
}