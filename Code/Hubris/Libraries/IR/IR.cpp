#include "Arduino.h"
#include "IR.h"     // DEV: Check this is correct

IR::IR(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

void IR::init()
{
  // nothing to do
}

float IR::read()
{
  return analogRead(_pin);
}