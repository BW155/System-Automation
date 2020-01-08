//
// Created by programmer on 04-12-19.
//
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
#include "Socket.h"

using json = nlohmann::json ;
using namespace std;
#define PORT 8080
Socket::Socket() {connected = 0;}
Socket::Socket(int id_, string name_,const char *IP_) {
    id = id_;
    IP = IP_;
    name = name_;
    sock = 0;
    struct sockaddr_in temp;
    sock_addr = temp;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, IP, &sock_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
    }

    if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        connected = false;
    }
    else {
        connected = true;
    }

}
int Socket::getId() {return id;}
string Socket::getIP() {return IP;}
string Socket::getName() {return name;}
void Socket::setName(string name_) {name = name_;}

void Socket::makeConnection() {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, IP, &sock_addr.sin_addr)<=0)
    {
//        printf("\nInvalid address/ Address not supported \n");
    }

    if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }
}

bool Socket::getConnected() {
    return connected;
}

char* Socket::sendReceive(char *message) {
    char *temp;
    makeConnection();
    cout<<"twee"<<endl;
    char buffer[1024] = {0};
    send(sock, message, strlen(message), 0);
    cout<<"twwee.5"<<endl;
    int valread = read(sock, buffer, 1024);
    temp = buffer;
    close(sock);
//    if (buffer[0] == NULL) {
//        return "-1";
//    }
//    else {
        cout<<"drie"<<endl;
        return temp;
//    }
}


