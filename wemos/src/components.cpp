#include "components.h"

/////////////////////
/// Set Actuators ///
/////////////////////

void setLed(bool state) {

}

///////////////////
/// Get Sensors ///
///////////////////
unsigned int getForceSensor() {
    Wire.requestFrom(0x36, 4);
    unsigned int anin0 = Wire.read() & 0x03;
    anin0 = anin0 << 8;
    anin0 = anin0 | Wire.read();
    return anin0;
}
