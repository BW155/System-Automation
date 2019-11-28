#include <Wire.h>
#include <Arduino.h>

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
bool getButton();

#endif
