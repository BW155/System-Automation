#include "domobject.h"

int Wall::getId() {
    return 2;
}

void Wall::getSensors(JsonArray& arr) {
    JsonObject ldr = arr.createNestedObject();
    ldr["name"] = "LDRSensor";
    ldr["value"] = getWallSensors(0);

    JsonObject pot = arr.createNestedObject();
    pot["name"] = "Pot";
    pot["value"] = getWallSensors(1);
}

void Wall::writeActuators(JsonArray& actuators) {
    JsonObject led = actuators[0];
    int l = led["value"];

    JsonObject vib = actuators[1];
    int v = vib["value"];

    setWallActuators(l, v);
}
