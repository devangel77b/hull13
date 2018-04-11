/*
   windbirdie.cpp implementation file
   Dennis Evangelista, MIDN Luke Marino, 2018
   
   Mr Marino added sensor health stuff in a fork of this that may get 
   pulled into this code at a later date. 
*/

#include "mbed.h"
#include "rtos.h"
#include "windbirdie.h"




/*
  Callback function for the wind birdie to control its reading. 
  _read_process() is private, should not be called from outside world
  Thread _WBThread will have this process running, which periodically reads
  the sensor, then does a thead-safe wait, allowing other stuff to happen.
 */
void WindBirdie::_read_process(void){
  while(1){
    // Take reading and apply calibration
    WindBirdie::raw = WindBirdie::_WBIn.read();
    WindBirdie::deg = WINDBIRDIE_CAL_M*WindBirdie::raw + WINDBIRDIE_CAL_B;

    // Thread-safe wait to relinquish to other processes. 
    Thread::wait(WINDBIRDIE_UPDATE_PERIOD);
  } // while(1)
} // _read_process()







/**
   WindBirdie(pin) is the constructor. Use this to declare a WindBirdie
   connected to a particular pin, e.g. WindBirdie windBirdie(p19).
   
   @param pin the AnalogIn pin the windbirdie is connected to
   @returns a WindBirdie object
 */
WindBirdie::WindBirdie(PinName pin):_WBIn(pin){
  debug("WindBirdie constructor called.\n"); // for debugging.
  WindBirdie::raw = WINDBIRDIE_CAL_B; // 0.5V input, 0 deg relative brg
  WindBirdie::deg = 0.0; // initialize to 0 deg relative brg
  
  // the next line starts the WindBirdie read process going in the thread.
  WindBirdie::_WBThread.start(callback(this, &WindBirdie::_read_process));
} // WindBirdie(pin) constructor






/**
   ~WindBirdie() is the destructor. This one is not too complicated, not much
   to do...
*/
WindBirdie::~WindBirdie(){
  debug("WindBirdie destructor called.\n");
} // ~WindBirdie() destructor
