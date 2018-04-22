#include "mbed.h"
#include "rtos.h"
#include "compass.h"

void Compass::_update_process(void){
  while(1){
    // if there's serial data read and parse it to update heading
    // non blocking wait otherwise
    Thread::wait(COMPASS_UPDATE_PERIOD_MS);
  } // while(1)
} // Imu::_update_process()

Compass::Compass(PinName tx, PinName rx):_serial(tx,rx){
  debug("Compass constructor called\n");
  // set _serial baudrate and serial port parameters
  // initialize compass readings
  // flush buffer
  // start _update_process by attaching it to _thread
} // Compass::Compass constructor

Compass::~Compass(){
  debug("Compass destructor called\n");
}
