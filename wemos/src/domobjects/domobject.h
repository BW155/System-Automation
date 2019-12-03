#include <WString.h>
#include "ArduinoJson-v6.13.0.h"
#include "../components.h"

#ifndef DOMOBJECT
#define DOMOBJECT

class DomObject {
    public:
        virtual String getName();
        virtual void getSensors(JsonArray&);
        virtual void writeActuators();
};

class Bed: public DomObject {
    public:
        String getName() override;
        void getSensors(JsonArray&) override;
        void writeActuators() override;
};

class Chair: public DomObject {
    public:
        String getName() override;
        void getSensors(JsonArray&) override;
        void writeActuators() override;
};

class Deur: public DomObject {
    public:
        String getName() override;
        void getSensors(JsonArray&) override;
        void writeActuators() override;
};

#endif
