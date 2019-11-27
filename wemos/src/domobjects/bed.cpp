#include "domobject.h"

String Bed::getName() {
    return "Bed";
}

void Bed::getSensors(JsonArray& arr) {
    JsonObject forceSensor = arr.createNestedObject();
    forceSensor["name"] = "ForceSensor";
    forceSensor["value"] = getForceSensor();
}

void Bed::writeActuators() {
    
}
