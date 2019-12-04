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


void setFridgeFan(){
  //Set PCA9554 outputs (IO44-IO7)
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x01));            
  Wire.write(byte(1<<4));            
  Wire.endTransmission(); 
}

double thermistor(int RawADC) {  //Function to perform the fancy math of the Steinhart-Hart equation

 double temperature;
 temperature = log(((10240000/RawADC) - 10000));
 temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature ))* temperature );
 temperature = temperature - 273.15;              // Convert Kelvin to Celsius
 //temperature = (temperature * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit - comment out this line if you need Celsius
 return temperature;
}

///////////////////
/// Get Sensors ///
///////////////////

double getFridgeTempSensor(int choice){
  Wire.requestFrom(0x36, 4);   
  unsigned int anin0 = Wire.read()&0x03;  
  anin0=anin0<<8;
  anin0 = anin0|Wire.read();  
  unsigned int anin1 = Wire.read()&0x03;  
  anin1=anin1<<8;
  anin1 = anin1|Wire.read(); 

  Serial.print("Fridge inside: ");
    Serial.print(thermistor(anin0));
    Serial.print("Fridge outside: ");
    Serial.println(thermistor(anin1));
    Serial.println(" ");
  
  //Temp sensor inside 
  if(choice = 0){
      double value = thermistor(anin0);
      return value;
  }
  //Temp sensor outside
  if(choice = 1){
      double value = thermistor(anin1);
      return value;
  }
  return -10;
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

void resetButton() {
    static_button_state = false;
}

////////////////////////////////////////

// Loop that the main loop goes through to check components that require more realtime checking, like buttons.
void componentCheckLoop() {
    getButton();
}
