// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include "Socket.h"
#include "json.hpp"
using json = nlohmann::json;


using namespace std;
#define PORT 8080

int counter;
//Socket *sockets;

Socket sockets[7]; // NOLINT(cert-err58-cpp)

void discoverDevices();

void communicate(char* buffer,int valread);
void communicateBed(char* buffer, int valread);
void communicateChair(char* buffer, int valread);
void communicateLamp(char* buffer, int valread);
void communicatePillar(char* buffer, int valread);
void communicateWall(char* buffer, int valread);
void communicateFridge(char* buffer, int valread);
void communicateDoor(char* buffer, int valread);

bool checkConnectedDevices();

json toJson(string jsonString);
string toCharArray(json jsonObj);

int main(int argc, char const *argv[])
{
    counter = 0;
    discoverDevices();
    char buffer[1024] = {0};
    int valread;
//    if (!checkConnectedDevices()) {sendSimpleMessage(buffer,valread);return -1;}
    counter = 1;
    while(counter > 0) {
//        if (counter == 8) {counter = 1;}
        if (counter == 2) { break;}

        communicate(buffer, valread);
        printf("\n");
        counter++;
    }
    return 0;
}
json toJson(string jsonString) {
    json jsonObj;
    std::stringstream(jsonString) >> jsonObj;
    return jsonObj;
}
string toCharArray(json jsonObj) {
    std::string result = jsonObj.dump();
    return result;
}

bool checkConnectedDevices() {
    if (counter != 6) {
        printf("not all devices connected\n");
        return 0;
    }
    else {
        counter = 0;
        return 1;
    }
}
void discoverDevices() {
    int valread;
    const char *hello = "hello";
    char buffer[1024] = {0};
    const char *IPGROUP = "192.168.2.";
    char *IP;
    int Device;
    for (int x = 182; x < 185; x+=10) {
        stringstream ss;
        ss << IPGROUP << x;
        const std::string tmp = ss.str();
        IP = const_cast<char *>(tmp.c_str());

        Socket test(100,"test",IP);
        send(test.sock , hello , strlen(hello) , 0 );
        valread = read(test.sock , buffer, 1024);
//      Bed = 1;
//      Stoel = 2;
//      Schemerlamp = 3;
//      Zuil = 4;
//      Muur = 5;
//      Koelkast = 6;
//      Deur = 7;
        stringstream temp(buffer);
        temp >> Device;
        switch (Device) {
            case 1 : {
                Socket bed(1, "bed", IP);
                printf("Bed was made\n");
                sockets[1] = bed;
                counter++;
                break;
            }
            case 2 : {
                Socket chair(2, "chair", IP);
                printf("Chair was made");
                sockets[2] = chair;
                counter++;
                break;
            }
            case 3 : {
                Socket tableLamp(3,"tableLamp", IP);
                printf("Lamp was made");
                sockets[3] = tableLamp;
                counter++;
                break;
            }
            case 4 : {
                Socket pillar(1, "pillar", IP);
                printf("Pillar was made");
                sockets[4] = pillar;
                counter++;
                break;
            }
            case 5 : {
                Socket wall(1, "wall", IP);
                printf("Wall was made");
                sockets[5] = wall;
                counter++;
                break;
            }
            case 6 : {
                Socket fridge(1, "fridge", IP);
                printf("Fridge was made");
                sockets[6] = fridge;
                counter++;
                break;
            }
            case 7 : {
                Socket door(1, "door", IP);
                printf("Door was made");
                sockets[7] = door;
                counter++;
                break;
            }
            default: printf("Not found, help");
        }
        printf("Device search done\n");
    }
}

void communicate(char* buffer, int valread) {
    //dosomething
    switch (counter) {
        case 1: {
            communicateBed(buffer,valread);
        }
        case 2: {
            communicateChair(buffer, valread);
        }
        case 3: {
            communicateLamp(buffer, valread);
        }
        case 4: {
            communicatePillar(buffer, valread);
        }
        case 5: {
            communicateWall(buffer, valread);
        }
        case 6: {
            communicateFridge(buffer, valread);
        }
        case 7: {
            communicateDoor(buffer, valread);
        }
    }

}

