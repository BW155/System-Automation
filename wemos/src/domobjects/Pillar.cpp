#include "domobject.h"
#include "components.h"

int Pillar::getId() {
    return 4;
}

void Pillar::getSensors(JsonArray& arr) {
    JsonObject GasSensor = arr.createNestedObject();
    GasSensor["name"] = "Gassensor";
    GasSensor["value"] = getGassensor();

    JsonObject buttonPillar = arr.createNestedObject();
    buttonPillar["name"] = "ButtonPillar";
    buttonPillar["value"] = getButtonPillar();
    resetPillarButton();
}

void Pillar::writeActuators(JsonArray& actuators) {
    JsonObject PillarLed = actuators[0];
    int PL = PillarLed["value"];
        
    JsonObject Buzzer = actuators[1];
    int Buzz = Buzzer["value"];
    setPillarActuators(PL, Buzz);
}
