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
  private:
    int _pin;
};

#endif
