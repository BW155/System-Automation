// Lars Hartog
#include <domObjects/fridge.h>
#include "includes.h"


using json = nlohmann::json;
using namespace std;

#define PORT 9001

int counter;
Socket sockets[8]; // NOLINT(cert-err58-cpp)

json toJson(char* jsonString) {
    json jsonObj;
    std::stringstream(jsonString)>>jsonObj;
    return jsonObj;
}
char* toCharArray(json jsonObj) {
    std::string temp = jsonObj.dump();
    char *result = new char[temp.length()+1];
    strcpy(result, temp.c_str());
    return result;
}

bool checkConnectedDevices() {
    if (counter != 6) {
        cout<<"not all devices connected\n"<<endl;
        return 0;
    }
    else {
        counter = 0;
        return 1;
    }
}
void discoverDevices() {
    TimeClass obj1 (5,0,0,0);

    for (int x = 1; x < 8; x++) {
        sockets[x] = Socket();
    }
    const char *IPGROUP = "192.168.2.";
    char *IP;
    int Device;
    for (int x = 180; x < 200; x+=1) {
        int valread;
        const char *hello = "hello";
        char buffer[1024] = {0};
        stringstream ss;
        ss << IPGROUP << x;
        const string tmp = ss.str();
        const char *IP = tmp.c_str();

        Socket test(100,"test",IP);
        if (test.getConnected()) {
            send(test.sock, hello, strlen(hello), 0);
            valread = read(test.sock, buffer, 1024);
//      Bed = 1;
//      Stoel = 2;
//      Schemerlamp = 3;
//      Zuil = 4;
//      Muur = 5;
//      Koelkast = 6;
//      Deur = 7;
            stringstream temp(buffer);
            temp >> Device;
            switch (Device) {
                case 1 : {
                    Socket bed(1, "bed", IP);
                    cout << "Bed was made\n" << endl;
                    sockets[1] = bed;
                    counter++;
                    break;
                }
                case 2 : {
                    Socket chair(2, "chair", IP);
                    cout << "Chair was made\n" << endl;
                    sockets[2] = chair;
                    counter++;
                    break;
                }
                case 3 : {
                    Socket tableLamp(3, "tableLamp", IP);
                    cout << "Lamp was made\n" << endl;
                    sockets[3] = tableLamp;
                    counter++;
                    break;
                }
                case 4 : {
                    Socket pillar(1, "pillar", IP);
                    cout << "Pillar was made\n" << endl;
                    sockets[4] = pillar;
                    counter++;
                    break;
                }
                case 5 : {
                    Socket wall(1, "wall", IP);
                    cout << "Wall was made\n" << endl;
                    sockets[5] = wall;
                    counter++;
                    break;
                }
                case 6 : {
                    Socket fridge(1, "fridge", IP);
                    cout << "Fridge was made\n" << endl;
                    sockets[6] = fridge;
                    counter++;
                    break;
                }
                case 7 : {
                    Socket door(1, "door", IP);
                    cout << "Door was made\n" << endl;
                    sockets[7] = door;
                    counter++;
                    break;
                }
                default:
                    cout << "Not found, help\n" << endl;
            }
        }
    }
    cout<<"Device search done\n"<<endl;
}

json sendReceive(char *message, int valread, char *buffer) {
    sockets[counter].makeConnection();
    send(sockets[counter].sock, message, strlen(message), 0);
    valread = read(sockets[counter].sock, buffer, 1024);
    close(sockets[counter].sock);
    if (buffer[0] == NULL) {
        return "-1";
    }
    else {
        json Result = toJson(buffer);
        return Result;
    }
}

