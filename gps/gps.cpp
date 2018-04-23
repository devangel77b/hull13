/*
   gps.cpp implementation file
   Dennis Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "gps.h"
//#include "TinyGPS.h"



/*
  Callback function for the wind birdie to control its reading. 
  _read_process() is private, should not be called from outside world
  Thread _WBThread will have this process running, which periodically reads
  the sensor, then does a thead-safe wait, allowing other stuff to happen.
 */
void Gps::_read_process(void){
  //char raw_string[82];
  
  while(1){
    // Take reading and apply calibration
    if (Gps::_gps.readable()){
	Gps::_parser.encode(Gps::_gps.getc()); 
      }
    
    // Thread-safe wait to relinquish to other processes. 
    Thread::wait(GPS_UPDATE_PERIOD);
  } // while(1)
} // _read_process()







/**
   Gps(tx,rx) is the constructor. Use this to declare a Gps
   connected to a particular port, e.g. Gps gps(PC_3,PC_3).

   @param tx is the RS232 serial tx pin
   @param rx is the RS232 serial rx pin
   @returns a Gps object

   For Hull 13 mod 2 rev D, GPSTX is PC_2, GPSRX is PC_3.
   The Copernicus II uses 4800 8N1 and is expected to put out
   NMEA0183 compliant sentences. 
 */
Gps::Gps(PinName tx, PinName rx):_gps(tx,rx){
  debug("Gps constructor called.\n"); // for debugging.
  Gps::_gps.baud(4800); // 4800 8N1
  Gps::_gps.format(8,SerialBase::None,1); 
  
  // the next line starts the Gps read process going in the thread.
  Gps::_thread.start(callback(this, &Gps::_read_process));
} // Gps(tx,rx) constructor






/**
   ~Gps() is the destructor. This one is not too complicated, not much
   to do...
*/
Gps::~Gps(){
  debug("Gps destructor called.\n");
} // ~Gps() destructor

void Gps::get_position(long *latitude, long *longitude, unsigned long *fix_age){
  Gps::_parser.get_position(latitude, longitude, fix_age); 
}

void Gps::get_datetime(unsigned long *date, unsigned long *time, unsigned long *fix_age){
  Gps::_parser.get_datetime(date, time, fix_age);
}

unsigned long Gps::course(){
  return Gps::_parser.course();
}

unsigned long Gps::speed(){
  return Gps::_parser.speed();
}

unsigned short Gps::satellites(){
  return Gps::_parser.satellites();
}
  
void Gps::f_get_position(float * latitude,
			 float * longitude,
			 unsigned long * fix_age){
  Gps::_parser.f_get_position(latitude, longitude, fix_age);
}

void Gps::crack_datetime(int *year, byte *month, byte *day, 
			 byte *hour, byte *minute, byte *second,
			 byte *hundredths, unsigned long *fix_age){
  Gps::_parser.crack_datetime(year, month, day,
			      hour, minute, second,
			      hundredths, fix_age);
}

float Gps::f_altitude(){
  return Gps::_parser.f_altitude();
}

float Gps::f_course(){
  return Gps::_parser.f_course();
}

float Gps::f_speed_knots(){
  return Gps::_parser.f_speed_knots();
}

float Gps::f_speed_mps(){
  return Gps::_parser.f_speed_mps();
}


