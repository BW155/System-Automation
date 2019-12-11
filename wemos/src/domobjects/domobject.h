#include <WString.h>
#include "ArduinoJson-v6.13.0.h"
#include "../components.h"

#ifndef DOMOBJECT
#define DOMOBJECT

class DomObject {
    public:
        virtual int getId();
        virtual void getSensors(JsonArray&);
        virtual void writeActuators(JsonArray&);
};

class Bed: public DomObject {
    public:
        int getId() override;
        void getSensors(JsonArray&) override;
        void writeActuators(JsonArray&) override;
};

class Chair: public DomObject {
    public:
        int getId() override;
        void getSensors(JsonArray&) override;
        void writeActuators(JsonArray&) override;
};

<<<<<<< HEAD
class Pillar: public DomObject {
=======
class Door: public DomObject {
>>>>>>> development
    public:
        int getId() override;
        void getSensors(JsonArray&) override;
        void writeActuators(JsonArray&) override;
};

#endif
