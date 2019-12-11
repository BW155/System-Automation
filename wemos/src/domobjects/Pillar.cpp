#include "domobject.h"
#include "components.h"

int Pillar::getId() {
    return 4;
}

void Pillar::getSensors(JsonObject& obj) {
    obj["Gassensor"] = getGassensor();
    obj["ButtonPillar"] = getButtonPillar();
    resetPillarButton();
}

void Pillar::writeActuators(JsonObject& actuators) {
    int pillarLed = actuators["pillarLed"];
    int buzzer = actuators["buzzer"];
    setPillarActuators(pillarLed, buzzer);
}
