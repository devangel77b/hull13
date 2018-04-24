/*
  rudder.cpp implementation file
  Dennis Evangelista, 2018
 */

#include "mbed.h"
#include "rtos.h"
#include "rudder.h"




/**
   This function sets the rudder position in degrees. If a position outside 
   of the allowable range is passed, it clips it to be within the allowable 
   range. 
     
   @param deg The angle in degrees
   @returns nothing
   
   In future hulls, this may be a process running inside a microcontroller 
   embedded in the rudder actuator, acting on messages via NMEA 2000 or from 
   ROS twist type commands from a higher level processor. 
*/
void Rudder::write(float deg){

  // clip to be in acceptable range
  if (deg < -RUDDER_RANGE_DEG)
    { deg = -RUDDER_RANGE_DEG; }
  else if (deg > RUDDER_RANGE_DEG)
    { deg = RUDDER_RANGE_DEG; }
  Rudder::_deg = deg;

  // compute correct servo timing
  Rudder::_us = RUDDER_ZERO_US + (int)(RUDDER_RANGE_US * Rudder::_deg/RUDDER_RANGE_DEG);
     
  // set the servo position
  debug("Rudder %d us",Rudder::_us); 
  Rudder::_pwm.pulsewidth_us(Rudder::_us);
} // write()




/**
   This function gets the rudder position in degrees. 
   @returns position in degrees as a float. 
 */
float Rudder::read(void){
  return Rudder::_deg;
}




/** 
    Constructor for a Rudder object
    @param pin The PWM pin the rudder servo PWM line is connected to
    @returns a Rudder object
    PC_8 is the PWM pin for the rudder in Hull 13 mod 2 D board. 
*/
Rudder::Rudder(PinName pin):_pwm(pin){
  debug("Rudder constructor called.\n");
  Rudder::_deg = 0.0;
  Rudder::_us = RUDDER_ZERO_US; 
  Rudder::_pwm.period_ms(RUDDER_PERIOD_MS); // 20 ms, 50 Hz
  Rudder::_pwm.pulsewidth_us(Rudder::_us); // rudder amidships
} // Rudder constructor





/**
   Destructor for a Rudder object
 */
Rudder::~Rudder(void){
  debug("Rudder destructor called.\n");
} // ~Rudder destructor
