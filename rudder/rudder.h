/*
  USNA Sailbot Hull 13 mod 2 Rudder
  D Evangelista, 2018
 */

#ifndef RUDDER_H
#define RUDDER_H

#include "mbed.h"
#include "rtos.h"

#define RUDDER_VERSION "13.2.1"

/// The rudder for Hull 13 mod 2 is a Hitec HS5646WP servo
#define RUDDER_PERIOD_MS 20 // 50Hz, 20 ms
#define RUDDER_ZERO_US 1500 // at 0 position
#define RUDDER_RANGE_US 600 // on either side of 0 position
#define RUDDER_RANGE_DEG 45 // Paul Miller ordered 90 degree range

#define RUDDER_SMALL 5.0
#define RUDDER_FULL 15.0


/**
   This defines a class and API for talking to the rudder servo. Example:
@code
#include "mbed.h"
#include "rtos.h"
#include "rudder.h"

Rudder rudder(p21);

int main(){
  rudder.write(0.0);
  Thread::wait(10);
  rudder.write(30.0);
  Thread::wait(10);
  rudder.write(0.0);
  Thread::wait(10); 
}
@endcode
 */
class Rudder{
 private:
  mbed::PwmOut _pwm; // PWM pin connected to rudder servo PC_8 for rev D board
  float _deg; // rudder angle in degrees (positive is right?)
  int _us; // servo pulse width in us

 public:  
  Rudder(PinName pin); // constructor
  ~Rudder(void); // destructor
  void write(float deg); // sets the rudder angle in degrees
  float read(void); // gets the rudder angle in degrees

  // Rudder.amidships(), Rudder.left(), Rudder.right(), etc. 
  void right(void);
  void right_full(void);
  void left(void); 
  void left_full(void);
  void amidships(void); 
  

}; // class Rudder

#endif
