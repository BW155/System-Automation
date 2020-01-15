//
// Created by LarsLinux on 16-12-19.
//

#include "door.h"
#include "../json/json.hpp"

using json = nlohmann::json;

Door::Door(const char* IP, webSocket* w, TimeClass *t): domObject(w, t, 7){
    servo = 0;
    buttonOutside = false;
    buttonInside = false;
    ledOutside = false;
    ledInside = false;
    pillar = NULL;
    
    Socket temp(7,"door",IP);
    domObject::wemos = temp;
}

void Door::update() {
    char* result;
    char* message;
    json jsonResult;
    int jsonServo = servo;

    domObject::timeObj->autoIncreaseTime();
    int* currentTime = domObject::timeObj->getTime;

    if(python->sendMessage(7)) {
        result = python->receiveActuators(7);
        jsonResult = toJson(result);
        //servo
        jsonServo = jsonResult["actuators"]["servo"];

        //ledIn
        ledInside = jsonResult["actuators"]["led1"] == 1;

        //ledOut
        ledOutside = currentTime[0] < 6 || currentTime[0] > 18 || buttonOutside;
    }

    if(pillar->get_buzzer() && buttonInside) {
        if (servo == 1) {
            servo = 0;
        }
        else {
            servo = 1;
        }
    }else if (buttonInside) {
        json message = {
                {"type", 4},
                {"id", 1}
        };
        python->sendNotification(toCharArray(message));
    }else{
        if(jsonServo != 0){
            servo = jsonServo;
        }else{
            servo = 0;
        }
    }

    if (buttonOutside) {
        json message = {
                {"type", 4},
                {"id", 2}
        };
        python->sendNotification(toCharArray(message));
    }
    //wemos
    message = wemosMessage(ledInside, ledOutside, servo); //verstuur dit naar wemos
    result = wemos.sendReceive(message);
    jsonResult = toJson(result); //ontvangen van wemos
    buttonInside = jsonResult["sensors"]["button1"];
    buttonOutside = jsonResult["sensors"]["button2"];

    python->sendAll(7, pythonMessage());

//    toLogFile();
}

char* Door::wemosMessage(bool ledIn, bool ledOut, int servo) {
    json message = {
            {"id",7},
            {"actuators", {
                          {"led1", ledIn},
                          {"led2", ledOut},
                          {"servo", servo}
                  }
            }
    };
    return toCharArray(message);
}

json Door::pythonMessage() {
    json message = {
            {"id", 7},
            {"actuators", {
                           {"led1", ledInside},
                           {"led2", ledOutside},
                           {"servo", servo}
                   }
            },
            {"sensors", {
                           {"button1", buttonInside},
                           {"button2", buttonOutside}
                   }
            }
    };
    return message;
}

void Door::setPillarPointer(Pillar* p){
    pillar = p;
}

void Door::toLogFile() {
    //log
    ofstream myfile;
    myfile.open("log.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << domObject::timeObj->getTimeString() << "Door: " << pythonMessage() << endl;
        if  (myfile.bad()) {
            cout<<"write failed"<<endl;
        }

    }
    else {
        cout<<"file not found"<<endl;
    }
    myfile.close();
}