#ifndef SERIALWRAPPEREXTERN_H
#define SERIALWRAPPEREXTERN_H

#include "SerialWrapper.h"
#include "AiEsp32RotaryEncoder.h"  // Rotary encoder library

// Declare the external instance of SerialInterceptor
extern SerialInterceptor mirroredSerial;
extern AiEsp32RotaryEncoder rotaryEncoder;
extern UMS3 ums3;
// Replace the global Serial object with mirroredSerial


#endif // SERIALWRAPPEREXTERN_H