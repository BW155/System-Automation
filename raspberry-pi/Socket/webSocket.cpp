//
// Created by LarsLinux on 18-12-19.
//

#include <arpa/inet.h>
#include "Socket.h"
#include "webSocket.h"

webSocket::webSocket() {
    sock = 0;
    char *IP = "xo";
    struct sockaddr_in temp;
    sock_addr = temp;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
    }
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(8080);
    if(inet_pton(AF_INET, IP, &sock_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
    }

    if (connect(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr)) < 0) {
        printf("\nConnection Failed \n");
    }
}

void webSocket::send(char *sensors) {

}

json webSocket::receive() {
    return json();
}
