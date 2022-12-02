#include "Arduino.h"
#include "IR.h"

// Constructor
IR::IR(int pin)
{
    pinMode(pin, INPUT);
    _pin = pin;
}

void IR::init()
{
    // initialize variables for digital conversion
    max = 300;
    upper_cutoff = 0.8 * max;
    lower_cutoff = 0.5 * max;

    // initialize digital value
    digitalValue = true;
}

float IR::read()
{
    return analogRead(_pin);
}

bool IR::digitalRead() {
    float analogValue = read();
    digitalValue = analogValue > upper_cutoff ? true : analogValue < lower_cutoff ? false : digitalValue;
    return digitalValue;
}