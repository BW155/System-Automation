#include <WString.h>

#ifndef DOMOBJECT
#define DOMOBJECT

class DomObject {
    public:
        virtual String getName();
        virtual String getSensors();
        virtual void writeActuators();
    protected:
        String name;
};

class Bed: public DomObject {
    public:
        String getName() override;
        String getSensors() override;
        void writeActuators() override;
};

class Chair: public DomObject {
    public:
        String getName() override;
        String getSensors() override;
        void writeActuators() override;
};

#endif
