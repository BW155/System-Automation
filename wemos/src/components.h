#include <Wire.h>
#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

#ifndef COMPONENTS
#define COMPONENTS
#define BED_BUTTON 0x01


/////////////////////
/// Set Actuators ///
/////////////////////

void setBedActuators(bool);
void setChairActuators(bool, bool);
void writeActuators(int);
void setTableActuators(bool);
void setLamp(bool);

///////////////////
/// Get Sensors ///
///////////////////

unsigned int getForceSensor();
bool getButton();
unsigned int getMotionSensor();

/////////////////////
/// Miscellaneous ///
/////////////////////

// States if the button was pressed for the sensor data receiver.
static bool static_button_state;

void componentCheckLoop();
void resetButton();

#endif
