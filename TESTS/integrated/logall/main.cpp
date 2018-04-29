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

float longitude;
float latitude;
float course;
float speed;
int year;
byte month;
byte day;
byte hour;
byte minute;
byte second;
byte hundredths; 
unsigned long fix_age;
unsigned long gdate;
unsigned long gtime; 
float hdg; 

int main(){
  pc.printf("Windbirdie version %s\n\r",WINDBIRDIE_VERSION);
  pc.printf("Compass version %s\n\r",COMPASS_VERSION);
  pc.printf("GPS version %s\n\r",GPS_VERSION);
  pc.printf("Logger version %s\n\r",LOGGER_VERSION);
  pc.printf("XBee version %s\n\r",XBEE_VERSION);
  pc.printf("Integrated test of GPS and logging\n\r");
  pc.printf("Take a walk!\n\r");
  pc.printf("wb_raw,wb_deg,wb_rel,mag_hdg,date,time,yyyymmdd,HH:mm:ss.ss,lon,lat,cse,spd\n\r");

  logger.printf("Windbirdie version %s\n\r",WINDBIRDIE_VERSION);
  logger.printf("Compass version %s\n\r",COMPASS_VERSION);
  logger.printf("GPS version %s\n\r",GPS_VERSION);
  logger.printf("Logger version %s\n\r",LOGGER_VERSION);
  logger.printf("XBee version %s\n\r",XBEE_VERSION);
  logger.printf("Integrated test of GPS and logging\n\r");
  logger.printf("Integrated test of GPS and logging\n");
  logger.printf("Take a walk! OpenLogger output\n\r");
  logger.printf("wb_raw,wb_deg,wb_rel,mag_hdg,date,time,yyyymmdd,HH:mm:ss.ss,lon,lat,cse,spd\n\r");
  
  telem.printf("Windbirdie version %s\n\r",WINDBIRDIE_VERSION);
  telem.printf("Compass version %s\n\r",COMPASS_VERSION);
  telem.printf("GPS version %s\n\r",GPS_VERSION);
  telem.printf("Logger version %s\n\r",LOGGER_VERSION);
  telem.printf("XBee version %s\n\r",XBEE_VERSION);
  telem.printf("Integrated test of GPS and logging\n\r");
  telem.printf("Integrated test of GPS and logging\n\r");
  telem.printf("Take a walk! Xbee output\n\r");
  telem.printf("wb_raw,wb_deg,wb_rel,mag_hdg,date,time,yyyymmdd,HH:mm:ss.ss,lon,lat,cse,spd\n\r");
  
  while(1){
    pc.printf("%5.3f, %5.1f, %5.1f, ",windBirdie.raw,windBirdie.deg,windBirdie.rdeg);
    logger.printf("%5.3f, %5.1f, %5.1f, ",windBirdie.raw,windBirdie.deg,windBirdie.rdeg);
    telem.printf("%5.3f, %5.1f, %5.1f, ",windBirdie.raw,windBirdie.deg,windBirdie.rdeg);

    hdg = compass.hdg; 
    pc.printf("%5.1f, ",hdg);
    logger.printf("%5.1f, ",hdg);
    telem.printf("%5.1f, ",hdg);
    
    
    gps.get_datetime(&gdate, &gtime, &fix_age);
    pc.printf("%d, %d, ",gdate,gtime);
    logger.printf("%d, %d, ",gdate,gtime);
    telem.printf("%d, %d, ",gdate,gtime);

    gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths,&fix_age);
    pc.printf("%d%02d%02d, %02d:%02d:%02d.%02d, ",year,month,day,hour,minute,second,hundredths);
    logger.printf("%d%02d%02d, %02d:%02d:%02d.%02d, ",year,month,day,hour,minute,second,hundredths);
    telem.printf("%d%02d%02d, %02d:%02d:%02d.%02d, ",year,month,day,hour,minute,second,hundredths); 
    
    gps.f_get_position(&latitude, &longitude, &fix_age);
    course = gps.f_course();
    speed = gps.f_speed_knots();
    pc.printf("%f, %f, %5.1f, %4.1\n\r",longitude,latitude,course,speed);
    logger.printf("%f, %f, %5.1f, %4.1\n\r",longitude,latitude,course,speed);
    telem.printf("%f, %f, %5.1f, %4.1\n\r",longitude,latitude,course,speed);


  
    
    Thread::wait(1000); 
  } // while(1)

  
} // TESTS/integrated/logall/main
