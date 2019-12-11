#include <Wire.h>
#include <Arduino.h>

#ifndef COMPONENTS
#define COMPONENTS
#define BED_BUTTON 0x01

double thermistor(int RawADC);

/////////////////////
/// Set Actuators ///
/////////////////////
void setLed(bool state);
void setFridgeFan(bool state);

///////////////////
/// Get Sensors ///
///////////////////
double getFridgeTempSensor(int choice);
void getFridgeFan();
void getFridgeClicker();
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
