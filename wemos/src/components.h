#include <Wire.h>
#include <Arduino.h>

#ifndef COMPONENTS
#define COMPONENTS
#define BED_BUTTON = 0x01;
#define PILLAR_BUTTON = 0x01;

/////////////////////
/// Set Actuators ///
/////////////////////
void setLed(bool state);
int setLedBuzzer(int outputs);

///////////////////
/// Get Sensors ///
///////////////////
unsigned int getForceSensor();
bool getButton();

void getGassensor();
int getButtonPillar();
void getGassensor();

/////////////////////
/// Miscellaneous ///
/////////////////////

// States if the button was pressed for the sensor data receiver.
static bool static_button_state;
static bool pillar_button_state;

void componentCheckLoop();
void resetButton();


#endif
