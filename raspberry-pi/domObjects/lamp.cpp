// Created by LarsLinux on 16-12-19.
//
#include "lamp.h"

//Pi stuurt:		{"id":3, "actuators":{"led":x}}
//Wemos stuurt:	{"error":"err", "sensors":{"motionSensor":x, "button":x}}

Lamp::Lamp(const char * IP, webSocket *s, TimeClass *t):  led(false), motionSensor(false), domObject(s, t, 3){
    Socket temp(3, "tableLamp", IP);
    domObject::wemos = temp;
    startTime = 0;
}


void Lamp::update(){
    char * message;
    char * result;
    json jsonResult;
    stuurLamp();
    if(python->sendMessage(3)){
        result = python->receiveActuators(3);
        jsonResult = toJson(result);
        bool light = jsonResult["actuators"]["led"] == 1;
        if(light == led){

        }
        else{
            led = !led;
        }
    }
    message = wemosMessage();
    result = wemos.sendReceive(message);
    jsonResult = toJson(result);
    bool motion = jsonResult["sensors"]["motionSensor"] ==1;

    if(motion != motionSensor) {
        motionSensor = !motionSensor;
    }
    //doe iets
    python->sendAll(3, pythonMessage());

//    toLogFile();
}

json Lamp::pythonMessage(){
    json motionmsg = {
            {"actuators", {
                {"led",led}
                     }},
            {"sensors" , {
                 {"motionSensor",motionSensor}
                   }
                    }
    };
    return motionmsg;
}

char * Lamp::wemosMessage(){
    json ledmsg = {
            {"id", 3},
            {"actuators",{
                           {"led",led}
                   }
            }
    };
    char* ledMsg = toCharArray(ledmsg);
    return ledMsg;
}

void Lamp::stuurLamp(){
    int currentTime;
    domObject::timeObj->autoIncreaseTime();
    currentTime = domObject::timeObj->getTime()[0]*3600 + domObject::timeObj->getTime()[1]*60 + domObject::timeObj->getTime()[2];
    if (motionSensor){
        led = true;
        startTime = currentTime;

    }
    if(!motionSensor){
        if((currentTime - startTime) > (300)){  //5 minuten (5 x 60)
            led = false;
        }
    }
}

void Lamp::toLogFile() {
    //log
    ofstream myfile;
    myfile.open("log.txt", ios::out | ios::app);
    if (myfile.is_open()) {
        myfile << domObject::timeObj->getTime()[0] << ":" << domObject::timeObj->getTime()[1] << ":"
               << domObject::timeObj->getTime()[2] << "Lamp: " << pythonMessage() << endl;
        if  (myfile.bad()) {
            cout<<"write failed"<<endl;
        }

    }
    else {
        cout<<"file not found"<<endl;
    }
    myfile.close();
}