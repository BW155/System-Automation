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

}

void setServo(int angle) {
    servo.write(angle);
}

///////////////////
/// Get Sensors ///
///////////////////

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
