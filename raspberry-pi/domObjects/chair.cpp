//
// Created by LarsLinux on 16-12-19.
//
#include "chair.h"
#include "../json/json.hpp"

using json = nlohmann::json;

Chair::Chair(const char *IP, webSocket *w, TimeClass *t) : domObject(w, t, 2) {
    led = false;
    forceSensor = 0;
    button = false;
    vibrator = false;
    timeOut = false;
    startTime = 0;
    counter = 0;
    updateForce = 0;
    startTimeMedication = 0;
    lastNotification = 0;

    Socket temp(2,"Chair",IP);
    domObject::wemos = temp;
}

void Chair::update() {
    char* result;
    json jsonResult;
    int currentTime;

    domObject::timeObj->autoIncreaseTime();

    //Current time in seconds;
    currentTime = domObject::timeObj->getTimeSeconds();

    if (startTimeMedication == 0 && lastNotification != 1) {
        startTimeMedication = currentTime + 1;
        lastNotification = 1;
        json message = {
                {"type", 4},
                {"id", 5}
        };
        cout<<"MEDICATIE"<<endl;
        python->sendNotification(toCharArray(message));
    } else if (currentTime-startTimeMedication >= 599 && currentTime-startTimeMedication < 620 && lastNotification != 2) {
        lastNotification = 2;
        json message = {
                {"type", 4},
                {"id", 6}
        };
        cout<<"MEDICATIE 2"<<endl;
        python->sendNotification(toCharArray(message));
    } else if (currentTime-startTimeMedication >= 1199&& currentTime-startTimeMedication < 1220 && lastNotification != 3) {
        lastNotification = 3;
        json message = {
                {"type", 4},
                {"id", 7}
        };
        cout<<"MEDICATIE 3"<<endl;
        python->sendNotification(toCharArray(message));
    } else if (currentTime-startTimeMedication >= 1799&& currentTime-startTimeMedication < 1820 && lastNotification != 4) {
        lastNotification = 4;
        json message = {
                {"type", 4},
                {"id", 8}
        };
        cout<<"MEDICATIE 4"<<endl;
        python->sendNotification(toCharArray(message));
        if (currentTime-startTimeMedication >= 2399 && currentTime-startTimeMedication < 2420) {
            startTimeMedication = 0;
        }
    }
    result = wemos.sendReceive(wemosMessage());
    if (result == NULL) {
        cout<<"error receiving"<<endl;
    }
    else {
        jsonResult = toJson(result);
        updateAttributes(jsonResult);
    }
    cout<<"tijd: "<<currentTime<<endl;


    if (updateForce - forceSensor > 300) {
        counter++;
        cout<<counter<<endl;
        if (counter == 1) {
            startTime = domObject::timeObj->getTimeSeconds();
        }
    }
    else if (currentTime - startTime > 600) {
        counter = 0;
        startTime = currentTime;
    }
    else if (counter >= 5) {
        cout<<"epsoilepsieboy"<<endl;
        counter = 0;
        startTime = currentTime;
        json message = {
                {"type", 4},
                {"id", 0}
        };
        python->sendNotification(toCharArray(message));
    }

    //30 min auto massage
    //10 because of safety for potentiol fluctuation in value from 0 - 1
    if(forceSensor <= 10) {
        vibrator = false;
        start_time_30min_check = currentTime;
        start_time_max_massage = currentTime;
    }

    if((currentTime-start_time_30min_check) > (30 * 60)){
        //60 seconds because time multiplier is above a minute. 2 minute pulse is 2 seconds real time vibrator pulse
        if((currentTime-start_time_30min_check) > ((30 * 60)+ 120)) {
            vibrator = false;
        }
        else {
            vibrator = true;
        }
    }

    //Chair massage
    if(forceSensor > 10) {
        if (button && !timeOut&& !vibrator) {
            vibrator = true;

        }
        else if ((currentTime - start_time_max_massage) > (5 * 60)&& vibrator) {
            vibrator = false;
            timeOut = true;
        }
    }
    if(timeOut){
        if((currentTime - start_timeOut) > (5 * 60))
            timeOut = false;
    }else{
        start_timeOut = currentTime;
    }

//    toLogFile();
//    usleep(100000);
}

char* Chair::wemosMessage() {
    json message = {
            {"id",2},
            {"actuators", {
                          {"led", led},
                          {"vibrator", vibrator }
                  }
            }
    };
    return toCharArray(message);
}

json Chair::pythonMessage() {
    json message = {
            {"actuators", {
                                  {"vibrator", vibrator},
                                  {"led", led}
                          }
            },
            {"sensors", {
                                  {"forceSensor", forceSensor},
                                  {"button", button}
                          }
            }
    };
    return message;
}

void Chair::updateAttributes(json result) {
    forceSensor = updateForce;
    updateForce = result["sensors"]["forceSensor"];
    button = result["sensors"]["button"];
    python->sendAll(2,pythonMessage());
}

void Chair::toLogFile() {
    //log
    ofstream myfile;
    myfile.open("log.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << domObject::timeObj->getTimeString() << "Chair: " << pythonMessage() << endl;
        if  (myfile.bad()) {
            cout<<"write failed"<<endl;
        }

    }
    else {
        cout<<"file not found"<<endl;
    }
    myfile.close();
}