#include <WString.h>
#include "ArduinoJson-v6.13.0.h"
#include "../components.h"

#ifndef DOMOBJECT
#define DOMOBJECT

class DomObject {
    public:
        virtual int getId() = 0;
        virtual void getSensors(JsonObject&) = 0;
        virtual void writeActuators(JsonObject&) = 0;
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

class Fridge: public DomObject{
    public:
        int getId() override;
        void getSensors(JsonObject&) override;
        void writeActuators(JsonObject&) override;
};

#endif
