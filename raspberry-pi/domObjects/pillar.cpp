//
// Created by Steyn
//
#include "pillar.h"
#include "../json/json.hpp"

using json = nlohmann::json;

// constructor for pillar
Pillar::Pillar(const char* IP, webSocket *w, TimeClass *t) : domObject(w, t, 4){
    gassensor = 0;
    button = 0;
    led = 0;
    buzzer = 0;
    Socket temp(4,IP);
    domObject::wemos = temp;
}

// Communicates with webserver and wemos, updates sensors and actuators accordingly
void Pillar::update(){

    string log;

    // char*' for storing result
    char *result;

    // check if a message has been received
    if(python->sendMessage(4)) { //als er verandering is
        // receive result, change to json
        result = python->receiveActuators(4);
        json Result = toJson(result);

        // change actuator value
        buzzer = Result["actuators"]["buzzer"] == 1;
        led = Result["actuators"]["led"] == 1;

        log += "led = ";
        log += to_string(led);
        log += " | ";

        log += "buzzer = ";
        log += to_string(buzzer);
        log += " | ";
    }

    result = nullptr;
    // make message for wemos and receive sensors
    char *wemos_message = wemosMessage();

    // send to wemos and receive sensors
    char* receive_sensor = wemos.sendReceive(wemos_message);

    // check if wemos didnt send an empty message
    if (receive_sensor == nullptr) {
        cout<<"error receiving"<<endl;
    }
    else {
        // change to json, update attributes
        json Receive_Sensor = toJson(receive_sensor);
        if (Receive_Sensor["error"] != "NoDataReceived") {
            gassensor = Receive_Sensor["sensors"]["gasSensor"];

            if (Receive_Sensor["sensors"]["button"] != button) {
                log += "button = ";
                log += to_string(Receive_Sensor["sensors"]["button"]);
                log += " | ";
            }
            button = Receive_Sensor["sensors"]["button"];
            if (button) {
                json message = {
                        {"type", 4},
                        {"id", 9}
                };
                python->sendNotification(toCharArray(message));
            }
            buzzer = gassensor >= 900 || buzzer;

            if (buzzer) {
                log += "ALARM";
            }
        }
    }

    //send all sensors and actuators to webserver
    python->sendAll(4, pythonMessage()); // stuur alle sensors, alleen als uit sendReceive blijkt dat er veranderingen zijn

    logToFile(domObject::timeObj, log);
}

// make message for wemos
char* Pillar::wemosMessage(){
    json message = {
            {"id",4},
            {"actuators", {
                        {"led", led},
                        {"buzzer", buzzer}
                    }
            }
    };
    return toCharArray(message);
}

// make message for webserver
json Pillar::pythonMessage() {
    json message = {
                {"actuators", {
                            {"led", led},
                            {"buzzer", buzzer}
                        }
                },
                {"sensors", {
                            {"gasSensor", gassensor},
                            {"button", button}
                    }
                }
        };
    return message;
}

// get buzzer value
bool Pillar::get_buzzer(){
    return buzzer;
}

