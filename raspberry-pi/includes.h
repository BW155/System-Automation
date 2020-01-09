#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include "Socket/Socket.h"
#include "Socket/webSocket.h"
#include "json/json.hpp"
#include <netinet/tcp.h>
#include "timeKeeper.h"
#include <iostream>
#include <fstream>

#include "domObjects/bed.h"
#include "domObjects/chair.h"
#include "domObjects/lamp.h"
#include "domObjects/wall.h"
#include "domObjects/pillar.h"
#include "domObjects/fridge.h"
#include "domObjects/door.h"
#include "domObjects/domObject.h"


//void coutBed(json Result) {
//    cout<<"Bed:"<<endl;
//    cout<<"ForceSensor: "<<Result["sensors"]["forceSensor"]<<endl;
//    cout<<"Button: "<<Result["sensors"]["button"]<<endl;
//    cout<<"\n"<<endl;
//}
//void coutChair(json Result) {
//    cout<<"Chair:"<<endl;
//    cout<<"ForceSensor: "<<Result["sensors"]["forceSensor"]<<endl;
//    cout<<"Button: "<<Result["sensors"]["button"]<<endl;
//    cout<<"\n"<<endl;
//}
//void coutLamp(json Result) {
//    cout<<"Lamp:"<<endl;
//    cout<<"MotionSensor: "<<Result["sensors"]["motionSensor"]<<endl;
//    cout<<"\n"<<endl;
//}
//void coutPillar(json Result) {
//    cout<<"Pillar:"<<endl;
//    cout<<"GasSensor: "<<Result["sensors"]["gasSensor"]<<endl;
//    cout<<"Button: "<<Result["sensors"]["button"]<<endl;
//    cout<<"\n"<<endl;
//}
//void coutWall(json Result) {
//    cout<<"Wall:"<<endl;
//    cout<<"Dimmer: "<<Result["sensors"]["dimmer"]<<endl;
//    cout<<"LDR: "<<Result["sensors"]["LDR"]<<endl;
//    cout<<"\n"<<endl;
//}
//void coutFridge(json Result) {
//    cout<<"Fridge:"<<endl;
//    cout<<"Thermometer 1: "<<Result["sensors"]["thermometer1"]<<endl;
//    cout<<"Thermometer 2: "<<Result["sensors"]["thermometer2"]<<endl;
//    cout<<"Door open: "<<Result["sensors"]["openClose"]<<endl;
//    cout<<"\n"<<endl;
//}
//void coutDoor(json Result) {
//    cout<<"Door:"<<endl;
//    cout<<"Button 1: "<<Result["sensors"]["button1"]<<endl;
//    cout<<"Button 2: "<<Result["sensors"]["button2"]<<endl;
//    cout<<"\n"<<endl;
//}