#include "domobject.h"
#include "components.h"

int Bed::getId() {
    return 1;
}

void Bed::getSensors(JsonObject& obj) {
    obj["ForceSensor"] = getForceSensor();
    obj["PushButton"] = getButton();
    resetButton();
}

void Bed::writeActuators(JsonObject& actuators) {
    int l = actuators["led"];
    setBedActuators(l);
}
