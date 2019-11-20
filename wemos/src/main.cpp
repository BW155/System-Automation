using namespace std;

#include <arduino.h>
#include <domobject.h>

DomObject* object;

void setup() {

    /// Get the right configuration (Decided at compile-time)
    #ifdef BED
    Bed bed;
    object = &bed;
    #endif

    #ifdef CHAIR
    Chair chair;
    object = &chair;
    #endif


    Serial.begin(9600);
    Serial.println(object->getName());
    Serial.println(object->getSensors());
}

void loop() {

}