bool x = true;
int y = 1;
u_int8_t z = 255;

void communicateBed(char* buffer, int valread) {
    json Message = {
            {"id",1},
            {"actuators", {
                          {"led", x}
                  }
            }
    };
    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
    valread = read(sockets[counter].sock, buffer, 1024);
    json Result = toJson(buffer);
    printf("Bed:\n");
    printf("ForceSensor: ");
    printf("%s\n",Result["sensors"]["forceSensor"].dump().c_str());
    printf("Button: ");
    printf("%s\n",Result["sensors"]["button"].dump().c_str());
    printf("\n");
}

void communicateChair(char* buffer, int valread) {
    json Message = {
            {"id",2},
            {"actuators", {
                          {"led", x},
                          {"Vibrator", x}
                  }
            }
    };
    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
    valread = read(sockets[counter].sock, buffer, 1024);
    json Result = toJson(buffer);
    printf("Chair:\n");
    printf("ForceSensor: ");
    printf("%s\n",Result["sensors"]["forceSensor"].dump().c_str());
    printf("Button: ");
    printf("%s\n",Result["sensors"]["button"].dump().c_str());
    printf("\n");
}

void communicateLamp(char* buffer, int valread) {
    json Message = {
            {"id",3},
            {"actuators", {
                          {"led", x}
                  }
            }
    };
    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
    valread = read(sockets[counter].sock, buffer, 1024);
    json Result = toJson(buffer);
    printf("Lamp:\n");
    printf("MotionSensor: ");
    printf("%s\n",Result["sensors"]["motionSensor"].dump().c_str());
    printf("Button: ");
    printf("%s\n",Result["sensors"]["button"].dump().c_str());
    printf("\n");
}

void communicatePillar(char* buffer, int valread) {
    json Message = {
            {"id",4},
            {"actuators", {
                          {"led", x},
                          {"buzzer",x}
                  }
            }
    };
    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
    valread = read(sockets[counter].sock, buffer, 1024);
    json Result = toJson(buffer);
    printf("Pillar:\n");
    printf("GasSensor: ");
    printf("%s\n",Result["sensors"]["gasSensor"].dump().c_str());
    printf("Button: ");
    printf("%s\n",Result["sensors"]["button"].dump().c_str());
    printf("\n");
}

void communicateWall(char* buffer, int valread) {
    json Message = {
            {"id",5},
            {"actuators", {
                          {"led", z},
                          {"window", x}
                  }
            }
    };
    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
    valread = read(sockets[counter].sock, buffer, 1024);
    json Result = toJson(buffer);
    printf("Wall:\n");
    printf("Dimmer: ");
    printf("%s\n",Result["sensors"]["dimmer"].dump().c_str());
    printf("LDR: ");
    printf("%s\n",Result["sensors"]["LDR"].dump().c_str());
    printf("\n");
}

void communicateFridge(char* buffer, int valread) {
    json Message = {
            {"id",6},
            {"actuators", {
                          {"cooling", x}
                  }
            }
    };
    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
    valread = read(sockets[counter].sock, buffer, 1024);
    json Result = toJson(buffer);
    printf("Fridge:\n");
    printf("Inside: ");
    printf("%s\n",Result["sensors"]["inside"].dump().c_str());
    printf("Outside :");
    printf("%s\n",Result["sensors"]["outside"].dump().c_str());
    printf("DoorOpen: ");
    printf("%s\n", Result["sensors"]["doorOpen"].dump().c_str());
    printf("\n");
}

void communicateDoor(char* buffer, int valread) {
    json Message = {
            {"id",7},
            {"actuators", {
                          {"led1", x},
                          {"led2", x},
                          {"servo", y}
                  }
            }
    };
    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
    valread = read(sockets[counter].sock, buffer, 1024);
    json Result = toJson(buffer);
    printf("Door:\n");
    printf("Button 1: ");
    printf("%s\n",Result["sensors"]["button1"].dump().c_str());
    printf("Button 2: ");
    printf("%s\n",Result["sensors"]["button2"].dump().c_str());
    printf("\n");
}
