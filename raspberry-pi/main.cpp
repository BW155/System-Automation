// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include "Socket.h"
#include "json.hpp"
#include <netinet/tcp.h>
using json = nlohmann::json;


using namespace std;
#define PORT 8080

int counter;
//Socket *sockets;

Socket sockets[8]; // NOLINT(cert-err58-cpp)

void discoverDevices();

void communicate();
void communicateBed();
void communicateChair();
void communicateLamp();
void communicatePillar();
void communicateWall();
void communicateFridge();
void communicateDoor();

bool checkConnectedDevices();

json toJson(char* jsonString);
char * toCharArray(json jsonObj);

int main(int argc, char const *argv[])
{
    counter = 0;
    discoverDevices();
    cout<<"\n"<<endl;
//    if (!checkConnectedDevices()) {sendSimpleMessage(buffer,valread);return -1;}
    counter = 1;
    while(true) {
//        if (counter == 8) {counter = 1;}
//        cout<<"loopie"<<endl;
        communicate();
//        cout<<"\n"<<endl;
        //counter++;
        sleep(5);

    }
    return 0;
}
json toJson(char* jsonString) {
    json jsonObj;
    std::stringstream(jsonString)>>jsonObj;
    return jsonObj;
}
char* toCharArray(json jsonObj) {
    std::string temp = jsonObj.dump();
    char *result = new char[temp.length()+1];
    strcpy(result, temp.c_str());
    return result;
}

bool checkConnectedDevices() {
    if (counter != 6) {
        cout<<"not all devices connected\n"<<endl;
        return 0;
    }
    else {
        counter = 0;
        return 1;
    }
}
void discoverDevices() {

    const char *IPGROUP = "192.168.2.";
    char *IP;
    int Device;
    for (int x = 192; x < 193; x+=10) {
        int valread;
        const char *hello = "hello";
        char buffer[1024] = {0};
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
                cout<<"Bed was made\n"<<endl;
                sockets[1] = bed;
                counter++;
                break;
            }
            case 2 : {
                Socket chair(2, "chair", IP);
                cout<<"Chair was made\n"<<endl;
                sockets[2] = chair;
                counter++;
                break;
            }
            case 3 : {
                Socket tableLamp(3, "tableLamp", IP);
                cout<<"Lamp was made\n"<<endl;
                sockets[3] = tableLamp;
                counter++;
                break;
            }
            case 4 : {
                Socket pillar(1, "pillar", IP);
                cout<<"Pillar was made\n"<<endl;
                sockets[4] = pillar;
                counter++;
                break;
            }
            case 5 : {
                Socket wall(1, "wall", IP);
                cout<<"Wall was made\n"<<endl;
                sockets[5] = wall;
                counter++;
                break;
            }
            case 6 : {
                Socket fridge(1, "fridge", IP);
                cout<<"Fridge was made\n"<<endl;
                sockets[6] = fridge;
                counter++;
                break;
            }
            case 7 : {
                Socket door(1, "door", IP);
                cout<<"Door was made\n"<<endl;
                sockets[7] = door;
                counter++;
                break;
            }
            default:
                cout<<"Not found, help\n"<<endl;
        }
    }
    cout<<"Device search done\n"<<endl;
}

void communicate() {
    //dosomething
    cout<<"naloopiiei"<<endl;
    switch (1) {
        case 1: {
            communicateBed();
            cout<<"comwerk"<<endl;
            break;
        }
        case 2: {
            communicateChair();
            break;
        }
//        case 3: {
//            communicateLamp();
//            break;
//        }
//        case 4: {
//            communicatePillar();
//            break;
//        }
//        case 5: {
//            communicateWall();
//            break;
//        }
//        case 6: {
//            communicateFridge();
//            break;
//        }
//        case 7: {
//            communicateDoor();
//            break;
//        }
        default: cout<<"help"<<endl;
    }

}

bool x = true;
int y = 1;
u_int8_t z = 255;

void communicateBed() {
    char buffer[1024] = {0};
    int valread;
    json Message = {
            {"id",1},
            {"actuators", {
                          {"led", x}
                  }
            }
    };
//    cout<<"3"<<endl;
    char *message = toCharArray(Message);
//    cout<<message<<endl;
    sockets[1].connectionTest();
    send(sockets[1].sock, message, strlen(message), 0);
//    cout<<"tussen"<<endl;
    valread = read(sockets[1].sock, buffer, 1024);
//    cout<<"na"<<endl;
    close(sockets[1].sock);
    if (buffer[0] == NULL) {

    }
    else {
//        cout<<buffer<<endl;
        json Result = toJson(buffer);
//        cout<<Result<<endl;
        cout<<"Bed:"<<endl;
        cout<<"ForceSensor: "<<endl;
        cout<<Result["sensors"]["forceSensor"]<<endl;
        cout<<("Button: ")<<endl;
        cout<<Result["sensors"]["button"]<<endl;
        cout<<"\n"<<endl;
    }
}

