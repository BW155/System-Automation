//
// Created by Zep
//
#include "chair.h"
#include "../json/json.hpp"

using json = nlohmann::json;

// constructor for chair
Chair::Chair(const char *IP, webSocket *w, TimeClass *t) : domObject(w, t, 2) {
    led = false;
    forceSensor = 0;
    button = false;
    vibrator = false;
    timeOut = false;
    startTime = 0;
    counter = 0;
    updateForce = 0;
    startTimeMedication = 0;
    lastNotification = 0;
    Socket temp(2,IP);
    domObject::wemos = temp;
}

// Communicates with webserver and wemos, updates sensors and actuators accordingly
void Chair::update() {

    // char*' for storing result
    char* result;

    // jsons for storing results in json format
    json jsonResult;

    // int for storing time
    int currentTime;

    // increase the time object
    domObject::timeObj->autoIncreaseTime();

    //Current time in seconds
    currentTime = domObject::timeObj->getTimeSeconds();

    // The system for sending a notification when Client should take medicine
    if (startTimeMedication == 0 && lastNotification != 1) {
        startTimeMedication = currentTime + 1;
        lastNotification = 1;
        json message = {
                {"type", 4},
                {"id", 5}
        };
        python->sendNotification(toCharArray(message));
    } else if (currentTime-startTimeMedication >= 599 && currentTime-startTimeMedication < 620 && lastNotification != 2) {
        lastNotification = 2;
        json message = {
                {"type", 4},
                {"id", 6}
        };
        python->sendNotification(toCharArray(message));
    } else if (currentTime-startTimeMedication >= 1199&& currentTime-startTimeMedication < 1220 && lastNotification != 3) {
        lastNotification = 3;
        json message = {
                {"type", 4},
                {"id", 7}
        };
        python->sendNotification(toCharArray(message));
    } else if (currentTime-startTimeMedication >= 1799&& currentTime-startTimeMedication < 1820 && lastNotification != 4) {
        lastNotification = 4;
        json message = {
                {"type", 4},
                {"id", 8}
        };
        python->sendNotification(toCharArray(message));
        if (currentTime-startTimeMedication >= 2399 && currentTime-startTimeMedication < 2420) {
            startTimeMedication = 0;
        }
    }

    // send message to wemos and receive sensors
    result = wemos.sendReceive(wemosMessage());

    // check if wemos didnt send an empty message
    if (result == NULL) {
        cout<<"error receiving"<<endl;
    }
    else {
        // change to json, update attributes
        jsonResult = toJson(result);
        updateAttributes(jsonResult);
    }

    // check for changes in the forcesensor
    if (updateForce - forceSensor > 300) {
        // update counter
        counter++;
        if (counter == 1) {
            startTime = domObject::timeObj->getTimeSeconds();
        }
    }

    // after 10 seconds, reset the timer that checks for epilepsy, else, if counter == 5, give an epilepsy notification
    if (currentTime - startTime > 600) {
        counter = 0;
        startTime = currentTime;
    }
    else if (counter >= 5) {
        counter = 0;
        startTime = currentTime;
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
        start_time_30min_check = currentTime;
        start_time_max_massage = currentTime;
    }

    // when client sits on chair, chair will shake after 30 seconds
    if((currentTime-start_time_30min_check) > (30 * 60)){
        //60 seconds because time multiplier is above a minute. 2 minute pulse is 2 seconds real time vibrator pulse
        if((currentTime-start_time_30min_check) > ((30 * 60)+ 120)) {
            vibrator = false;
        }
        else {
            vibrator = true;
        }
    }

    //Chair massage, for 5 seconds
    if(forceSensor > 10) {
        if (button && !timeOut&& !vibrator) {
            vibrator = true;

        }
        else if ((currentTime - start_time_max_massage) > (5 * 60)&& vibrator) {
            vibrator = false;
            timeOut = true;
        }
    }

    // timout between massages, 5 seconds
    if(timeOut){
        if((currentTime - start_timeOut) > (5 * 60))
            timeOut = false;
    }else{
        start_timeOut = currentTime;
    }

//    toLogFile();
}

// make message for wemos
char* Chair::wemosMessage() {
    json message = {
            {"id",2},
            {"actuators", {
                          {"led", led},
                          {"vibrator", vibrator }
                  }
            }
    };
    return toCharArray(message);
}

// make message for webserver
json Chair::pythonMessage() {
    json message = {
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
    return message;
}

// update all atributes according to json
void Chair::updateAttributes(json result) {
    forceSensor = updateForce;
    updateForce = result["sensors"]["forceSensor"];
    button = result["sensors"]["button"];
    python->sendAll(2,pythonMessage());
}

