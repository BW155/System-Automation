#include "domobject.h"
#include "components.h"

String Pillar::getName() {
    return "Pillar";
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
    int PillarLed = PillarLed["value"];
    setLedBuzzer(PillarLed);
    
    JsonObject Buzzer = actuators[1];
    int Buzzer = Buzzer["value"];
    setLedBuzzer(Buzzer);
}