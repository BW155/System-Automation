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
#include "../json/json.hpp"

using json = nlohmann::json;
using namespace std;
#define PORT 8080

class Socket {
private:
    int id;
    string name;
    const char *IP;
    bool connected;
public:
    int getId();
    int sock;
    bool getConnected();
    string getIP();
    string getName();
    void setName(string name_);
    void makeConnection();
    struct sockaddr_in sock_addr;
    char* sendReceive(char* message);

    Socket();
    Socket(int id_,string name_,const char *IP_);
};

#endif //SOCKET_SOCKET_H
