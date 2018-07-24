/*
  TESTS/integrated/gpsnlog/main.cpp
  Integrated test of GPS and logger at the same time
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "gps.h"
#include "logger.h"
#include "xbee.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
Gps gps(PC_2, PC_3);
Logger logger(PC_10,PC_11,9600);
XBee telem(PC_12,PD_2,57600);

int main(){
  pc.printf("GPS version %s\n\r",GPS_VERSION);
  pc.printf("Logger version %s\n\r",LOGGER_VERSION);
  pc.printf("Integrated test of GPS and logging\n\r");
  pc.printf("Take a walk!\n\r");
  pc.printf("date, time, YYYY-MM-DD, HH:mm:ss.ss, lat, long, cog, sog, sat\n\r");

  logger.printf("GPS version %s\n",GPS_VERSION);
  logger.printf("Logger version %s\n",LOGGER_VERSION);
  logger.printf("Integrated test of GPS and logging\n");
  logger.printf("Take a walk! OpenLogger output\n");
  logger.printf("date, time, YYYY-MM-DD, HH:mm:ss.ss, lat, long, cog, sog, sat\n");
  
  telem.printf("GPS version %s\n",GPS_VERSION);
  telem.printf("Logger version %s\n",LOGGER_VERSION);
  telem.printf("Integrated test of GPS and logging\n");
  telem.printf("Take a walk! Xbee output\n");
  telem.printf("date, time, YYYY-MM-DD, HH:mm:ss.ss, lat, long, cog, sog, sat\n");
  
  while(1){
    // date
    if (gps.parser.date.isValid()){
      pc.printf("%d, ", gps.parser.date.value());
      logger.printf("%d, ", gps.parser.date.value());
      telem.printf("%d, ", gps.parser.date.value());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }
    
    // time
    if (gps.parser.time.isValid()){
      pc.printf("%d, ", gps.parser.time.value());
      logger.printf("%d, ", gps.parser.time.value());
      telem.printf("%d, ", gps.parser.time.value());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }
    
    // YYYY-MM-DD
    if (gps.parser.date.isValid()){
      pc.printf("%04d-%02d-%02d, ", gps.parser.date.year(),
		gps.parser.date.month(), gps.parser.date.day());
      logger.printf("%04d-%02d-%02d, ", gps.parser.date.year(),
		    gps.parser.date.month(), gps.parser.date.day());
      telem.printf("%04d-%02d-%02d, ", gps.parser.date.year(),
		   gps.parser.date.month(), gps.parser.date.day());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }
    
    // HH:mm:ss.ss
    if (gps.parser.time.isValid()){
      pc.printf("%02d:%02d:%02d.%02d, ", gps.parser.time.hour(),
		gps.parser.time.minute(), gps.parser.time.second(),
		gps.parser.time.centisecond());
      logger.printf("%02d:%02d:%02d.%02d, ", gps.parser.time.hour(),
		    gps.parser.time.minute(), gps.parser.time.second(),
		    gps.parser.time.centisecond());
      telem.printf("%02d:%02d:%02d.%02d, ", gps.parser.time.hour(),
		   gps.parser.time.minute(), gps.parser.time.second(),
		   gps.parser.time.centisecond());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }
    
    // lat lng
    if (gps.parser.location.isValid()){
      pc.printf("%f, %f, ",gps.parser.location.lat(),
		gps.parser.location.lng());
      logger.printf("%f, %f, ",gps.parser.location.lat(),
		    gps.parser.location.lng());
      telem.printf("%f, %f, ",gps.parser.location.lat(),
		   gps.parser.location.lng());
    }
    else {
      pc.printf("NA, NA, ");
      logger.printf("NA, NA, ");
      telem.printf("NA, NA, ");
    }

    // course
    if (gps.parser.course.isValid()){
      pc.printf("%05.1f, ", gps.parser.course.deg());
      logger.printf("%05.1f, ", gps.parser.course.deg());
      telem.printf("%05.1f, ", gps.parser.course.deg());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }

    // speed
    if (gps.parser.speed.isValid()){
      pc.printf("%4.1f", gps.parser.speed.knots());
      logger.printf("%4.1f", gps.parser.speed.knots());
      telem.printf("%4.1f", gps.parser.speed.knots());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }

    // satellites, hdop
    pc.printf("%d\n\r",gps.parser.satellites.value());
    logger.printf("%d\n",gps.parser.satellites.value());
    telem.printf("%d\n",gps.parser.satellites.value());
    


  
    
    Thread::wait(1000); 
  } // while(1)

  
} // TESTS/integrated/logngps/main
