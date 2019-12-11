#include "domobject.h"

int Chair::getId() {
    return 2;
}

void Chair::getSensors(JsonObject& obj) {
    obj["ForceSensor"] = getForceSensor();
    obj["Button"] = getButton();
    resetButton();
}

void Chair::writeActuators(JsonObject& actuators) {
    int l = actuators["led"];
    int v = actuators["vib"];
    setChairActuators(l, v);
}
