//
// Created by Zep on 16-12-19.
//
#include <jansson.h>
#include "fridge.h"
#include "../Socket/Socket.h"
#include "domObject.h"

#define open 1
#define closed 0

using json = nlohmann::json ;

Fridge::Fridge(const char * IP, webSocket *s, TimeClass *t) : domObject(s, t){
    cooling = false;
    thermometer1 = 0;
    thermometer2 = 0; 
    openClose = 0 ;
    Socket temp(6,"Fridge",IP);
}

char* Fridge::wemosMessage(){
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

void Fridge::update(){
     char *result, *sensors;
     static int prev_time;
     int start_time, cur_time;
     bool state = 0;

     TimeClass *t2 = getTimePointer();
     t2 -> autoIncreaseTime();

     //Ask for current time in seconds
     cur_time = t2->getTime()[0]*3600 + t2->getTime()[1]*60  + t2->getTime()[2];

     if (openClose == open && state == 1){
        start_time = t2->getTime()[0]*3600 + t2->getTime()[1]*60  + t2->getTime()[2];
        state = 0;
     }
     if((cur_time-start_time) > (5 * 60)){
        cooling = false;
        char * message = wemosMessage();
     }
     if (openClose == closed && state == 0) {
         start_time = 0;
         state = 1;
         cooling = true;
         sendReceive(wemosMessage());
     }


}

