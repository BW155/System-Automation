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

Socket bedje; // NOLINT(cert-err58-cpp)

void discoverDevices();
void communicate(char*,int);
bool checkConnectedDevices();
json toJson(string);
string toCharArray(json);

void sendSimpleMessage(char*,int,Socket);

int main(int argc, char const *argv[])
{
    counter = 0;
    discoverDevices();
    char buffer[1024] = {0};
    int valread;
    if (!checkConnectedDevices()) {sendSimpleMessage(buffer,valread,bedje);return -1;}
    while(counter >= 0) {
        if (counter == 7) {counter = 0;}

        communicate(buffer, valread);

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
        printf("not all devices connected");
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
    for (int x = 182; x < 191; x+=10) {
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
                printf("Bed was made");
//                sockets[counter] = bed;
                bedje = bed;
                counter++;
                break;
            }
            case 2 : {
                Socket chair(2, "chair", IP);
                printf("Chair was made");
//                sockets[counter] = chair;
                counter++;
                break;
            }
            case 3 : {
                Socket tableLamp(3,"tableLamp", IP);
                printf("Lamp was made");
//                sockets[counter] = tableLamp;
                counter++;
                break;
            }
            case 4 : {
                Socket pillar(1, "pillar", IP);
                printf("Pillar was made");
//                sockets[counter] = pillar;
                counter++;
                break;
            }
            case 5 : {
                Socket wall(1, "wall", IP);
                printf("Wall was made");
//                sockets[counter] = wall;
                counter++;
                break;
            }
            case 6 : {
                Socket fridge(1, "fridge", IP);
                printf("Fridge was made");
//                sockets[counter] = fridge;
                counter++;
                break;
            }
            case 7 : {
                Socket door(1, "door", IP);
                printf("Door was made");
//                sockets[counter] = door;
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
//    send(sockets[counter].sock , "iets hier" , strlen("ja lengte") , 0 );
//    valread = read(sockets[counter].sock , buffer, 1024);
}

void sendSimpleMessage(char *buffer, int valread, Socket bedje) {
    json Message = {
            {"id", 1},
            {"actuators", {
                                  {"led", 1}
                          }
            }
    };
    send(bedje.sock, toCharArray(Message).c_str(), strlen(toCharArray(Message).c_str()), 0);
    valread = read(bedje.sock, buffer, 1024);
    printf("%s/n", buffer);
}
