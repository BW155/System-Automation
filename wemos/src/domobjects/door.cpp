#include "domobject.h"

int Door::getId() {
    return 7;
}

void Door::getSensors(JsonArray& arr) {
    JsonObject buttons = arr.createNestedObject();
    buttons["name"] = "Buttons";
    buttons["button 1"] = getDoorButton1();
    buttons["button 2"] = getDoorButton2();
    resetButton();
}

void Door::writeActuators(JsonArray& actuators) {
    JsonObject servo = actuators[0];
    int value = servo["value"];
    switch (value)
    {
    case -1:
        setServo(170);
        break;

    case 0:
        setServo(80);
        break;
    
    case 1:
        setServo(0);
        break;

    default:
        setServo(80);
        break;
    }
    ;
    
}
