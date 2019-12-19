//
// Created by LarsLinux on 16-12-19.
//
#include "lamp.h"
#include "json.hpp"


lamp::lamp(char * IP, webSocket *s): domObject(s), led(0), motionSensor(0){
Socket temp(3, "tableLamp", IP);
domObject::wemos = temp;
}

void lamp::stuurLamp(){
    
    if (motionSensor){
        led = true;

    }
    else if(!motionSensor){
        led = false;
    }
}