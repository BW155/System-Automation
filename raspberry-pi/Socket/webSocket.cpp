//
// Created by LarsLinux on 18-12-19.
//

#include <arpa/inet.h>
#include "Socket.h"
#include "webSocket.h"
#include "../json/json.hpp"

#define PORT 9001



webSocket::webSocket() {
    sock = 0;
    char *IP = "xo";
    struct sockaddr_in temp;
    sock_addr = temp;
    makeConnection();
}

char* webSocket::toCharArray(json jsonObj) {
    std::string temp = jsonObj.dump();
    char *result = new char[temp.length()+1];
    strcpy(result, temp.c_str());
    return result;
}

void webSocket::makeConnection() {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr)<=0)
    {
//        printf("\nInvalid address/ Address not supported \n");
    }

    if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }
}

bool webSocket::sendMessage(int id) {
    json message {
            {"id",id},
            {"type",1}
    };
    makeConnection();
    char buffer[1024] = {0};
    send(sock, toCharArray(message), strlen(toCharArray(message)), 0);
    int valread = read(sock, buffer, 1024);
    close(sock);
    return buffer[0] != 0;
}

char* webSocket::sendMessage(char *sensors) {
    makeConnection();
    char buffer[1024] = {0};
    send(sock, sensors, strlen(sensors), 0);
    int valread = read(sock, buffer, 1024);
    char *result = buffer;
    close(sock);
    return result;
}

char* webSocket::receive(int id) {
    json message{
            {"id",id},
            {"type", 3}
    };
    makeConnection();
    char buffer[1024] = {0};
    send(sock, toCharArray(message), strlen(toCharArray(message)), 0);
    int valread = read(sock, buffer, 1024);
    char *result = buffer;
    close(sock);
    return result;
}
