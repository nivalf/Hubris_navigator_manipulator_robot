// include guard
#ifndef Battery_H
#define Battery_H

// include Arduino library
#include "Arduino.h"

class BatteryVoltage
{
public:
    BatteryVoltage(int pin);
    float getVoltage();
    void checkVoltage();

private:
    int batteryVoltagePin;
};

#endif
