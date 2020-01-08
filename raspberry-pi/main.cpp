// Lars Hartog
#include "includes.h"

using json = nlohmann::json;
using namespace std;

#define PORT 8080


webSocket pyt;
TimeClass obj1 (20,0,0,0);

vector<domObject*> objects;

bool checkConnectedDevices() {
    return 1;
}

void discoverDevices() {

    const char *IPGROUP = "192.168.2.";
//    const char *IP;
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
            stringstream temp(buffer);
            temp >> Device;
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
        if (objects.size() == 7) {
            x = 201;
        }
    }
    cout<<"Device search done\n"<<endl;
}

bool init() {
    discoverDevices();
    int in;
    cout<<"type 1 for testing or 2 for the real deal: "<<endl;
    cin >> in;
    if (in == 1) {
        return true;
    }
    else {
        if (checkConnectedDevices()) {
            for (int x = 0; x < objects.size(); x++) {
                for (int y = 0; y < objects.size(); y++) {
                    if (objects[x]->id == 7 && objects[y]->id == 4) {
                        Door* door = dynamic_cast<Door*>(objects[x]);
                        Pillar* pillar = dynamic_cast<Pillar*>(objects[y]);
                        door->setPillarPointer(pillar);
                    }
                }
            }
            return 1;
        }
        return 0;
    }
}

int main(int argc, char const *argv[])
{
    bool run = init();
    cout<<"init done"<<endl;
    while (run) {
        for (int x = 0; x < objects.size(); x++) {
            cout<<objects[x]->id<<endl;
            objects[x]->update();
        }
//        sleep(1);
//        cout<<"rondje"<<endl;
    }
    return 0;
}