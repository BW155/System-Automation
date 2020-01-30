#include "domobject.h"
#include "components.h"

int Pillar::getId() {
    return 4;
}

void Pillar::getSensors(JsonObject& obj) {
    obj["gasSensor"] = getGassensor();
    obj["button"] = getButtonPillar();
    resetPillarButton();
}

void Pillar::writeActuators(JsonObject& actuators) {
    int pillarLed = actuators["led"];
    int buzzer = actuators["buzzer"];
    setPillarActuators(pillarLed, buzzer);
}
