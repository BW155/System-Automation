//
// Created by Steyn
//
#include "pillar.h"
#include "../json/json.hpp"

using json = nlohmann::json;

// constructor for pillar
Pillar::Pillar(const char* IP, webSocket *w) : domObject(w, 4){
    gassensor = 0;
    button = 0;
    led = 0;
    buzzer = 0;
    Socket temp(4,IP);
    domObject::wemos = temp;
}

// Communicates with webserver and wemos, updates sensors and actuators accordingly
void Pillar::update(){

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
    }

    result = nullptr;
    // make message for wemos and receive sensors
    char *wemos_message = wemosMessage();

    // send to wemos and receive sensors
    char* receive_sensor = wemos.sendReceive(wemos_message);

    // check if wemos didnt send an empty message
    if (receive_sensor == NULL) {
        cout<<"error receiving"<<endl;
    }
    else {
        // change to json, update attributes
        json Receive_Sensor = toJson(receive_sensor);

        gassensor = Receive_Sensor["sensors"]["gasSensor"];
        button = Receive_Sensor["sensors"]["button"];
        buzzer = gassensor >= 900 || buzzer;
    }

    //send all sensors and actuators to webserver
    python->sendAll(4, pythonMessage()); // stuur alle sensors, alleen als uit sendReceive blijkt dat er veranderingen zijn

//    toLogFile();
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

void Pillar::toLogFile() {
    //log
    ofstream myfile;
    myfile.open("log.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << domObject::timeObj->getTimeString() << "Pillar: " << pythonMessage() << endl;
        if  (myfile.bad()) {
            cout<<"write failed"<<endl;
        }

    }
    else {
        cout<<"file not found"<<endl;
    }
    myfile.close();
}
