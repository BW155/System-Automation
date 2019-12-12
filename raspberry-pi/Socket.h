//
// Created by programmer on 04-12-19.
//

#ifndef SOCKET_SOCKET_H
#define SOCKET_SOCKET_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;
#define PORT 8080

class Socket {
private:
    int id;
    string name;
    char *IP;
public:
    int getId();
    int sock;
    string getIP();
    string getName();
    void setName(string name_);
    void connectionTest();
    struct sockaddr_in sock_addr;

    Socket();
    Socket(int id_,string name_,char *IP_);
};

#endif //SOCKET_SOCKET_H
