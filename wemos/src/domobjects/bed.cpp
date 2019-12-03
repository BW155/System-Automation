#include "domobject.h"
#include "components.h"

String Bed::getName() {
    return "Bed";
}

void Bed::getSensors(JsonArray& arr) {
    JsonObject forceSensor = arr.createNestedObject();
    forceSensor["name"] = "ForceSensor";
    forceSensor["value"] = getForceSensor();

    JsonObject button = arr.createNestedObject();
    button["name"] = "PushButton";
    button["value"] = getButton();
    resetButton();
}

void Bed::writeActuators(JsonArray& actuators) {
    JsonObject led = actuators[0];
    int l = led["value"];
    setLed(l);
}
