//
// Created by Zep on 16-12-19.
//
#include "fridge.h"

fridge::fridge(char * IP, webSocket *s) : domObject(s), cooling(false), thermometer1(0), thermometer2(0), openClose(0) {

}

void fridge::update(){
        static int prev_time;
        int start_time, cur_time;
        bool state = 0;

        fridge f1();
        TimeClass *t2 = f1().getTimePointer();
        t2 -> autoIncreaseTime();

        //Ask for current time in seconds
        cur_time = t2->getTime()[0]*3600 + t2->getTime()[1]*60  + t2->getTime()[2];

    /*If openClose = open && state = 1{
        start_time = t2->getTime()[0]*3600 + t2->getTime()[1]*60  + t2->getTime()[2];
        state = 0;
    }
     if((cur_time-start_time) > (5 * 60)){
        cooling = false
     }

     if openClose = gesloten && state = 0 {
        state = 1;
        cooling = true;
     }

    */
}

