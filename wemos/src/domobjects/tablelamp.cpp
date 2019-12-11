#include "domobject.h"
#include "components.h"

int TableLamp::getId() {
    return 3;
}

void TableLamp::getSensors(JsonObject& obj) {
    obj["motionSensor"] = getMotionSensor();
}

void TableLamp::writeActuators(JsonObject& actuators) {
    int lamp = actuators["lamp"];
    setTableActuators(lamp);
}
