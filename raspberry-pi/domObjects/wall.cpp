//
// Created by LarsLinux on 16-12-19.
//

#include "wall.h"
#include "../json/json.hpp"

using json = nlohmann::json;

Wall::Wall(const char* IP, webSocket* w): domObject(w, 5){
    led = 0;
    window = false;
    dimmer = 0;
    LDR = 0;
    Socket temp(5,IP);
    domObject::wemos = temp;
}

void Wall::update(){
    char* result;
    char* message;
    json pythonResult;
    json wemosResult;

    //ontvang van interface
    if(python->sendMessage(5)){
        result = python->receiveActuators(5);
        pythonResult = toJson(result);
        led = pythonResult["actuators"]["led"];
    }
    //window
    if(pythonResult["actuators"]["window"] == 1){
        window = true;
    }else window = LDR < 500;
    //ledstrip


    //wemos
    message = wemosMessage();
    result = wemos.sendReceive(message);
    if (result == NULL) {
        cout<<"error receiving"<<endl;
    }
    else {
        wemosResult = toJson(result);
        int temp = wemosResult["sensors"]["dimmer"];
        if (dimmer - temp != 0) {
            led = wemosResult["sensors"]["dimmer"];
            dimmer = wemosResult["sensors"]["dimmer"];
        }

        LDR = wemosResult["sensors"]["LDR"];
    }

    //verstuur naar interface
    python->sendAll(5, pythonMessage());

//    toLogFile();
}

char* Wall::wemosMessage(){
    json message = {
            {"id", 5},
            {"actuators", {
                           {"led", led},
                           {"window", window}
                   }
            }
    };
    return toCharArray(message);
}

json Wall::pythonMessage(){
    json message = {
            {"actuators", {
                           {"led", led},
                           {"window", window}
                   }
            },
            {"sensors",{
                           {"dimmer", dimmer},
                           {"LDR", LDR}
                   }
            }
    };
    return message;
}

void Wall::toLogFile() {
    //log
    ofstream myfile;
    myfile.open("log.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << domObject::timeObj->getTimeString() << "Wall: " << pythonMessage() << endl;
        if  (myfile.bad()) {
            cout<<"write failed"<<endl;
        }

    }
    else {
        cout<<"file not found"<<endl;
    }
    myfile.close();
}