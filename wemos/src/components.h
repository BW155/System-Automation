#include <Wire.h>
#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

#ifndef COMPONENTS
#define COMPONENTS
#define BED_BUTTON 0x01
#define PILLAR_BUTTON 0x01
#define DOOR_BUTTON_1 0x01
#define DOOR_BUTTON_2 0x02


#ifdef WALL
#define NUM_LEDS 3 
#else
#define NUM_LEDS 1
#endif

double calculateThermistor(int RawADC);
void brightness();
/////////////////////
/// Set Actuators ///
/////////////////////
void setFridgeActuators(bool);
void setBedActuators(bool);
void setChairActuators(bool, bool);
void writeActuators(int);
void setPeltier(bool state);
void setTableActuators(bool);
void setWallActuators(bool, int);
void setDoorActuators(bool, bool);
void setLamp(bool);
void setPillarActuators(bool, bool);
void setLed(bool);
void setServo(int);
void setWallLamp(int);

///////////////////
/// Get Sensors ///
///////////////////
double getFridgeTempSensor(int choice);
void getFridgeFan();
int getFridgeClicker();
unsigned int getForceSensor();
bool getButton();
unsigned int getMotionSensor();
bool getDoorButton1();
bool getDoorButton2();
int getWallSensors(int choice);

int getGassensor();
bool getButtonPillar();

/////////////////////
/// Miscellaneous ///
/////////////////////

// States if the button was pressed for the sensor data receiver.
static bool static_button_state;
static bool pillar_button_state;
static bool static_button_1_state;
static bool static_button_2_state;

void initServo();
void initLed();
void componentCheckLoop();
void resetButton();
void resetPillarButton();

#endif

