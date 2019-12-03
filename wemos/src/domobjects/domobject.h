#include <WString.h>
#include "ArduinoJson-v6.13.0.h"
#include "../components.h"

#ifndef DOMOBJECT
#define DOMOBJECT

class DomObject {
    public:
        virtual String getName();
        virtual void getSensors(JsonArray&);
        virtual void writeActuators(JsonArray&);
};

class Bed: public DomObject {
    public:
        String getName() override;
        void getSensors(JsonArray&) override;
        void writeActuators(JsonArray&) override;
};

class Chair: public DomObject {
    public:
        String getName() override;
        void getSensors(JsonArray&) override;
        void writeActuators(JsonArray&) override;
};

#endif
