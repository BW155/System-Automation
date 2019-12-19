//
// Created by Zep on 16-12-19.
//
#include <jansson.h>
#include "fridge.h"
#include "../domObjects/domObject.h"

#define open 1
#define close 0

using json = nlohmann::json ;

fridge::fridge(char * IP, webSocket *s) : domObject(s), cooling(false), thermometer1(0), thermometer2(0), openClose(0) {
}

char* wemosMessage(bool cooling){
    json Message = {
            {"id",6},
            {"actuators", {
                          {"cooling", cooling}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}

void fridge::update(){
     char *result;
     static int prev_time;
     int start_time, cur_time;
     bool state = 0;

     fridge f1();
     TimeClass *t2 = f1().getTimePointer();
     t2 -> autoIncreaseTime();


     //Ask for current time in seconds
     cur_time = t2->getTime()[0]*3600 + t2->getTime()[1]*60  + t2->getTime()[2];

     if (openClose == open && state == 1){
        start_time = t2->getTime()[0]*3600 + t2->getTime()[1]*60  + t2->getTime()[2];
        state = 0;
     }
     if((cur_time-start_time) > (5 * 60)){
        cooling = false;
        sendReceive(wemosMessage(cooling));
     }

     if (openClose == closed && state == 0) {
         start_time = 0;
         state = 1;
         cooling = true;
         sendReceive(wemosMessage(cooling));

     }
}

