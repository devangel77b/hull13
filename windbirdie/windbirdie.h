
/*
  windbirdie.h header file
  Dennis Evangelista and MIDN L Marino, 2018

  The wind sensor in Hull 13 is a Honeywell RTY360LVNAX sensor connected
  through a voltage divider? (TBD). 
*/



#ifndef WINDBIRDIE_H // these lines make sure the header is only done once
#define WINDBIRDIE_H

#include "mbed.h"
#include "rtos.h"

#define WINDBIRDIE_VERSION "13.2.0"

#define WINDBIRDIE_UPDATE_PERIOD 500 // ms, default update period
#define WINDBIRDIE_CAL_M 450.0 // calibration constant, fix! TODO
#define WINDBIRDIE_CAL_B -44.99999999999999 // calibration constant, fix! TODO



/**
   The main interface to the outside world is this WindBirdie class (API).
   A user will declare, for example: WindBirdie WB(p20)
   Once it's declared, the sensor handles periodically polling the
   AnalogIn pin it is connected to. The most recent measurement is accessed
   using a property, the float value windBirdie.raw for the raw measurement
   or windBirdie.deg for the measurement converted to degrees. 
   @code
   #include "windbirdie.h"
   #include "mbed.h"
   #include "rtos.h"

   WindBirdie windBirdie(PC_4); 

   int main(){
     while(1){
       printf("Sensor reading %f", windBirdie.deg);
       Thread::wait(1000);
       } // while 1
   } // main
   @endcode

*/
class WindBirdie{

 private:
  // These should not be messed with by the outside world...

  mbed::AnalogIn _WBIn; // AnalogIn pin the sensor is connected to
  Thread _WBThread; // a Thread for running the sensor in.
  void _read_process(void); // the actual routine running in the Thread.




 public:
  // The outside world is allowed to use these...

  /// float that holds the most recent analog reading 0.0 to 1.0
  float raw;

  /// float that holds the most recent reading in degrees
  float deg;

  /// float to hold most recent reading in degrees relative
  float rdeg; 
  
  // function prototype for the constructor (very special).
  // the constructor creates a new WindBirdie object...
  // The PWM pin is PC_4 in Hull 13 mod 2 rev D.
  WindBirdie(PinName pin);

  // function prototype for the destructor (also special).
  // the destructor is called when the WindBirdie object is disposed of.
  ~WindBirdie(void);
}; // class WindBirdie header definition

#endif
