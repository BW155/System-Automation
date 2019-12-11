#include "domobject.h"

int Wall::getId() {
    return 2;
}

void Wall::getSensors(JsonObject& obj) {
    obj["LDRSensor"] = getWallSensors(0);
    obj["Pot"] = getWallSensors(1);
}

void Wall::writeActuators(JsonObject& actuators) {
    int window = actuators["window"];
    int led = actuators["led"];
    setWallActuators(window, led);
}
