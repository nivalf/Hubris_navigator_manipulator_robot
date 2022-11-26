// include guard
#ifndef IR_H
#define IR_H

// include Arduino library
#include "Arduino.h"

class IR
{
  public:
    IR(int pin);
    void init();
    float read();
    bool digitalRead();
  private:
    // pin number
    int _pin;

    // variables for digital conversion
    int max;
    int upper_cutoff;
    int lower_cutoff;

    // digital value
    bool digitalValue;
};

#endif
