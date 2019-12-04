#include "components.h"
#include <Wire.h>
#include <Servo.h>

/////////////////////
/// Setup         ///
/////////////////////

Servo servo;

void initServo() {
    servo.attach(14);
}

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

void setServo(int angle) {
    servo.write(angle);
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

bool getButton(int n) {
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x00));
    Wire.endTransmission();
    Wire.requestFrom(0x38, 1);
    unsigned int inputs = Wire.read();
    return inputs & 1 << n;
}

void resetButton() {
    static_button_state = false;
}

////////////////////////////////////////

// Loop that the main loop goes through to check components that require more realtime checking, like buttons.
void componentCheckLoop() {
    
}

