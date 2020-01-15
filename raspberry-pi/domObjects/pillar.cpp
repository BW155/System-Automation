//
// Created by LarsLinux on 16-12-19.
//
#include "pillar.h"
#include "../json/json.hpp"

using json = nlohmann::json;

Pillar::Pillar(const char* IP, webSocket *w) : domObject(w, 4){
    gassensor = 0;
    button = 0;
    led = 0;
    buzzer = 0;
    
    Socket temp(4, "pillar", IP);
    domObject::wemos = temp;
}

void Pillar::update(){
    char *result;
    if(python->sendMessage(4)) { //als er verandering is
        result = python->receiveActuators(4);
        json Result = toJson(result);
        buzzer = Result["actuators"]["buzzer"] == 1;
        led = Result["actuators"]["led"] == 1;
        cout<<"een"<<endl;
    }
    
    char *wemos_message = wemosMessage();
     
    char* receive_sensor = wemos.sendReceive(wemos_message);
    json Receive_Sensor = toJson(receive_sensor);

    gassensor = Receive_Sensor["sensors"]["gasSensor"];
    button = Receive_Sensor["sensors"]["button"];
    buzzer = gassensor >= 900 || buzzer;
    
    python->sendAll(4, pythonMessage()); // stuur alle sensors, alleen als uit sendReceive blijkt dat er veranderingen zijn

//    toLogFile();
}

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
