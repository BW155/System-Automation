#include <WString.h>
#include <ESP8266WiFi.h>
#include "domobjects/domobject.h"

#ifndef WIFI
#define WIFI

void wifiSetup();
void handleWifi(DomObject*);
String constructResult(const char*);
String constructResult(JsonObject);


#endif
