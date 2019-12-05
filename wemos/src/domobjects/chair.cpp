#include "domobject.h"

String Chair::getName() {
    return "Chair";
}

void Chair::getSensors(JsonArray& arr) {
    JsonObject forceSensor = arr.createNestedObject();
    forceSensor["name"] = "ForceSensor";
    forceSensor["value"] = getForceSensor();

    JsonObject button = arr.createNestedObject();
    forceSensor["name"] = "Button";
    forceSensor["value"] = getButton();
    resetButton();
}

void Chair::writeActuators(JsonArray& actuators) {
    JsonObject led = actuators[0];
    int l = led["value"];

    JsonObject vib = actuators[1];
    int v = vib["value"];

    setChairActuators(l, v);
}