void communicateChair() {
    char buffer[1024] = {0};
    int valread;
    json Message = {
            {"id",2},
            {"actuators", {
                          {"led", x},
                          {"Vibrator", x}
                  }
            }
    };
    send(sockets[counter].sock, toCharArray(Message), strlen(toCharArray(Message)), 0);
    valread = read(sockets[counter].sock, buffer, 1024);
    json Result = toJson(buffer);
    cout<<"Bed:"<<endl;
    cout<<"ForceSensor: "<<endl;
    cout<<Result["sensors"]["ForceSensor"]<<endl;
    cout<<("Button:")<<endl;
    cout<<Result["sensors"]["PushButton"]<<endl;
    cout<<"\n"<<endl;
}

//void communicateLamp() {
//    char *buffer = {0};
//    int valread;
//    json Message = {
//            {"id",3},
//            {"actuators", {
//                          {"led", x}
//                  }
//            }
//    };
//    send(sockets[counter].sock, toCharArray(Message), strlen(toCharArray(Message)), 0);
//    valread = read(sockets[counter].sock, buffer, 1024);
//    json Result = toJson(buffer);
//    printf("Lamp:\n");
//    printf("MotionSensor: \n");
//    printf("%s\n",Result["sensors"]["motionSensor"].dump().c_str());
//    printf("Button: \n");
//    printf("%s\n",Result["sensors"]["button"].dump().c_str());
//    printf("\n");
//}
//
//void communicatePillar() {
//    char *buffer = {0};
//    int valread;
//    json Message = {
//            {"id",4},
//            {"actuators", {
//                          {"led", x},
//                          {"buzzer",x}
//                  }
//            }
//    };
//    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
//    valread = read(sockets[counter].sock, buffer, 1024);
//    json Result = toJson(buffer);
//    printf("Pillar:\n");
//    printf("GasSensor: \n");
//    printf("%s\n",Result["sensors"]["gasSensor"].dump().c_str());
//    printf("Button: \n");
//    printf("%s\n",Result["sensors"]["button"].dump().c_str());
//    printf("\n");
//}
//
//void communicateWall() {
//    char *buffer = {0};
//    int valread;
//    json Message = {
//            {"id",5},
//            {"actuators", {
//                          {"led", z},
//                          {"window", x}
//                  }
//            }
//    };
//    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
//    valread = read(sockets[counter].sock, buffer, 1024);
//    json Result = toJson(buffer);
//    printf("Wall:\n");
//    printf("Dimmer: \n");
//    printf("%s\n",Result["sensors"]["dimmer"].dump().c_str());
//    printf("LDR: \n");
//    printf("%s\n",Result["sensors"]["LDR"].dump().c_str());
//    printf("\n");
//}
//
//void communicateFridge() {
//    char *buffer = {0};
//    int valread;
//    json Message = {
//            {"id",6},
//            {"actuators", {
//                          {"cooling", x}
//                  }
//            }
//    };
//    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
//    valread = read(sockets[counter].sock, buffer, 1024);
//    json Result = toJson(buffer);
//    printf("Fridge:\n");
//    printf("Inside: \n");
//    printf("%s\n",Result["sensors"]["inside"].dump().c_str());
//    printf("Outside: \n");
//    printf("%s\n",Result["sensors"]["outside"].dump().c_str());
//    printf("DoorOpen: \n");
//    printf("%s\n", Result["sensors"]["doorOpen"].dump().c_str());
//    printf("\n");
//}
//
//void communicateDoor() {
//    char *buffer = {0};
//    int valread;
//    json Message = {
//            {"id",7},
//            {"actuators", {
//                          {"led1", x},
//                          {"led2", x},
//                          {"servo", y}
//                  }
//            }
//    };
//    send(sockets[counter].sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
//    valread = read(sockets[counter].sock, buffer, 1024);
//    json Result = toJson(buffer);
//    printf("Door:\n");
//    printf("Button 1: \n");
//    printf("%s\n",Result["sensors"]["button1"].dump().c_str());
//    printf("Button 2: \n");
//    printf("%s\n",Result["sensors"]["button2"].dump().c_str());
//    printf("\n");
//}
