/*
  compass.h header file
  Dennis Evangelista, 2018

  The compass in Hull 13 is an Adafruit BNO055 Absolute Orientation sensor. 
 */


#ifndef COMPASS_H // make sure the header is only done once
#define COMPASS_H

#include "mbed.h"
#include "rtos.h"
#include "BNO055.h" // StressedDave BNO055 library
// https://os.mbed.com/users/StressedDave/code/BNO055

#define COMPASS_VERSION "13.2.0"
#define COMPASS_UPDATE_PERIOD_MS 100 // ms, default update period


/**
   This is the main interface to the outside world for the compass (API). 
   Use it as follows:
   @code
   #include "compass.h"
   #include "mbed.h"
   #include "rtos.h"

   Compass compass(PC_9, PC_8);
   
   int main(){
     while(1){
       printf("Heading %3.0f", compass.hdg);
       Thread::wait(1000);
     } // while(1)
   } // main
   @endcode
 */
class Compass{
 private: // these should not be messed with by the outside world

  Thread _thread; // a Thread for running the sensor in
  void _update_process(void); // the actual routine runnine in the Thread
  BNO055 _bno055; // the actual sensor is this

 public: // outside world is allowed to use these
  float hdg;  // heading value
  Compass(PinName sda, PinName scl); // constructor
  ~Compass(void); // destructor
}; // Compass class definition

#endif
