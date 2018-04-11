/*
  USNA Sailbot Hull 13 mod 2 Rudder
  D Evangelista, 2018
 */

#ifndef MAINSAIL_H
#define MAINSAIL_H

#include "mbed.h"
#include "rtos.h"

#define MAINSAIL_VERSION "13.2.0"

/// The mainsail for Hull 13 mod 2 is a Hitec D845WP servo
#define MAINSAIL_PERIOD_MS 20 // 50Hz, 20 ms
#define MAINSAIL_ZERO_US 1500 // at 0 position
#define MAINSAIL_RANGE_US 600 // on either side of 0 position
#define MAINSAIL_RANGE_DEG 90 // 



/**
   This defines a class and API for talking to the mainsail servo. Example:
@code
#include "mbed.h"
#include "rtos.h"
#include "mainsail.h"

Mainsail mainsail(p22);

int main(){
  mainsail.write(0.0);
  Thread::wait(10);
  mainsail.write(30.0);
  Thread::wait(10);
  mainsail.write(0.0);
  Thread::wait(10); 
}
@endcode
 */
class Mainsail{
 private:
  mbed::PwmOut _pwm; // PWM pin connected to mainsail servo
  float _deg; // mainsail angle in degrees (positive is ??)
  int _us; // servo pulse width in us

 public:  
  Mainsail(PinName pin); // constructor
  ~Mainsail(void); // destructor
  void write(float deg); // sets the mainsail angle in degrees
  float read(void); // gets the mainsail angle in degrees

  // TODO Mainsail.beamreach(), Mainsail.closehaulport(), Mainsail.closehaulstbd(), etc. 
  

}; // class Mainsail

#endif
