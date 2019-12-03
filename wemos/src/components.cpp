#include "components.h"

/////////////////////
/// Set Actuators ///
/////////////////////

void setLed(bool state) {
    int led = state << 4;
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x01));
    Wire.write(led);
    Wire.endTransmission();
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
    if (inputs & 0x01) {
        static_button_state = true;
    }
    if (static_button_state) {
        return true;
    }
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
