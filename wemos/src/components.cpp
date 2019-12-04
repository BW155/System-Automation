#include "components.h"

/////////////////////
/// Set Actuators ///
/////////////////////

int setLedBuzzer(int outputs) {
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(outputs << 4));
  Wire.endTransmission();
}

///////////////////
/// Get Sensors ///
///////////////////

int getButtonPillar() {
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x00));
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);
  unsigned int inputs = Wire.read();
  if (inputs & PILLAR_BUTTON){
      pillar_button_state = true;
  }
  if (pillar_button_state){
      return true;
  }
  return inputs & pillar_button_state;
}

void resetButton() {
    static_button_state = false;
}

void getGassensor() {
  Wire.requestFrom(0x36, 4);
  unsigned int anin0 = Wire.read() & 0x03;
  anin0 = anin0 << 8;
  anin0 = anin0 | Wire.read();
}

///////////////////////////////

void componentCheckLoop(){
    getGassensor();
    getButtonPillar();
}
