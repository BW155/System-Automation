#include "components.h"

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

void writeActuators(int output) {
    Serial.print("Output Actuators: ");
    Serial.println(output);

    Wire.beginTransmission(0x38);
    Wire.write(byte(0x01));
    Wire.write(byte(output));
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
    if (inputs & BED_BUTTON) {
        static_button_state = true;
    }
    if (static_button_state) {
        return true;
    }
    return inputs & BED_BUTTON;
}

void resetButton() {
    static_button_state = false;
}

////////////////////////////////////////

// Loop that the main loop goes through to check components that require more realtime checking, like buttons.
void componentCheckLoop() {
    getButton();
}
