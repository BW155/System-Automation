#include "domobject.h"

int Door::getId() {
    return 7;
}

void Door::getSensors(JsonObject& obj) {
    obj["button 1"] = getDoorButton1();
    obj["button 2"] = getDoorButton2();
    resetButton();
}

void Door::writeActuators(JsonObject& actuators) {
    int value = actuators["servo"];
    switch (value) {
        case -1:
            setServo(170);
            break;
        case 0:
            setServo(80);
            break;
        case 1:
            setServo(0);
            break;
        default:
            setServo(80);
            break;
    }
}
