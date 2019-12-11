using namespace std;

#include <Wire.h>
#include <Arduino.h>
#include <string>
#include "domobjects/domobject.h"
#include "components.h"
#include "wifiHandler.h"

// Get the right configuration (Decided at compile-time)
#ifdef BED
Bed object;
#endif

#ifdef CHAIR
Chair object;
#endif

void setup() {
    Serial.begin(9600);
    delay(1000);
    wifiSetup();
    Serial.println("Hi, my name is " + object.getName());

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

  //Config PCA9554
  //Inside loop for debugging purpose (hot plugging wemos module into i/o board). 
  //IO0-IO3 as input, IO4-IO7 as output.
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));          
  Wire.write(byte(0x0F));         
  Wire.endTransmission();
  setFridgeFan(1);
}

void loop() {
    handleWifi(&object);
    delay(20);
    componentCheckLoop();
    getFridgeClicker();
    Serial.print("Binnen Koelkast Temperatuur: "); Serial.println(getFridgeTempSensor(0));
    Serial.print("Buiten Koelkast Temperatuur: "); Serial.println(getFridgeTempSensor(1));
    Serial.println(" ");
  delay(1000);
}

