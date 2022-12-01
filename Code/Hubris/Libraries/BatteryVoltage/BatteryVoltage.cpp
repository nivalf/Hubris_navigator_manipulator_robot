#include "BatteryVoltage.h"

BatteryVoltage::BatteryVoltage(int pin): batteryVoltagePin(pin)
{
    pinMode(batteryVoltagePin, INPUT);
}

/*
    The battery is connected to a voltage divider circuit of 2k & 3.3k resistors.
    Vout = Vin * (R2 / (R1 + R2))
    Vout of 3.3k resistor is given to the arduino.
*/
float BatteryVoltage::getVoltage()
{
    int batteryReading = analogRead(batteryVoltagePin);
    float voltage = 5.0 * (batteryReading / 1023.0) * 5300 / 3300;
    return voltage;
}

void BatteryVoltage::checkVoltage()
{
    Serial.print("Battery Voltage: ");
    Serial.print(getVoltage());
    Serial.println(" V");
}