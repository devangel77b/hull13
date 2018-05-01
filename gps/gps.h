
/*
  gps.h header file
  Dennis Evangelista, 2018

  The gps receiver in Hull 13 is a Sparkfun/Trimble Copernicus II 
  breakout board. It is connected to the main processor using a Serial
  port set to 4800 8N1. For Hull 13 mod 2 rev D, GPSTX is PC_2, GPSRX is
  PC_3. 
*/



#ifndef GPS_H // these lines make sure the header is only done once
#define GPS_H

#include "mbed.h"
#include "rtos.h"
#include "TinyGPS.h" // parser from DRob

#define GPS_VERSION "13.2.1"

#define GPS_UPDATE_PERIOD 10 // ms, default update period



/**
   The main interface to the outside world is this `Gps` class (API).
   A user will declare, for example: `Gps gps(PC_2,PC_3)`

   @code
   #include "gps.h"
   #include "mbed.h"
   #include "rtos.h"

   Gps gps(PC_2,PC_3); 

   int main(){
     while(1){
       //TBD
       } // while 1
   } // main
   @endcode

*/
class Gps{

 private:
  // These should not be messed with by the outside world...

  mbed::Serial _gps; // Serial port the sensor is connected to
  Thread _thread; // a Thread for running the sensor in.
  void _rx_callback(void); // the actual routine running in the Thread.
  TinyGPS _parser; 



 public:
  // The outside world is allowed to use these...
  bool newdata; 
  
  // function prototype for the constructor (very special).
  // the constructor creates a new Gps object...
  // For Hull 13 mod 2 rev D, GPSTX is PC_2, GPSRX is PC_3
  Gps(PinName tx, PinName rx);

  // function prototype for the destructor (also special).
  // the destructor is called when the Gps object is disposed of.
  ~Gps(void);

  // expose these from the parser
  void get_position(long *latitude, long *longitude, unsigned long *fix_age=0);
  void get_datetime(unsigned long *date, unsigned long *time, unsigned long *fix_age=0);
  unsigned long course();
  unsigned long speed();
  unsigned short satellites();
  
  void f_get_position(float * latitude,
		      float * longitude,
		      unsigned long * fix_age=0);
  void crack_datetime(int *year, byte *month, byte *day, 
    byte *hour, byte *minute, byte *second, byte *hundredths = 0, unsigned long *fix_age = 0);
  float f_altitude();
  float f_course();
  float f_speed_knots();
  float f_speed_mph();
  float f_speed_mps();
  float f_speed_kmph();
  
}; // class Gps header definition

#endif
