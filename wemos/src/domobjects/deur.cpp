#include "domobject.h"

String Chair::getName() {
    return "deur";
}

void Chair::getSensors(JsonArray& arr) {
    JsonObject buttons = arr.createNestedObject();
    buttons["name"] = "buttons";
    buttons["button1"] = getButton(1);
    buttons["button2"] = getButton(2);
}

void Chair::writeActuators() {
    
}
