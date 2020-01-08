//
// Created by LarsLinux on 16-12-19.
//

#include "wall.h"
#include "../json/json.hpp"

using json = nlohmann::json;

Wall::Wall(const char* IP, webSocket* w): domObject(w){
    led = 0;
    window = 0;
    dimmer = 0;
    LDR = 0;
    Socket temp(5, "wall", IP);
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
    }

    //window
    if(pythonResult["actuators"]["window"] == 1){
        window = true;
    }else window = LDR < 500;

    //ledstrip
    if(pythonResult["actuators"]["led"] != 0){
        led = pythonResult["actuators"]["led"];
    }else{
        led = (dimmer/1024.0) * 256;
    }

    //wemos
    message = wemosMessage();
    result = wemos.sendReceive(message);
    wemosResult = toJson(result);
    dimmer = wemosResult["sensors"]["dimmer"];
    LDR = wemosResult["sensors"]["LDR"];

    //verstuur naar interface
    json Mes = pythonMessage();
    python->sendAll(5, Mes);
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