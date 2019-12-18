//
// Created by LarsLinux on 18-12-19.
//

#ifndef SOCKET_WEBSOCKET_H
#define SOCKET_WEBSOCKET_H

#include <netinet/in.h>
#include "../json/json.hpp"

using json = nlohmann::json;

class webSocket {
public:
    int sock;
    sockaddr_in sock_addr;
    char* sendMessage(char *sensors);
    bool sendMessage(int id);
    char* receive(int id);
    void makeConnection();
    char *toCharArray(json jsonObj);
    webSocket();

};
#endif //SOCKET_WEBSOCKET_H
