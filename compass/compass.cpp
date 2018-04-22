/*
  compass.cpp implementation file
  Dennis Evangelista, 2018
 */

#include "mbed.h"
#include "rtos.h"
#include "compass.h"
#include "BNO055.h" // StressedDave BNO055 library
// https://os.mbed.com/users/StressedDave/code/BNO055


/*
  Callback function for the compass. This is private and should not be
  called from the outside world. Thread _thread will have this process running
  which periodically reads the compass and has a thread-safe wait, allowing 
  other stuff to happen. 
 */
void Compass::_update_process(void){
  while(1){
    // take compass reading
    Compass::_bno055.get_angles();
    hdg = _bno055.euler.yaw; // need to check if this is right

    // thread-safe wait to relinquish to other processes
    Thread::wait(COMPASS_UPDATE_PERIOD_MS);
  } // while(1)
} // Compass::_update_process()




/**
   Compass(sda, scl) is the constructor. Use this to declare a compass
   connected to a particular pair of mins, e.g. Compass(PB_9, PB_8). 

   @param(sda) is the I2C SDA pin
   @param(scl) is the I2C SCL pin
   @returns a Compass object

   The pins should be SDA PB_9 and SCL PB_8 in Hull 13 mod 2 rev D. 
 */
Compass::Compass(PinName sda, PinName scl):_bno055(sda, scl){
  debug("Compass constructor called\n");

  // start the bno055, need to check if this is right
  Compass::_bno055.reset();
  Thread::wait(675);
  Compass::_bno055.check();
  Compass::_bno055.setmode(OPERATION_MODE_COMPASS);
  Compass::_bno055.set_angle_units(DEGREES);
  
  // start _update_process by attaching it to _thread
  Compass::_thread.start(callback(this, &Compass::_update_process));
} // Compass::Compass constructor




/**
   ~Compass() is the destructor. Not too much to do. 
 */
Compass::~Compass(){
  debug("Compass destructor called\n");
}
