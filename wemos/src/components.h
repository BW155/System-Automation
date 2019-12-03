#include <Wire.h>
#include <Arduino.h>

#ifndef COMPONENTS
#define COMPONENTS
#define BED_BUTTON = 0x01;

/////////////////////
/// Set Actuators ///
/////////////////////
void setLed(bool state);

///////////////////
/// Get Sensors ///
///////////////////
unsigned int getForceSensor();
bool getButton();

/////////////////////
/// Miscellaneous ///
/////////////////////

// States if the button was pressed for the sensor data receiver.
static bool static_button_state;

void componentCheckLoop();
void resetButton();

#endif
