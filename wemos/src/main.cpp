using namespace std;

#include <Wire.h>
#include <Arduino.h>
#include <string>
#include "domobjects/domobject.h"
#include "components.h"
#include "wifiHandler.h"

/// Get the right configuration (Decided at compile-time)
#ifdef BED
Bed object;
#endif

#ifdef CHAIR
Chair object;
#endif

#ifdef DOOR
Door object;
#endif

void setup() {
    Serial.begin(9600);
    Wire.begin();

    // Config maxi 16647 (analog part)
    Wire.beginTransmission(0x36);
    Wire.write(byte(0xA2));
    Wire.write(byte(0x03));
    Wire.endTransmission();

    // Config 
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x03));
    Wire.write(byte(0x0F));
    Wire.endTransmission();

    writeActuators(0);
    initServo();

    wifiSetup();
    Serial.println("Hi, my id is " + String(object.getId()));
}

void loop() {
    handleWifi(&object);
    delay(20);
    componentCheckLoop();
}