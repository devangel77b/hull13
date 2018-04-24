/*
   gps.cpp implementation file
   Dennis Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "gps.h"
#include "TinyGPS.h"



/*
  Callback function for the gps, to be attached to RxIrq on the Serial 
  connection _gps to the Copernicus II.
 */
void Gps::_rx_callback(void){
  // have to actually read to clear the interrupt 
  Gps::newdata = Gps::_parser.encode(Gps::_gps.getc()); 
}
    







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
  
  // the next line attaches the rx callback to Gps rx irq
  Gps::_gps.attach(callback(this,&Gps::_rx_callback),Serial::RxIrq);
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


