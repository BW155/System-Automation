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

using namespace std;
#define PORT 8080
Socket::Socket() {}
Socket::Socket(int id_, string name_, char *IP_) {
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
    }
}
int Socket::getId() {return id;}
string Socket::getIP() {return IP;}
string Socket::getName() {return name;}
void Socket::setName(string name_) {name = name_;}


