//
// Created by LarsLinux on 16-12-19.
//
#include "chair.h"
#include "../Socket/Socket.h"
#include "domObject.h"

Chair::Chair(const char *IP, webSocket *s, TimeClass *t) : domObject(s, t, 2) {
    led = false;
    forceSensor = 0;
    button = false;
    vibrator = false;
    timeOut = false;
    Socket temp(2,"Chair",IP);
    domObject::wemos = temp;
}

using json = nlohmann::json ;

char* Chair::wemosMessage() {
    json Message = {
            {"id",2},
            {"actuators", {
                          {"led", led},
                          {"vibrator", vibrator }
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}

json Chair::pythonMessage() {
    json Message = {
            {"actuators", {
                                  {"vibrator", vibrator},
                                  {"led", led}
                          }
            },
            {"sensors", {
                                  {"forceSensor", forceSensor},
                                  {"button", button}
                          }
            }
    };
    return Message;
}

void Chair::update() {
    char* result;
    json jsonResult;
    int cur_time;

    domObject::timeObj->autoIncreaseTime();

    //Current time in seconds;
    cur_time = domObject::timeObj->getTime()[0]*3600 + domObject::timeObj->getTime()[1]*60 + domObject::timeObj->getTime()[2];

    result = wemos.sendReceive(wemosMessage());
    jsonResult = toJson(result);
    updateAttributes(jsonResult);

    //30 min auto massage
    //10 because of safety for potentiol fluctuation in value from 0 - 1
    if(forceSensor <= 10) {
        vibrator = false;
        start_time_30min_check = cur_time;
        start_time_max_massage = cur_time;
    }

    if((cur_time-start_time_30min_check) > (30 * 60)){
        //60 seconds because time multiplier is above a minute. 2 minute pulse is 2 seconds real time vibrator pulse
        if((cur_time-start_time_30min_check) > ((30 * 60)+ 120)) {
            vibrator = false;
        }
        else {
            vibrator = true;
        }
    }

    //Chair massage
    if(forceSensor > 10) {
        if (button && !timeOut&& !vibrator) {
            vibrator = true;

        }
        else if ((cur_time - start_time_max_massage) > (5 * 60)&& vibrator) {
            vibrator = false;
            timeOut = true;
        }
    }
    if(timeOut){
        if((cur_time - start_timeOut) > (5 * 60))
            timeOut = false;
    }else{
        start_timeOut = cur_time;
    }
}

void Chair::updateAttributes(json result) {
    forceSensor = result["sensors"]["forceSensor"];
    button = result["sensors"]["button"];
    python->sendAll(2,pythonMessage());
}