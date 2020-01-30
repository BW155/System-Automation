//
// Created by Jasper
//

#include "door.h"
#include "../json/json.hpp"

using json = nlohmann::json;

// constructor for door
Door::Door(const char* IP, webSocket* w, TimeClass *t): domObject(w, t, 7){
    servo = 0;
    buttonOutside = false;
    buttonInside = false;
    ledOutside = false;
    ledInside = false;
    pillar = NULL;
    Socket temp(7, IP);
    domObject::wemos = temp;
}

// Communicates with webserver and wemos, updates sensors and actuators accordingly
void Door::update() {

    string log;

    // char*'s for storing result and message
    char* result;
    char* message;

    // json for storing results in json format
    json jsonResult;

    // int for checking change in servo
    int jsonServo = servo;

    // increase the time object
    domObject::timeObj->autoIncreaseTime();

    //Current time in seconds;
    int* currentTime = domObject::timeObj->getTime();

    // check if a message has been received
    if(python->sendMessage(7)) {
        // receive result, change to json
        result = python->receiveActuators(7);
        jsonResult = toJson(result);

        // update actuator values
        jsonServo = jsonResult["actuators"]["servo"];
        ledInside = jsonResult["actuators"]["led1"] == 1;
        log += "deur = ";
        log += to_string(servo);
        log += " | ";

        log += "led binnen = ";
        log += to_string(ledInside);
        log += " | ";
    }

    // when alarm is raised, door can be opened with button
    if(pillar->get_buzzer() && buttonInside) {
        servo = 1;
        log += "deur = ";
        log += to_string(servo);
        log += " | ";
    }
    // when there is no alarm, pressing the button will send a message to the guard
    else if (buttonInside) {
        json message = {
                {"type", 4},
                {"id", 1}
        };
        python->sendNotification(toCharArray(message));
        log += "button inside pressed";
    }
    // when button is not pressed, change state of door
    else{
        if(jsonServo != 0){
            servo = jsonServo;
        }else{
            servo = 0;
        }
    }

    // when button outside is pressed, send notification to guard
    if (buttonOutside) {
        json message = {
                {"type", 4},
                {"id", 2}
        };
        python->sendNotification(toCharArray(message));
        log += "button outside pressed";
    }

    result = nullptr;
    // make message for wemos and receive sensors
    message = wemosMessage(); //verstuur dit naar wemos

    // send to wemos and receive sensors
    result = wemos.sendReceive(message);

    // check if wemos didnt send an empty message
    if (result == nullptr) {
        cout<<"error receiving"<<endl;
    }
    else {
        // change to json, update attributes
        jsonResult = toJson(result);
        if (jsonResult["error"] != "NoDataReceived") {
            buttonInside = jsonResult["sensors"]["button1"];
            buttonOutside = jsonResult["sensors"]["button2"];
        }
    }

    // led outside during night always on, during day controlled by button
    ledOutside = getTimePointer()->isNight() || buttonOutside;

    //send all sensors and actuators to webserver
    python->sendAll(7, pythonMessage());

    logToFile(domObject::timeObj, log);
}

// make message for wemos
char* Door::wemosMessage() {
    json message = {
            {"id",7},
            {"actuators", {
                          {"led1", ledInside},
                          {"led2", ledOutside},
                          {"servo", servo}
                  }
            }
    };
    return toCharArray(message);
}

// make message for webserver
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

// link door and Pillar
void Door::setPillarPointer(Pillar* p){
    pillar = p;
}

