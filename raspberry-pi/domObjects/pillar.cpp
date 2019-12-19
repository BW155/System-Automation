//
// Created by LarsLinux on 16-12-19.
//
#include "pillar.h"
#include "domObject.h"

using namespace std;
using json = nlohmann::json;

Pillar::Pillar(char* IP, webSocket *x) : domObject(x){
    gassensor = 0;
    button = 0;
    led = 0;
    buzzer = 0;
    Socket temp(4, "pillar", IP);
    domObject::wemos = temp;
}

char* Pillar::wemosMessage(json Result){
    button = Result["sensors"]["button"];
    gassensor = Result["sensor"]["gasSensor"];
}

char* Pillar::pythonMessage(bool Led, bool buz) {
    json Message = {
            {"id",4},
            {"actuators", {
                        {"led", led},
                        {"buzzer", buzzer}
                    }
            }
        };
    char *message = toCharArray(Message);
    return message;
}

void Pillar::update(){
    char *result;
    if(python->sendMessage(4)) { //als er verandering is
        result = python->receiveActuators(4);
    }
    json Result = toJson(result);

    buzzer = Result["actuators"]["buzzer"];
    led = Result["actuators"]["led"];

    json wemosMessage = {
            {"id",4},
            {"actuators", {
                        {"led", led},
                        {"buzzer", buzzer}
                    }
            }
    };
    char *wemos_message = toCharArray(wemosMessage);
        
    char* receive_sensor = wemos.sendReceive(wemos_message);
    json ReceiveSensor = toJson(receive_sensor);

    if(gassensor == !ReceiveSensor["sensors"]["gasSensor"] || button == !ReceiveSensor["sensors"]["button"]){
        gassensor = ReceiveSensor["sensors"]["gasSensor"];
        button = ReceiveSensor["sensors"]["button"];

        buzzer = (gassensor >= 875);
        
        json python_Message = {
                {"id",4},
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
        char *python_message = toCharArray(python_Message);
        python->sendAll(4, *python_message); // stuur alle sensors, alleen als uit sendReceive blijkt dat er veranderingen zijn
    }
}

bool Pillar::get_buzzer(){
    return buzzer;
}  
