#include "domobject.h"
#include "ArduinoJson-v6.13.0.h"
#include "components.h"

String DomObject::getName() {
    return "NONE";
}

String DomObject::getSensors() {
    return "{\"sensors\": \"test\"}";
}

void DomObject::writeActuators() {}


/// Start Bed overrides
String Bed::getName() {
    return "Bed";
}

String Bed::getSensors() {
    char output[64];
    const int capacity = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<capacity> doc;

    doc["ForceSensor"] = getForceSensor();

    serializeJson(doc, output);
    return output;
}

void Bed::writeActuators() {
    
}


/// Start Chair overrides
String Chair::getName() {
    return "Chair";
}

String Chair::getSensors() {
    char output[64];
    const int capacity = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<capacity> doc;

    doc["ForceSensor"] = getForceSensor();

    serializeJson(doc, output);
    return output;
}

void Chair::writeActuators() {
    
}
