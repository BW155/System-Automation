#include "domobject.h"

String Chair::getName() {
    return "Chair";
}

void Chair::getSensors(JsonArray& arr) {
    char output[64];
    const int capacity = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<capacity> doc;

    doc["ForceSensor"] = getForceSensor();

    serializeJson(doc, output);
}

void Chair::writeActuators() {
    
}
