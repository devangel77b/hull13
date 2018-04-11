/*
  rudder.cpp implementation file
  Dennis Evangelista, 2018
 */

#include "mbed.h"
#include "rtos.h"
#include "rudder13.h"





void Rudder::write(float deg){

  // clip to be in acceptable range
  if (deg < -RUDDER_RANGE_DEG)
    { deg = -RUDDER_RANGE_DEG; }
  else if (deg > RUDDER_RANGE_DEG)
    { deg = RUDDER_RANGE_DEG; }
  Rudder::_deg = deg;

  // compute correct servo timing
  Rudder::_us = RUDDER_ZERO_US + (int)(RUDDER_RANGE_US + Rudder::_deg/RUDDER_RANGE_DEG);
     
  // set the servo position
  debug("Rudder %d us",Rudder::_us); 
  Rudder::_pwm.pulsewidth_us(Rudder::_us);
} // write()





float Rudder::read(void){
  return Rudder::_deg;
}





Rudder::Rudder(PinName pin):_pwm(pin){
  debug("Rudder constructor called.\n");
  Rudder::_deg = 0.0;
  Rudder::_us = RUDDER_ZERO_US; 
  Rudder::_pwm.period_ms(RUDDER_PERIOD_MS); // 20 ms, 50 Hz
  Rudder::_pwm.pulsewidth_us(Rudder::_us); // rudder amidships
} // Rudder constructor

Rudder::~Rudder(void){
  debug("Rudder destructor called.\n");
} // ~Rudder destructor
