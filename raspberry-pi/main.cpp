// Lars Hartog
#include "includes.h"

using json = nlohmann::json;
using namespace std;

#define PORT 8080


webSocket pyt;
TimeClass obj1 (1,0,0,0);

vector<domObject*> objects;
Door tempT("x", &pyt, &obj1);
Fridge fridge("x", &pyt, &obj1);
Pillar p("x", &pyt);
Wall wall("x", &pyt);
Bed bed("x", &pyt, &obj1);

bool checkConnectedDevices() {
    return objects.size() == 7;
}

void discoverDevices() {

    const char *IPGROUP = "192.168.2.";
//    const char *IP;
    int Device;

    for (int x = 197; x < 198; x+=1) {
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
                    Bed b(IP, &pyt, &obj1);
//                    objects.push_back(b);
                    bed = b;
                    cout << "Bed was made\n" << endl;
                    break;
                }
//                case 2 : {
//                    Chair c(IP, &pyt);
//                    objects.push_back(c);
//                    cout << "Chair was made\n" << endl;
//                    break;
//                }
//                case 3 : {
//                    Lamp t(IP,&pyt);
//                    objects.push_back(t);
//                    tempT = &t;
//                    cout << "Lamp was made\n" << endl;
//                    break;
//                }
                case 4 : {
                    Pillar pillar(IP, &pyt);
                    p = pillar;
                    // objects.push_back(p);

                    cout << "Pillar was made\n" << endl;
                    break;
                }
                case 5 : {
                    Wall w(IP, &pyt);
//                    objects.push_back(w);
                    wall = w;
                    cout << "Wall was made\n" << endl;
                    break;
                }
                case 6 : {
                    Fridge f(IP, &pyt, &obj1);
                    fridge = f;
                    cout << "Fridge was made\n" << endl;
                    break;
                }
                case 7 : {
                    Door d(IP, &pyt, &obj1);
//                    objects.push_back(d);
                    tempT = d;
                    cout << "Door was made\n" << endl;
                    break;
                }
                default:
                    cout << "Not found, help\n" << endl;
            }
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
    else if (in == 2) {
        return checkConnectedDevices();
    }
    else {
        return checkConnectedDevices();
    }
}

int main(int argc, char const *argv[])
{
    bool run = init();
    cout<<"init done"<<endl;
    while (run) {
//        for (int x = 0; x < objects.size(); x++) {
            fridge.update();
//        }
        sleep(1);
//        cout<<"rondje"<<endl;
    }
    return 0;
}