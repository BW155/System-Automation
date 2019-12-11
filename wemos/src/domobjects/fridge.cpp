#include "domobject.h"
#include "components.h"

int Fridge::getId() {
    return 6;
}

void Fridge::getSensors(JsonArray& arr) {
    JsonObject thermometer1 = arr.createNestedObject();
    thermometer1["name"] = "thermometer1";
    thermometer1["value"] = getFridgeTempSensor(0); //Inside temp sensor

    JsonObject thermometer2 = arr.createNestedObject();
    thermometer2["name"] = "thermometer2";
    thermometer2["value"] = getFridgeTempSensor(1); //Outside temp sensor

    JsonObject openClose = arr.createNestedObject();
    openClose["name"] = "openClose";
    openClose["value"] = getFridgeClicker();
}    

void Fridge::writeActuators(JsonArray& actuators) {
    JsonObject cooling = actuators[0];
    int c = cooling["value"];
    setFridgeActuators(c);
}