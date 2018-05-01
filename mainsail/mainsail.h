/*
  USNA Sailbot Hull 13 mod 2 Rudder
  D Evangelista, 2018
 */

#ifndef MAINSAIL_H
#define MAINSAIL_H

#include "mbed.h"
#include "rtos.h"

#define MAINSAIL_VERSION "13.2.1"

/// The mainsail for Hull 13 mod 2 is a Hitec D845WP servo
#define MAINSAIL_PERIOD_MS 20 // 50Hz, 20 ms
#define MAINSAIL_ZERO_US 1500 // at 0 position
#define MAINSAIL_RANGE_US 600 // on either side of 0 position
#define MAINSAIL_RANGE_DEG 45 // Paul Miller ordered 90 deg range ones! 

#define MAINSAIL_CLOSEHAUL 45 // this is gonna suck
#define MAINSAIL_CLOSEREACH 45.0 // this is also gonna suck
#define MAINSAIL_BEAMREACH 10.0
#define MAINSAIL_RUN 0.0


/**
   This defines a class and API for talking to the mainsail servo. Example:
   @code
   #include "mbed.h"
   #include "rtos.h"
   #include "mainsail.h"
   
   Mainsail mainsail(PC_6));

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
  mbed::PwmOut _pwm; // PWM pin connected to mainsail servo, PC_6 in rev D
  float _deg; // mainsail angle in degrees (positive is ??)
  int _us; // servo pulse width in us

 public:  
  Mainsail(PinName pin); // constructor
  ~Mainsail(void); // destructor
  void write(float deg); // sets the mainsail angle in degrees
  float read(void); // gets the mainsail angle in degrees

  // TODO Mainsail.beamreach(), Mainsail.closehaulport(), Mainsail.closehaulstbd(), Mainsail.run(), etc.
  void closehaul_stbd(void);
  void closereach_stbd(void);
  void beamreach_stbd(void);
  void run(void);
  void closehaul_port(void);
  void closereach_port(void);
  void beamreach_port(void);
  
  

}; // class Mainsail

#endif
