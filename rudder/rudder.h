#ifndef RUDDER_H
#define RUDDER_H

#include "mbed.h"
#include "rtos.h"

#define RUDDER_UPDATE_PERIOD_MS 22 // 22 ms
#define RUDDER_PWM p21 // set this correctly
#define RUDDER_PERIOD_MS 20 // 50Hz, 20 ms
#define RUDDER_ZERO_US 1500 // at 0 position
#define RUDDER_RANGE_US 600 // on either side of 0 position
#define RUDDER_RANGE_DEG 90 // 

const int RUDDER_MIN_US = RUDDER_ZERO_US-RUDDER_RANGE_US;
const int RUDDER_MAX_US = RUDDER_ZERO_US+RUDDER_RANGE_US; 

class Rudder{
 public:
  float deg; 
  
  Rudder(PinName pin);
  ~Rudder(void);

  // later: Rudder.amidships(), Rudder.left(), Rudder.right(), etc. 
  
 private:
  Thread _rudderThread;
  mbed::PwmOut _pwm;
  void _rudder_process(void); 
};

#endif
