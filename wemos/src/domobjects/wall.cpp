#include "domobject.h"

int Wall::getId() {
    return 5;
}

void Wall::getSensors(JsonObject& obj) {
    obj["LDR"] = getWallSensors(0);
    obj["dimmer"] = getWallSensors(1);
}

void Wall::writeActuators(JsonObject& actuators) {
    int window = actuators["window"];
    int led = actuators["led"];
    setWallActuators(window, led);
}
