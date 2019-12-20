//
// Created by LarsLinux on 16-12-19.
//

#include "wall.h"
#include "../json/json.hpp"

using json = nlohmann::json;

Wall::Wall(char* IP, webSocket* w): domObject(w){
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
    if(python->sendMessage(7)){
        result = python->receiveActuators(7);
        pythonResult = toJson(result);
    }

    //window
    if(pythonResult["actuators"]["window"]){
        window = pythonResult["actuators"]["window"];
    }else if(LDR < 500){    //nog te calibreren
        window = true;
    }else{
        window = false;
    }

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
    message = pythonMessage();
    python->sendAll(7, message);
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

char* Wall::pythonMessage(){
    json message = {
        {"id", 5},
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
    return toCharArray(message);
}