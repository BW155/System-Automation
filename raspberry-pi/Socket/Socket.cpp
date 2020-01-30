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

// Empty constructor
Socket::Socket() {connected = 0;}

// Actual constructor, initiate variables
Socket::Socket(int id_, const char *IP_) {
    id = id_;
    IP = IP_;
    sock = 0;
    struct sockaddr_in temp;
    sock_addr = temp;

    // First a check whether the socket was made correctly
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }

    // set some variables for the socket connection
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);

    // check if the IP adress is correct
    if(inet_pton(AF_INET, IP, &sock_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
    }

    // check if a connection can be made with the socket
    connected = connect(sock, (struct sockaddr *) &sock_addr, sizeof(sock_addr)) >= 0;

}

// To make a new connection to the socket
void Socket::makeConnection() {
    // First a check whether the socket was made correctly
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }

    // set some variables for the socket connection
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);

    // check if the IP adress is correct
    if(inet_pton(AF_INET, IP, &sock_addr.sin_addr)<=0)
    {
//        printf("\nInvalid address/ Address not supported \n");
    }

    // check if a connection can be made with the socket
    if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0)
    {
        printf("\nConnection Failed \n");
    }
}

// get the value of connected
bool Socket::getConnected() {
    return connected;
}

// function to send actuators to wemos, and receive sensors
char* Socket::sendReceive(char *message) {

    char *result;

    // make connection
    makeConnection();

    // make the buffer
    char buffer[1024] = {0};

    // send message
    send(sock, message, strlen(message), 0);

    // receive message
    int valread = read(sock, buffer, 1024);
    result = buffer;

    // close the socket
    close(sock);

    // return result
    return result;
}


