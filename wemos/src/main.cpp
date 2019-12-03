using namespace std;

#include <arduino.h>
#include "domobjects/domobject.h"
#include "wifi.h"

/// Get the right configuration (Decided at compile-time)
#ifdef BED
Bed object;
#endif

#ifdef CHAIR
Chair object;
#endif

#ifdef DOOR
Deur object;
#endif

void setup() {
    Serial.begin(9600);
    wifiSetup();
    Serial.println("Hi, my name is " + object.getName());
}

void loop() {
    delay(100);
    handleWifi(&object);
}

