#include "domobject.h"

int Chair::getId() {
    return 2;
}

void Chair::getSensors(JsonObject& obj) {
    obj["forceSensor"] = getForceSensor();
    obj["button"] = getButton();
    resetButton();
}

void Chair::writeActuators(JsonObject& actuators) {
    int l = actuators["led"];
    int v = actuators["vibrator"];
    setChairActuators(l, v);
}
