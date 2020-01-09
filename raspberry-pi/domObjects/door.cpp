//
// Created by LarsLinux on 16-12-19.
//

#include "door.h"
#include "../timeKeeper.h"
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

    int time[] = {0,0,0,0}; // timeObject->getTime
    if(python->sendMessage(7)) {
        result = python->receiveActuators(7);
        jsonResult = toJson(result);
        //servo
        jsonServo = jsonResult["actuators"]["servo"];



        //ledIn
        ledInside = jsonResult["actuators"]["led1"] == 1;

        //ledOut
        ledOutside = time[0] < 6 || time[0] > 18 || buttonOutside;
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
                {"id", 1}
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
}

char* Door::wemosMessage(bool ledIn, bool ledOut, int servo) {
    json Message = {
            {"id",7},
            {"actuators", {
                          {"led1", ledIn},
                          {"led2", ledOut},
                          {"servo", servo}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}

json Door::pythonMessage() {
    json Message = {
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
    char *message = toCharArray(Message);
    return Message;
}

void Door::setPillarPointer(Pillar* p){
    pillar = p;
}