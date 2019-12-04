#include "domobject.h"

String Door::getName() {
    return "Door";
}

void Door::getSensors(JsonArray& arr) {
    JsonObject forceSensor = arr.createNestedObject();
    forceSensor["name"] = "ForceSensor";
    forceSensor["value"] = getForceSensor();
}

void Door::writeActuators(JsonArray& actuators) {
    
}
