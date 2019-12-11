#include <Wire.h>
#include <Arduino.h>

#ifndef COMPONENTS
#define COMPONENTS
#define BED_BUTTON 0x01

double thermistor(int RawADC);

/////////////////////
/// Set Actuators ///
/////////////////////
void setFridgeFan(bool state);

void setBedActuators(bool);
void setChairActuators(bool, bool);
void writeActuators(int);

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
