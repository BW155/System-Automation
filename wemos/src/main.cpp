#include <Wire.h>
#include <Arduino.h>
#include <string>
#include "domobjects/domobject.h"
#include "components.h"
#include "wifiHandler.h"
#include "Ticker.h"

using namespace std;

// Get the right configuration (Decided at compile-time)
#ifdef BED
Bed object;
#endif

#ifdef CHAIR
Chair object;
#endif

#ifdef TABLELAMP
TableLamp object;
#endif

#ifdef PILLAR
Pillar object;
#endif

#ifdef DOOR
Door object;
#endif

#ifdef WALL
Wall object;
#endif    

#ifdef FRIDGE
Fridge object;
#endif
Ticker tick(brightness, 0.05);

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
    initLed();
    wifiSetup();

    Serial.println("Hi, my id is " + String(object.getId()));
    
    tick.start();
}

void loop() {
    handleWifi(&object);
    delay(20);
    componentCheckLoop();
    tick.update();  
}
