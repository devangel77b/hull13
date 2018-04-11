/*
  rudder.cpp implementation file
  Dennis Evangelista, 2018
 */

#include "mbed.h"
#include "rtos.h"
#include "rudder.h"

void Rudder::_rudder_process(void){
  while(1){

    // compute rudder servo pulsewidth
    int w = RUDDER_ZERO_US + (int)(RUDDER_RANGE_US + Rudder::deg/RUDDER_RANGE_DEG);
    // pin between min and max
    if (w < RUDDER_MIN_US)
      { w = RUDDER_MIN_US; }
    else if (w > RUDDER_MAX_US)
      { w = RUDDER_MAX_US; }
    
    // set rudder position
    debug("Rudder %d us",w); 
    Rudder::_pwm::pulsewidth_us(w);
    
    Thread::wait(RUDDER_UPDATE_PERIOD_MS);
  }  // while(1)
} // _rudder_process





Rudder::Rudder(PinName pin):_pwm(pin){
  debug("Rudder constructor called.\n");
  Rudder::deg = 0.0;
  Rudder::_pwm::period_ms(RUDDER_PERIOD_MS); // 20 ms, 50 Hz
  Rudder::_pwm::pulsewidth_us(RUDDER_ZERO_US); // rudder amidships

  // attach rudder_process to rudderThread and start it
  Rudder::_rudderThread::start(callback(this,&Rudder::_rudder_process));
}

Rudder::~Rudder(void){
  debug("Rudder destructor called.\n");
}
