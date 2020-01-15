//
// Created by LarsLinux on 18-12-19.
//

#include <arpa/inet.h>
#include "Socket.h"
#include "webSocket.h"
#include "../json/json.hpp"

#define PORT2 9001

// constructor, make the websocket
webSocket::webSocket() {
    sock = 0;
    struct sockaddr_in temp;
    sock_addr = temp;
}

// function to change json object to char *
char* webSocket::toCharArray(json jsonObj) {
    std::string temp = jsonObj.dump();
    char *result = new char[temp.length()+1];
    strcpy(result, temp.c_str());
    return result;
}

// To make a new connection to the socket
void webSocket::makeConnection() {
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n webSocket creation error \n");
    }

    // set some variables for the socket connection
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT2);

    // check if the IP adress is correct
    if(inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported websocket\n");
    }

     // check if a connection can be made with the socket
    if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        printf("\nConnection Failed webSocket \n");
    }
}

// message type 1, ask if changes were made
bool webSocket::sendMessage(int id) {
    // type 1 message only sends id
    json message {
            {"id",id},
            {"type",1}
    };

    // make connection
    makeConnection();

    // make buffer
    char buffer[1024] = {0};

    // send message, receive a 0 or a 1
    send(sock, toCharArray(message), strlen(toCharArray(message)), 0);
    int valread = read(sock, buffer, 1024);

    // change char * to int
    int result = stoi(buffer);

    // close socket
    close(sock);

    // return true if result == 1
    return result == 1;
}

// funtion to send notifications to webserver
void webSocket::sendNotification(char *message) {
    // make connection
    makeConnection();

    // make buffer
    char buffer[1024] = {0};

    // send notifications
    send(sock, message, strlen(message), 0);
    int valread = read(sock, buffer, 1024);

    // close socket
    close(sock);
}

// message type 2, receive all actuator values changed on webserver
char* webSocket::receiveActuators(int id) {
    // type 2 message sends only id
    json message {
            {"id",id},
            {"type",2}
    };

    // make connection
    makeConnection();

    // make buffer
    char buffer[1024] = {0};

    // send id, receive actuators
    send(sock, toCharArray(message), strlen(toCharArray(message)), 0);
    int valread = read(sock, buffer, 1024);

    // get buffer
    char *result = buffer;

    // close socket
    close(sock);

    // return result
    return result;
}

// function type 3, to send all sensors and actuators
void webSocket::sendAll(int id, json everything) {

    // everything contains sensors and actuators
    json message = everything;

    // add id and type to message
    message["id"] = id;
    message["type"] = 3;

    // make connection
    makeConnection();

    // make buffer
    char buffer[1024] = {0};

    // send message
    send(sock, toCharArray(message), strlen(toCharArray(message)), 0);
    int valread = read(sock, buffer, 1024);

    // close socket
    close(sock);
}
