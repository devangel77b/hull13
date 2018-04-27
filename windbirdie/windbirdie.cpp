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
    if (WindBirdie::deg < 180)
      { WindBirdie::rdeg = WindBirdie::deg;}
    else
      { WindBirdie::rdeg = -(360.0-WindBirdie::deg);}

    // Thread-safe wait to relinquish to other processes. 
    Thread::wait(WINDBIRDIE_UPDATE_PERIOD);
  } // while(1)
} // _read_process()







/**
   WindBirdie(pin) is the constructor. Use this to declare a WindBirdie
   connected to a particular pin, e.g. WindBirdie windBirdie(PC_4).
   
   @param pin the AnalogIn pin the windbirdie is connected to
   @returns a WindBirdie object

   The AnalogIn pin should be PC_4 in Hull 13 mod 2 rev D.
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
