#include "components.h"
Adafruit_NeoPixel led(1, D5, NEO_GRB + NEO_KHZ800);
/////////////////////
/// Set Actuators ///
/////////////////////

void setChairActuators(bool led, bool vibrationMotor) {
    int output = (led << 4) | (vibrationMotor << 5);
    writeActuators(output);
}

void setBedActuators(bool led) {
    int output = (led << 4);
    writeActuators(output);
}
void setTableActuators(bool lamp){
    setLamp(lamp);
}

void writeActuators(int output) {
    Serial.print("Output Actuators: ");
    Serial.println(output);
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x01));
    Wire.write(byte(output));
    Wire.endTransmission();
}

void setLamp(bool state){
    led.begin();
    led.show();
    for(uint8_t i=0; i<255; i++){
        if(state){
            led.setBrightness(i);
        } else {
            led.setBrightness(255-i);
        }
        led.setPixelColor(0, 255, 255, 255);
        led.show();
       // delay(5);
    }
}


///////////////////
/// Get Sensors ///
///////////////////

unsigned int getForceSensor() {
    Wire.requestFrom(0x36, 4);
    unsigned int anin0 = Wire.read() & 0x03;
    anin0 = anin0 << 8;
    anin0 = anin0 | Wire.read();
    return anin0;
}

bool getButton() {
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x00));
    Wire.endTransmission();
    Wire.requestFrom(0x38, 1);
    unsigned int inputs = Wire.read();
    if (inputs & BED_BUTTON) {
        static_button_state = true;
    }
    if (static_button_state) {
        return true;
    }
    return inputs & BED_BUTTON;
}
unsigned int getMotionSensor() {
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  

  return inputs & 0x01;
}

void resetButton() {
    static_button_state = false;
}

////////////////////////////////////////

// Loop that the main loop goes through to check components that require more realtime checking, like buttons.
void componentCheckLoop() {
    getButton();
}

