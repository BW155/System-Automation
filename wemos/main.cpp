#include <Wire.h>
#include <Arduino.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  //Config MAX11647
  //Inside loop for debugging purpose (hot plugging wemos module into i/o board).
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));
  Wire.write(byte(0x03));
  Wire.endTransmission();

  //Read analog 10bit inputs 0&1
  Wire.requestFrom(0x36, 4);
  unsigned int anin0 = Wire.read() & 0x03;
  anin0 = anin0 << 8;
  anin0 = anin0 | Wire.read();
  unsigned int anin1 = Wire.read() & 0x03;
  anin1 = anin1 << 8;
  anin1 = anin1 | Wire.read();
  Serial.print("analog in 0: ");
  Serial.println(anin0);
  Serial.print("analog in 1: ");
  Serial.println(anin1);
  Serial.println("");

  delay(500);
}
