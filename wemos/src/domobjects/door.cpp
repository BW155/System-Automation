#include "domobject.h"

int Door::getId() {
    return 7;
}

void Door::getSensors(JsonObject& obj) {
    obj["button1"] = getDoorButton1();
    obj["button2"] = getDoorButton2();
    resetButton();
}

void Door::writeActuators(JsonObject& actuators) {
    int led1 = actuators["led1"];
    int led2 = actuators["led2"];
    setDoorActuators(led1, led2);
    int servoValue = actuators["servo"];
    switch (servoValue) {
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
