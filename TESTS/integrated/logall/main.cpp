/*
  TESTS/integrated/logall/main.cpp
  Log everything test while pushing around on a cart
  Dennis Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "windbirdie.h"
#include "compass.h"
#include "gps.h"
#include "logger.h"
#include "xbee.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
WindBirdie windBirdie(PC_4);
Compass compass(PB_9,PB_8); 
Gps gps(PC_2, PC_3);

Logger logger(PC_10,PC_11,9600);
XBee telem(PC_12,PD_2,57600);
float hdg;


int main(){
  pc.printf("Windbirdie version %s\n\r",WINDBIRDIE_VERSION);
  pc.printf("Compass version %s\n\r",COMPASS_VERSION);
  pc.printf("GPS version %s\n\r",GPS_VERSION);
  pc.printf("Logger version %s\n\r",LOGGER_VERSION);
  pc.printf("XBee version %s\n\r",XBEE_VERSION);
  pc.printf("Integrated test of GPS and logging\n\r");
  pc.printf("Take a walk!\n\r");
  pc.printf("wb_raw,wb_deg,wb_rel,mag_hdg,date,time,yyyy-mm-dd,HH:mm:ss.ss,lat,lon,cog,sog,sat\n\r");

  logger.printf("Windbirdie version %s\n\r",WINDBIRDIE_VERSION);
  logger.printf("Compass version %s\n\r",COMPASS_VERSION);
  logger.printf("GPS version %s\n\r",GPS_VERSION);
  logger.printf("Logger version %s\n\r",LOGGER_VERSION);
  logger.printf("XBee version %s\n\r",XBEE_VERSION);
  logger.printf("Integrated test of GPS and logging\n\r");
  logger.printf("Integrated test of GPS and logging\n");
  logger.printf("Take a walk! OpenLogger output\n\r");
  logger.printf("wb_raw,wb_deg,wb_rel,mag_hdg,date,time,yyyy-mm-dd,HH:mm:ss.ss,lat,lon,cog,sog,sat\n\r");
  
  telem.printf("Windbirdie version %s\n\r",WINDBIRDIE_VERSION);
  telem.printf("Compass version %s\n\r",COMPASS_VERSION);
  telem.printf("GPS version %s\n\r",GPS_VERSION);
  telem.printf("Logger version %s\n\r",LOGGER_VERSION);
  telem.printf("XBee version %s\n\r",XBEE_VERSION);
  telem.printf("Integrated test of GPS and logging\n\r");
  telem.printf("Integrated test of GPS and logging\n\r");
  telem.printf("Take a walk! Xbee output\n\r");
  telem.printf("wb_raw,wb_deg,wb_rel,mag_hdg,date,time,yyyy-mm-dd,HH:mm:ss.ss,lat,lon,cog,sog,sat\n\r");
  
  while(1){
    // wind birdie readings
    pc.printf("%5.3f, %5.1f, %5.1f, ",windBirdie.raw,windBirdie.deg,windBirdie.rdeg);
    logger.printf("%5.3f, %5.1f, %5.1f, ",windBirdie.raw,windBirdie.deg,windBirdie.rdeg);
    telem.printf("%5.3f, %5.1f, %5.1f, ",windBirdie.raw,windBirdie.deg,windBirdie.rdeg);

    // compass heading (magnetic)
    hdg = compass.hdg; 
    pc.printf("%5.1f, ",hdg);
    logger.printf("%5.1f, ",hdg);
    telem.printf("%5.1f, ",hdg);
    
    // date
    if (gps.parser.date.isValid()){
      pc.printf("%d, ",gps.parser.date.value());
      logger.printf("%d, ",gps.parser.date.value());
      telem.printf("%d, ",gps.parser.date.value());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }
    
    // time
    if (gps.parser.time.isValid()){
      pc.printf("%d, ",gps.parser.time.value());
      logger.printf("%d, ",gps.parser.time.value());
      telem.printf("%d, ",gps.parser.time.value());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }

    // date
    if (gps.parser.date.isValid()){
      pc.printf("%04d-%02d-%02d, ",gps.parser.date.year(),
		gps.parser.date.month(),
		gps.parser.date.day());
      logger.printf("%04d-%02d-%02d, ",gps.parser.date.year(),
		    gps.parser.date.month(),
		    gps.parser.date.day());
      telem.printf("%04d-%02d-%02d, ",gps.parser.date.year(),
		   gps.parser.date.month(),
		   gps.parser.date.day());      
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }

    // time
    if (gps.parser.time.isValid()){
      pc.printf("%02d:%02d:%02d.%02d, ",
		gps.parser.time.hour(),
		gps.parser.time.minute(),
		gps.parser.time.second(),
		gps.parser.time.centisecond());
      logger.printf("%02d:%02d:%02d.%02d, ",
		    gps.parser.time.hour(),
		    gps.parser.time.minute(),
		    gps.parser.time.second(),
		    gps.parser.time.centisecond());
      telem.printf("%02d:%02d:%02d.%02d, ",
		   gps.parser.time.hour(),
		   gps.parser.time.minute(),
		   gps.parser.time.second(),
		   gps.parser.time.centisecond());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }
    
    // lat and lon
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
      pc.printf("%04.1, ",gps.parser.speed.knots());
      logger.printf("%04.1, ",gps.parser.speed.knots());
      telem.printf("%04.1f, ",gps.parser.speed.knots());
    }
    else {
      pc.printf("NA, ");
      logger.printf("NA, ");
      telem.printf("NA, ");
    }

    // satellites
    pc.printf("%d\n\r",gps.parser.satellites.value());
    logger.printf("%d\n",gps.parser.satellites.value());
    telem.printf("%d\n",gps.parser.satellites.value());
    
    
    Thread::wait(1000); 
  } // while(1)

  
} // TESTS/integrated/logall/main
