/*
  mainsail.cpp implementation file
  Dennis Evangelista, 2018
 */

#include "mbed.h"
#include "rtos.h"
#include "mainsail.h"




/**
   This function sets the mainsail position in degrees. If a position outside of the allowable range is passed, it clips it to be within the allowable range. 
   @param deg The angle in degrees
   @returns nothing
   In future hulls this will be a process on a microcontroller embedded in the sail actuator; and may be the recipient of commands via NMEA 2000 bus and/or a ROS twist type message. 
*/
void Mainsail::write(float deg){

  // clip to be in acceptable range
  if (deg < -MAINSAIL_RANGE_DEG)
    { deg = -MAINSAIL_RANGE_DEG; }
  else if (deg > MAINSAIL_RANGE_DEG)
    { deg = MAINSAIL_RANGE_DEG; }
  Mainsail::_deg = deg;

  // compute correct servo timing
  Mainsail::_us = MAINSAIL_ZERO_US + (int)(MAINSAIL_RANGE_US + Mainsail::_deg/MAINSAIL_RANGE_DEG);
     
  // set the servo position
  debug("Mainsail %d us",Mainsail::_us); 
  Mainsail::_pwm.pulsewidth_us(Mainsail::_us);
} // write()




/**
   This function gets the mainsail position in degrees. 
   @returns position in degrees as a float. 
 */
float Mainsail::read(void){
  return Mainsail::_deg;
}




/** 
    Constructor for a Mainsail object
    @param pin The PWM pin the mainsail servo PWM line is connected to
    @returns a Mainsail object
*/
Mainsail::Mainsail(PinName pin):_pwm(pin){
  debug("Mainsail constructor called.\n");
  Mainsail::_deg = 0.0;
  Mainsail::_us = MAINSAIL_ZERO_US; 
  Mainsail::_pwm.period_ms(MAINSAIL_PERIOD_MS); // 20 ms, 50 Hz
  Mainsail::_pwm.pulsewidth_us(Mainsail::_us); // beam reach
} // Mainsail constructor





/**
 * Destructor for a Mainsail object
 */
Mainsail::~Mainsail(void){
  debug("Mainsail destructor called.\n");
} // ~Mainsail destructor
