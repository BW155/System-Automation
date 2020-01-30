//
// Created by programmer on 04-12-19.
//

#ifndef SOCKET_H
#define SOCKET_H

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
    const char *IP;
    bool connected;

public:
    int sock;
    bool getConnected();
    void makeConnection();
    struct sockaddr_in sock_addr;
    char* sendReceive(char* message);

    Socket();
    Socket(int id_, const char *IP_);
};

#endif //SOCKET_H
