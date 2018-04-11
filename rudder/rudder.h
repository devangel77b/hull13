/*
  USNA Sailbot Hull 13 mod 2 Rudder
  D Evangelista, 2018
 */

#ifndef RUDDER_H
#define RUDDER_H

#include "mbed.h"
#include "rtos.h"

#define RUDDER_VERSION "13.2.0"
#define RUDDER_PERIOD_MS 20 // 50Hz, 20 ms
#define RUDDER_ZERO_US 1500 // at 0 position
#define RUDDER_RANGE_US 600 // on either side of 0 position
#define RUDDER_RANGE_DEG 90 // 




class Rudder{
 private:
  mbed::PwmOut _pwm; // PWM pin connected to rudder servo
  float _deg; // rudder angle in degrees (positive is right?)
  int _us; // servo pulse width in us

 public:  
  Rudder(PinName pin); // constructor
  ~Rudder(void); // destructor
  void write(float deg); // sets the rudder angle in degrees
  float read(void); // gets the rudder angle in degrees

  // later: Rudder.amidships(), Rudder.left(), Rudder.right(), etc. 
  

}; // class Rudder

#endif
