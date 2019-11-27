#include "domobject.h"

String Chair::getName() {
    return "Chair";
}

void Chair::getSensors(JsonArray& arr) {
    JsonObject forceSensor = arr.createNestedObject();
    forceSensor["name"] = "ForceSensor";
    forceSensor["value"] = getForceSensor();
}

void Chair::writeActuators() {
    
}
