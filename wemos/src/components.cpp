#include "components.h"
#include <Wire.h>
#include <Servo.h>
Adafruit_NeoPixel led(1, D5, NEO_GRB + NEO_KHZ800);

/////////////////////
/// Setup         ///
/////////////////////

Servo servo;

void initServo() {
    servo.attach(14);
    servo.write(80);
}



double calculateThermistor(int RawADC) {  //Function to perform the fancy math of the Steinhart-Hart equation
    double temperature;
    temperature = log(((10240000/RawADC) - 10000));
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature ))* temperature );
    temperature = temperature - 273.15;              // Convert Kelvin to Celsius
    return temperature;
}


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

void setPillarActuators(bool led, bool buzzer){
    int output = (led << 5) | (buzzer << 4);
    writeActuators(output);
}

void setFridgeActuators(bool fridge){
    int output = (fridge << 4);
    writeActuators(output);
    setPeltier(fridge);
}

void writeActuators(int output) {
    Serial.print("Output Actuators: ");
    Serial.println(output);

    Wire.beginTransmission(0x38);
    Wire.write(byte(0x01));
    Wire.write(byte(output));
    Wire.endTransmission();
}

int getFridgeClicker(){
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x00));
    Wire.endTransmission();
    Wire.requestFrom(0x38, 1);
    unsigned int anin0 = Wire.read() & 0x01;
    Serial.print("Clicker: ");
    Serial.println(anin0);
    return anin0;
}

//Set Peltier Module Fridge
void setPeltier(bool state){
    void setPeltier(bool state);
    pinMode(14, OUTPUT);
    digitalWrite(14, state);
}

void setLamp(bool state) {
    led.begin();
    led.show();
    for(uint8_t i = 0; i < 255; i++) {
        if(state) {
            led.setBrightness(i);
        } else {
            led.setBrightness(255 - i);
        }
        led.setPixelColor(0, 255, 255, 255);
        led.show();
       // delay(5);
    }
}


void setServo(int angle) {
    servo.write(angle);
}

///////////////////
/// Get Sensors ///
///////////////////

double getFridgeTempSensor(int choice){
  Wire.requestFrom(0x36, 4);   
  unsigned int anin0 = Wire.read() & 0x03;  
  anin0 = anin0 << 8;
  anin0 = anin0 | Wire.read();  
  unsigned int anin1 = Wire.read() & 0x03;  
  anin1 = anin1 << 8;
  anin1 = anin1 | Wire.read(); 
  if (choice == 0){
       return calculateThermistor(anin0);
  }
  if( choice == 1){
       return calculateThermistor(anin1);
  }
}

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

bool getButtonPillar() {
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

bool getDoorButton1() {
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x00));
    Wire.endTransmission();
    Wire.requestFrom(0x38, 1);
    unsigned int inputs = Wire.read();
    if (inputs & DOOR_BUTTON_1) {
        static_button_1_state = true;
    }
    if (static_button_1_state) {
        return true;
    }
    return inputs & DOOR_BUTTON_1;
}

bool getDoorButton2() {
    Wire.beginTransmission(0x38);
    Wire.write(byte(0x00));
    Wire.endTransmission();
    Wire.requestFrom(0x38, 1);
    unsigned int inputs = Wire.read();
    if (inputs & DOOR_BUTTON_2) {
        static_button_2_state = true;
    }
    if (static_button_2_state) {
        return true;
    }
    return inputs & DOOR_BUTTON_2;
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
    static_button_1_state = false;
    static_button_2_state = false;
}

void resetPillarButton() {
    pillar_button_state = false;
}

int getGassensor() {
    Wire.requestFrom(0x36, 4);
    unsigned int anin0 = Wire.read() & 0x03;
    anin0 = anin0 << 8;
    anin0 = anin0 | Wire.read();
    return anin0;
}

///////////////////////////////
// Loop that the main loop goes through to check components that require more realtime checking, like buttons.
///////////////////////////////

void componentCheckLoop(){
    getGassensor();
    getButtonPillar();
    getButton();
    getDoorButton1();
    getDoorButton2();
}