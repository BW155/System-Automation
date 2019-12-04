#include "domobject.h"
#include "components.h"

String Pillar::getName() {
    return "Pillar";
}

void Pillar::getSensors(JsonArray& arr) {
    JsonObject forceSensor = arr.createNestedObject();
    forceSensor["name"] = "Gassensor";
    forceSensor["value"] = getGassensor();

    JsonObject button = arr.createNestedObject();
    button["name"] = "ButtonPillar";
    button["value"] = getButtonPillar();
    resetButton();
}

void Pillar::writeActuators(JsonArray& actuators) {
    JsonObject PillarLed = actuators[0];
    int PillarLed = PillarLed["value"];
    
    JsonObject Buzzer = actuators[1];
    int Buzzer = Buzzer["value"];

    int outputs = PillarLed + Buzzer;
    setLedBuzzer(outputs);
}