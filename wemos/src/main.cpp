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
    //wifiSetup();
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
}

void loop() {
   // handleWifi(&object);
    delay(20);
    componentCheckLoop();
    setFridgeFan();




  Wire.requestFrom(0x36, 4);   
  unsigned int anin0 = Wire.read()&0x03;  
  anin0=anin0<<8;
  anin0 = anin0|Wire.read();  
  unsigned int anin1 = Wire.read()&0x03;  
  anin1=anin1<<8;
  anin1 = anin1|Wire.read(); 
  Serial.print("analog in 0: ");
  Serial.println(anin0);   
  Serial.print("analog in 1: ");
  Serial.println(anin1);   
  Serial.println("");


  Serial.println(thermistor(anin0));
  Serial.println(thermistor(anin1));
  delay(1000);
}

