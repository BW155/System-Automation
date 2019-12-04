#include "domobject.h"

String Door::getName() {
    return "Door";
}

void Door::getSensors(JsonArray& arr) {
    JsonObject buttons = arr.createNestedObject();
    buttons["name"] = "Buttons";
    buttons["button 1"] = getButton(0);
    buttons["button 2"] = getButton(1);
}

void Door::writeActuators(JsonArray& actuators) {
    JsonObject servo = actuators[0];
    int angle = servo["value"];
    setServo(angle);
}
