//
// Created by LarsLinux on 16-12-19.
//
#include "pillar.h"

Pillar::Pillar(const char* IP, webSocket *x) : domObject(x, 4){
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
    
    json python_message = pythonMessage();
    python->sendAll(4, python_message); // stuur alle sensors, alleen als uit sendReceive blijkt dat er veranderingen zijn

//    toLogFile();
}

bool Pillar::get_buzzer(){
    return buzzer;
}

void Pillar::toLogFile() {
    //log
    ofstream myfile;
    myfile.open("log.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << domObject::timeObj->getTime()[0] << ":" << domObject::timeObj->getTime()[1] << ":"
               << domObject::timeObj->getTime()[2] << "Pillar: " << pythonMessage() << endl;
        if  (myfile.bad()) {
            cout<<"write failed"<<endl;
        }

    }
    else {
        cout<<"file not found"<<endl;
    }
    myfile.close();
}
