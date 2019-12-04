#include "components.h"
#include <Wire.h>
#include <Servo.h>

/////////////////////
/// Setup         ///
/////////////////////

Servo servo;

void initI2C() {
    Wire.begin();

    //Config PCA9554
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x03));    //DDR      
    Wire.write(byte(0x0F));    //d7-4 output, d3-0 input     
    Wire.endTransmission();

     //Config MAX11647
    Wire.beginTransmission(0x36);
    Wire.write(byte(0xA2));          
    Wire.write(byte(0x03));  
    Wire.endTransmission();
}

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

bool getInput(int n){
    Wire.beginTransmission(0x38); 
    Wire.write(byte(0x00));      
    Wire.endTransmission();
    Wire.requestFrom(0x38, 1);   
    return Wire.read() & (1<<n);
}

double getForceSensor() {
    return 0.1;
}

bool getButton(int n) {
    if(n == 1){
        return getInput(0);
    }else if(n == 2){
        return getInput(1);
    }else{
        return false;
    }
}
