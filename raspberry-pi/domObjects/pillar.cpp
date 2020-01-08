//
// Created by LarsLinux on 16-12-19.
//
#include "pillar.h"

Pillar::Pillar(const char* IP, webSocket *x) : domObject(x){
    gassensor = 0;
    button = 0;
    led = 0;
    buzzer = 0;
    Socket temp(4, "pillar", IP);
    domObject::wemos = temp;
}

char* Pillar::wemosMessage(){
    json wemos_Message = {
            {"id",4},
            {"actuators", {
                        {"led", led},
                        {"buzzer", buzzer}
                    }
            }
    };
    char *wemos_message = toCharArray(wemos_Message);
    return wemos_message;
}

json Pillar::pythonMessage() {
    json Message = {
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
    return Message;
}

void Pillar::update(){
    char *result;
    if(python->sendMessage(4)) { //als er verandering is
        cout<<"verandering"<<endl;
        result = python->receiveActuators(4);
        json Result = toJson(result);
        buzzer = Result["actuators"]["buzzer"] == 1;
        led = Result["actuators"]["led"] == 1;
    }
    
    char *wemos_message = wemosMessage();
     
    char* receive_sensor = wemos.sendReceive(wemos_message);
    cout<<receive_sensor<<endl;
    json Receive_Sensor = toJson(receive_sensor);

    gassensor = Receive_Sensor["sensors"]["gasSensor"];
    button = Receive_Sensor["sensors"]["button"] == 1;
    cout<<gassensor<<endl;
    buzzer = gassensor >= 900 || buzzer;
    
    json python_message = pythonMessage();
    python->sendAll(4, python_message); // stuur alle sensors, alleen als uit sendReceive blijkt dat er veranderingen zijn
}

bool Pillar::get_buzzer(){
    return buzzer;
}  
