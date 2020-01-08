//
// Created by LarsLinux on 18-12-19.
//

#include <arpa/inet.h>
#include "Socket.h"
#include "webSocket.h"
#include "../json/json.hpp"

#define PORT2 9001



webSocket::webSocket() {
    sock = 0;
    struct sockaddr_in temp;
    sock_addr = temp;
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
    else {
        cout<<"Socket Created"<<endl;
    }
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT2);
    if(inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
    }
    else {
        cout<<"adress supported"<<endl;
    }

    if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        printf("\nConnection Failed webSocket \n");
    }
    else {
        cout<<"connection made"<<endl;
    }
}

bool webSocket::sendMessage(int id) {
    json message {
            {"id",id},
            {"type",1}
    };
    makeConnection();
    char buffer[1024] = {0};
    cout<<"sending"<<endl;
    send(sock, toCharArray(message), strlen(toCharArray(message)), 0);
    cout<<"receiving"<<endl;
    int valread = read(sock, buffer, 1024);
    close(sock);
    return buffer[0] != 0;
}

char* webSocket::receiveActuators(int id) {
    json message {
            {"id",id},
            {"type",2}
    };
    makeConnection();
    char buffer[1024] = {0};
    send(sock, toCharArray(message), strlen(toCharArray(message)), 0);
    int valread = read(sock, buffer, 1024);
    char *result = buffer;
    close(sock);
    return result;
}

void webSocket::sendAll(int id, json everything) {
    json message = everything;
    message["id"] = id;
    message["type"] = 3;
    makeConnection();
    char buffer[1024] = {0};
    send(sock, toCharArray(message), strlen(toCharArray(message)), 0);
    int valread = read(sock, buffer, 1024);
    close(sock);
}
