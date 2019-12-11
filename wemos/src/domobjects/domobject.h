#include <WString.h>
#include "ArduinoJson-v6.13.0.h"
#include "../components.h"

#ifndef DOMOBJECT
#define DOMOBJECT

class DomObject {
    public:
        virtual int getId();
        virtual void getSensors(JsonObject&);
        virtual void writeActuators(JsonObject&);
};

class Bed: public DomObject {
    public:
        int getId() override;
        void getSensors(JsonObject&) override;
        void writeActuators(JsonObject&) override;
};

class Chair: public DomObject {
    public:
        int getId() override;
        void getSensors(JsonObject&) override;
        void writeActuators(JsonObject&) override;
};

class TableLamp: public DomObject {
     public:
        int getId() override;
        void getSensors(JsonObject&) override;
        void writeActuators(JsonObject&) override;
};

class Pillar: public DomObject {
    public:
        int getId() override;
        void getSensors(JsonObject&) override;
        void writeActuators(JsonObject&) override;
};

class Door: public DomObject {
    public:
        int getId() override;
        void getSensors(JsonObject&) override;
        void writeActuators(JsonObject&) override;
};

class Wall: public DomObject {
    public:
        int getId() override;
        void getSensors(JsonObject&) override;
        void writeActuators(JsonObject&) override;
};
#endif
