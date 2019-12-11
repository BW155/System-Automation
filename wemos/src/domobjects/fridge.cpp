#include "domobject.h"
#include "components.h"

int Fridge::getId() {
    return 6;
}

void Fridge::getSensors(JsonObject& obj) {
    obj["thermometer1"] = getFridgeTempSensor(0); //Inside temp sensor
    obj["thermometer2"] = getFridgeTempSensor(1); //Outside temp sensor
    obj["openClose"] = getFridgeClicker();
}    

void Fridge::writeActuators(JsonObject& actuators) {
    int cooling = actuators["cooling"];
    setFridgeActuators(cooling);
}
