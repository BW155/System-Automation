#include <Wire.h>
#include <arduino.h>

#define I2C_SDL    D1
#define I2C_SDA    D2

#ifndef COMPONENTS
#define COMPONENTS

/////////////////////
/// Set Actuators ///
/////////////////////
void setLed(bool state);

///////////////////
/// Get Sensors ///
///////////////////
unsigned int getForceSensor();

#endif
