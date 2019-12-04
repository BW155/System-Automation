#include "domobject.h"
#include "components.h"

int Bed::getId() {
    return 1;
}

void Bed::getSensors(JsonArray& arr) {
    JsonObject forceSensor = arr.createNestedObject();
    forceSensor["name"] = "ForceSensor";
    forceSensor["value"] = getForceSensor();

    JsonObject button = arr.createNestedObject();
    button["name"] = "PushButton";
    button["value"] = getButton(0);
    resetButton();
}

void Bed::writeActuators(JsonArray& actuators) {
    JsonObject led = actuators[0];
    int l = led["value"];
    setBedActuators(l);
}
