// Lars Hartog
#include "includes.h"

using json = nlohmann::json;
using namespace std;

#define PORT 8080

// Setup for webSocket with python server
webSocket pyt;

// Timeclass used by domObjects
TimeClass obj1 (1,0,0,0);

// Vector containing the domObjects
vector<domObject*> objects;

// Check if all devices are connected
bool checkConnectedDevices() {
    return objects.size() == 7;
}

// Function to add devices to Objects vector
void discoverDevices() {

    // Standard first part of IP
    const char *IPGROUP = "192.168.2.";

    // Int to check which device is beijng used
    int Device;

    // Loop through all IP adresses
    for (int x = 180; x < 200; x+=1) {

        // Standard variables for Socket communication
        int valread;
        char buffer[1024] = {0};
        const char *hello = "hello";

        // making a full IP adress from IPGROUP and current x
        stringstream ss;
        ss << IPGROUP << x;
        const string tmp = ss.str();
        const char *IP = tmp.c_str();

        // Make the socket
        Socket test(100,"test",IP);

        // Check if the socket is connected
        if (test.getConnected()) {

            // Send and receive to and from socket
            send(test.sock, hello, strlen(hello), 0);
            valread = read(test.sock, buffer, 1024);

            // Change valread to a number
            stringstream temp(buffer);
            temp >> Device;

            // Decide which device is attached to the socket,
            // Then make a new instance of this object and
            // put it in objects vector
            switch (Device) {
                case 1 : {
                    objects.push_back(new Bed(IP,&pyt,&obj1));
                    cout << "Bed was made\n" << endl;
                    break;
                }
                case 2 : {
                    objects.push_back(new Chair(IP, &pyt, &obj1));
                    cout << "Chair was made\n" << endl;
                    break;
                }
                case 3 : {
                    objects.push_back(new Lamp(IP,&pyt,&obj1));
                    cout << "Lamp was made\n" << endl;
                    break;
                }
                case 4 : {
                    objects.push_back(new Pillar(IP,&pyt));
                    cout << "Pillar was made\n" << endl;
                    break;
                }
                case 5 : {
                    objects.push_back(new Wall(IP,&pyt));
                    cout << "Wall was made\n" << endl;
                    break;
                }
                case 6 : {
                    objects.push_back(new Fridge(IP,&pyt,&obj1));
                    cout << "Fridge was made\n" << endl;
                    break;
                }
                case 7 : {
                    objects.push_back(new Door(IP,&pyt,&obj1));
                    cout << "Door was made\n" << endl;
                    break;
                }
                default:
                    cout << "Not found, help\n" << endl;
            }
        }

        // When all devices are connected, stop the loop
        if (objects.size() == 7) {
            x = 201;
        }
    }
    cout<<"Device search done\n"<<endl;
}

// initialize connection to sockets, empty log, connect some objects to each other
bool init() {

    // Discover devices
    discoverDevices();

    // Clear the log
    std::ofstream ofs;
    ofs.open("log.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    // Decide whether to test or to actually run
    int in;
    cout<<"type 1 for testing or 2 for the real deal: "<<endl;
    cin >> in;

    if (in == 1) {
        return true;
    }
    else {
        // check if all devices are connected
        if (checkConnectedDevices()) {

            // Link Door and Pillar
            for (int x = 0; x < objects.size(); x++) {
                for (int y = 0; y < objects.size(); y++) {
                    if (objects[x]->id == 7 && objects[y]->id == 4) {
                        Door* door = dynamic_cast<Door*>(objects[x]);
                        Pillar* pillar = dynamic_cast<Pillar*>(objects[y]);
                        door->setPillarPointer(pillar);
                    }
                }
            }
            return true;
        }
        return false;
    }
}


int main(int argc, char const *argv[])
{
    // initialize
    bool run = init();
    cout<<"init done"<<endl;

    // keep updating devices
    while (run) {
        for (int x = 0; x < objects.size(); x++) {
            objects[x]->update();
//            cout<<objects[x]->id<<endl;
        }
    }
    return 0;
}