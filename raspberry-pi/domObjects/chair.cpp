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
    startTime = 0;
    counter = 0;
    updateForce = 0;
    Socket temp(2,"Chair",IP);
    domObject::wemos = temp;
    startTimeMedication = 0;
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

//    if (startTimeMedication == 0) {
//        startTimeMedication = cur_time;
//        json message = {
//                {"type", 4},
//                {"id", 5}
//        };
//        python->sendNotification(toCharArray(message));
//    } else if (cur_time-startTimeMedication > 599) {
//        json message = {
//                {"type", 4},
//                {"id", 6}
//        };
//        python->sendNotification(toCharArray(message));
//    } else if (cur_time-startTimeMedication > 1199) {
//        json message = {
//                {"type", 4},
//                {"id", 7}
//        };
//        python->sendNotification(toCharArray(message));
//    } else if (cur_time-startTimeMedication > 1799) {
//        json message = {
//                {"type", 4},
//                {"id", 8}
//        };
//        python->sendNotification(toCharArray(message));
//        if (cur_time-startTimeMedication > 2399) {
//            startTimeMedication = 0;
//        }
//    }
    result = wemos.sendReceive(wemosMessage());
    jsonResult = toJson(result);
    updateAttributes(jsonResult);




    if (updateForce - forceSensor > 300) {
        counter++;
        cout<<counter<<endl;
        if (counter == 1) {
            startTime = domObject::timeObj->getTime()[0]*3600 + domObject::timeObj->getTime()[1]*60 + domObject::timeObj->getTime()[2];
        }
    }
    else if (cur_time - startTime > 6000) {
        counter = 0;
        startTime = cur_time;
        cout<<"tijd"<<endl;
    }
    else if (counter >= 5) {
        cout<<"epsoilepsieboy"<<endl;
        counter = 0;
        startTime = cur_time;
        json message = {
                {"type", 4},
                {"id", 0}
        };
        python->sendNotification(toCharArray(message));
    }

    //30 min auto massage
    //10 because of safety for potentiol fluctuation in value from 0 - 1
    if(forceSensor <= 10) {
        vibrator = false;
        start_time_30min_check = cur_time;
        start_time_max_massage = cur_time;
    }

    if((cur_time-start_time_30min_check) > (30 * 600)){
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
        else if ((cur_time - start_time_max_massage) > (5 * 600)&& vibrator) {
            vibrator = false;
            timeOut = true;
        }
    }
    if(timeOut){
        if((cur_time - start_timeOut) > (5 * 600))
            timeOut = false;
    }else{
        start_timeOut = cur_time;
    }
}

void Chair::updateAttributes(json result) {
    forceSensor = updateForce;
    updateForce = result["sensors"]["forceSensor"];
    button = result["sensors"]["button"];
    python->sendAll(2,pythonMessage());
}