//
// Created by LarsLinux on 16-12-19.
//

#include "door.h"
#include "../timeKeeper.h"
#include "../json/json.hpp"

using json = nlohmann::json;

Door::Door(const char* IP, webSocket* w, TimeClass *t): domObject(w, t){
    servo = 0;
    buttonOutside = false;
    buttonInside = false;
    ledOutside = false;
    ledInside = false;
    pillar = NULL;
    Socket temp(7,"door",IP);
    domObject::wemos = temp;
}

void Door::update() {
    char* result;
    char* message;
    json jsonResult;

    int time[] = {0,0,0,0}; // timeObject->getTime
    if(python->sendMessage(7)) {
        result = python->receiveActuators(7);
        jsonResult = toJson(result);
        //servo
        cout<<result<<endl;
        int serv = jsonResult["actuators"]["servo"];
        cout<<serv<<endl;
        if(serv != 0){
            servo = jsonResult["actuators"]["servo"];
            //}else if(pillar->get_buzzer() && buttonInside){
            //    servo = 1;
        }else{
            servo = 0;
        }


        //ledIn
        ledInside = jsonResult["actuators"]["led1"] == 1;
        //ledOut
        ledOutside = time[0] < 6 || time[0] > 18 || buttonOutside;
        cout<<"klaar met py"<<endl;
    }

    //wemos
    message = wemosMessage(ledInside, ledOutside, servo); //verstuur dit naar wemos
    result = wemos.sendReceive(message);
    jsonResult = toJson(result); //ontvangen van wemos
    buttonInside = jsonResult["sensors"]["button1"];
    buttonOutside = jsonResult["sensors"]["button2"];
    cout<<"een"<<endl;


//    message  = pythonMessage();
    python->sendAll(7, pythonMessage());
}

char* Door::wemosMessage(bool ledIn, bool ledOut, int servo) {
    json Message = {
            {"id",7},
            {"actuators", {
                          {"led1", ledIn},
                          {"led2", ledOut},
                          {"servo", servo}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}

json Door::pythonMessage() {
    json Message = {
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
    char *message = toCharArray(Message);
    return Message;
}

//void Door::setPillarPointer(Pillar* p){
//    pillar = p;
//}