//
// Created by LarsLinux on 16-12-19.
//
#include "lamp.h"

//Pi stuurt:		{"id":3, "actuators":{"led":x}}
//Wemos stuurt:	{"error":"err", "sensors":{"motionSensor":x, "button":x}}

Lamp::Lamp(const char * IP,webSocket *s): domObject(s), led(0), motionSensor(0){
    Socket temp(3, "tableLamp", IP);
    domObject::wemos = temp;
}


void Lamp::update(){
    json ledmsg = {
            {"id",3},
            {"actuators",{
                          {"led",led}
                  }
            }
    };
    json motionmsg = {
            {"id",3},
            {"actuators",{
                          {"led",led}
                  },
                    {"sensors",{
                                       {"motionSensor",motionSensor}
                               }
                    }
            }
    };
    char* ledMsg = toCharArray(ledmsg);
    char* motionMsg = toCharArray(motionmsg);
    socket.sendReceive(ledMsg);

}

void Lamp::stuurLamp(){
    if (motionSensor){
        led = true;

    }
    else if(!motionSensor){
        led = false;
    }
}