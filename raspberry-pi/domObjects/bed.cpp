//
// Created by Jasper & Lars
//
#include "bed.h"
#include <iostream>
#include <string>

using json = nlohmann::json;

// constructor for bed
Bed::Bed(const char* IP, webSocket* w, TimeClass *t): domObject(w, t, 1){
    led = false;
    forceSensor = 0;
    updateForce = 0;
    button = false;
    startTime = 0;
    startTimeLed = 0;
    startTimeAwake = 0;
    buttonPressed = false;
    ledTimerStarted = false;
    counter = 0;
    Socket temp(5, IP);
    domObject::wemos = temp;
}

// Communicates with webserver and wemos, updates sensors and actuators accordingly
void Bed::update(){

    string log;

    // char*'s for storing result and message
    char* result;
    char* message;

    // jsons for storing results in json format
    json pythonResult;
    json wemosResult;

    // increase the time object
    domObject::timeObj->autoIncreaseTime();

    // check if a message has been received
    if(python->sendMessage(1)){
        // receive result, change to json
        result = python->receiveActuators(1);
        pythonResult = toJson(result);

        // change actuator value
        if (!(buttonPressed && led)) {
            led = pythonResult["actuators"]["led"] == 1;
            log += "led = ";
            log += to_string(led);
            log += " | ";
        }
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
        // change to json, update attributes
        wemosResult = toJson(result);
        if (wemosResult["error"] != "NoDataReceived") {
            if (wemosResult["sensors"]["button"] && !buttonPressed) {
                led = true;
                buttonPressed = true;
                log += "knop ingedrukt | ";
                log += "led = 1 | ";
            } else if (wemosResult["sensors"]["button"] && led) {
                led = false;
                buttonPressed = false;
                log += "knop ingedrukt | ";
                log += "led = 0 | ";
            }

            forceSensor = updateForce;
            updateForce = wemosResult["sensors"]["forceSensor"];
        }
    }

    // get the current time
    int currentTime = domObject::timeObj->getTimeSeconds();

    // check for changes in the forcesensor
    if (updateForce - forceSensor > 300) {
        // update counter
        counter++;
        if (counter == 1) {
            startTime = domObject::timeObj->getTimeSeconds();
        }
        log += "forceSensor waarde: ";
        log += to_string(updateForce);
        log += " | ";
        // reset the timer that checks if Client is awake
        startTimeAwake = currentTime;
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
        startTimeAwake = currentTime;
        log += "Epilepsie!! | ";
    }

    // start timer for led if led is on and timer isn't started yet
    if (led && !ledTimerStarted) {
        startTimeLed = currentTime;
        ledTimerStarted = true;
    }

    // turn led off after 10 seconds
    if (currentTime-startTimeLed > 600) {
        led = false;
        buttonPressed = false;
        startTimeLed = currentTime;
        ledTimerStarted = false;
        log += "led = 0 | ";
    }

    // send notification when Client wakes up
    if (forceSensor - updateForce > 600 && currentTime - startTimeAwake > 600) {
        json message = {
                {"type", 4},
                {"id", 3}
        };
        python->sendNotification(toCharArray(message));
        startTimeAwake = currentTime;
        log += "Client uit bed | ";
    }

    //send all sensors and actuators to webserver
    if (!python->sendMessage(1)) {
        python->sendAll(1, pythonMessage());
    } else {
        // receive result, change to json
        result = python->receiveActuators(1);
        pythonResult = toJson(result);

        // change actuator value
        if (!(buttonPressed && led)) {
            led = pythonResult["actuators"]["led"] == 1;
            log += "led = ";
            log += to_string(led);
            log += " | ";
        }
    }

    logToFile(domObject::timeObj, log);

}

// make message for wemos
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

// make message for webserver
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