char *bedMessage(bool x) {
    json Message = {
            {"id",1},
            {"actuators", {
                          {"led", x}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}
char *chairMessage(bool x) {
    json Message = {
            {"id",2},
            {"actuators", {
                          {"led", x},
                          {"vibrator", x}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}
char *lampMessage(bool x) {
    json Message = {
            {"id",3},
            {"actuators", {
                          {"led", x}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}
char *pillarMessage(bool x) {
    json Message = {
            {"id",4},
            {"actuators", {
                          {"led", x},
                          {"buzzer", x}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}
char *wallMessage(bool x, uint8_t z) {
    json Message = {
            {"id",5},
            {"actuators", {
                          {"led", z},
                          {"window", x}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}
char *doorMessage(bool x) {
    json Message = {
            {"id",7},
            {"actuators", {
                          {"led1", x},
                          {"led2", x},
                          {"servo", x}
                  }
            }
    };
    char *message = toCharArray(Message);
    return message;
}

void coutBed(json Result) {
    cout<<"Bed:"<<endl;
    cout<<"ForceSensor: "<<Result["sensors"]["forceSensor"]<<endl;
    cout<<"Button: "<<Result["sensors"]["button"]<<endl;
    cout<<"\n"<<endl;
}
void coutChair(json Result) {
    cout<<"Chair:"<<endl;
    cout<<"ForceSensor: "<<Result["sensors"]["forceSensor"]<<endl;
    cout<<"Button: "<<Result["sensors"]["button"]<<endl;
    cout<<"\n"<<endl;
}
void coutLamp(json Result) {
    cout<<"Lamp:"<<endl;
    cout<<"MotionSensor: "<<Result["sensors"]["motionSensor"]<<endl;
    cout<<"\n"<<endl;
}
void coutPillar(json Result) {
    cout<<"Pillar:"<<endl;
    cout<<"GasSensor: "<<Result["sensors"]["gasSensor"]<<endl;
    cout<<"Button: "<<Result["sensors"]["button"]<<endl;
    cout<<"\n"<<endl;
}
void coutWall(json Result) {
    cout<<"Wall:"<<endl;
    cout<<"Dimmer: "<<Result["sensors"]["dimmer"]<<endl;
    cout<<"LDR: "<<Result["sensors"]["LDR"]<<endl;
    cout<<"\n"<<endl;
}
void coutFridge(json Result) {
    cout<<"Fridge:"<<endl;
    cout<<"Thermometer 1: "<<Result["sensors"]["thermometer1"]<<endl;
    cout<<"Thermometer 2: "<<Result["sensors"]["thermometer2"]<<endl;
    cout<<"Door open: "<<Result["sensors"]["openClose"]<<endl;
    cout<<"\n"<<endl;
}
void coutDoor(json Result) {
    cout<<"Door:"<<endl;
    cout<<"Button 1: "<<Result["sensors"]["button1"]<<endl;
    cout<<"Button 2: "<<Result["sensors"]["button2"]<<endl;
    cout<<"\n"<<endl;
//    redis.set("Deur.led.1", "test");
}
bool x = true;
void communicate() {
    char buffer[1024] = {0};
    int valread;
    char *message;
    json result;


    int y = 1;
    u_int8_t z = 255;

    switch (counter) {
        case 1: {
            x = !x;
            message = bedMessage(x);
            result = sendReceive(message, valread, buffer);
            coutBed(result);
            break;
        }
        case 2: {
            message =chairMessage(x);
            result = sendReceive(message, valread, buffer);
            coutChair(result);
            break;
        }
        case 3: {
            message =lampMessage(x);
            result = sendReceive(message, valread, buffer);
            coutLamp(result);
            break;
        }
        case 4: {
            message =pillarMessage(x);
            result = sendReceive(message, valread, buffer);
            coutPillar(result);
            break;
        }
        case 5: {
            message =wallMessage(x,y);
            result = sendReceive(message, valread, buffer);
            coutWall(result);
            break;
        }
        case 6: {
            message =fridgeMessage(x);
            result = sendReceive(message, valread, buffer);
            coutFridge(result);
            break;
        }
        case 7: {
            // get value from redis database
//            bool temp = 0;
//            auto val2 = redis.get("deur");
//            if (val2->compare("open")) {
//                temp = 1;
//            }
//            else if (val2->compare("closed")) {
//                temp = 0;
//            }
//            else {
//                cout << "faal" << endl;
//            }
            message =doorMessage(x);
            result = sendReceive(message, valread, buffer);
            coutDoor(result);
            break;
        }
        default: cout<<"help"<<endl;
    }

}
int main(int argc, char const *argv[])
{
//    counter = 0;
//    discoverDevices();
//    cout<<"\n"<<endl;
//    if (!checkConnectedDevices()) {sendSimpleMessage(buffer,valread);return -1;}
//    counter = 1;
//    while(true) {
//        if (counter == 8) {counter = 1;}
//        if (sockets[counter].getConnected()) {
//            communicate();
//            counter++;
//            sleep(2);
//        }
//        else {
//            counter++;
//        }
//    }
    webSocket tester;
    while (true) {
        cout << tester.sendMessage(1) << endl;
        sleep(2);
    }
    return 0;
}
