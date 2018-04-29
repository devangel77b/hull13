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

int main(){
  pc.printf("GPS version %s\n\r",GPS_VERSION);
  pc.printf("Logger version %s\n\r",LOGGER_VERSION);
  pc.printf("Integrated test of GPS and logging\n\r");
  pc.printf("Take a walk!\n\r");
  pc.printf("date, time, YYMMDD, HH:mm:ss.ss, lat, long, cse, spd\n\r");

  logger.printf("GPS version %s\n",GPS_VERSION);
  logger.printf("Logger version %s\n",LOGGER_VERSION);
  logger.printf("Integrated test of GPS and logging\n");
  logger.printf("Take a walk! OpenLogger output\n");
  logger.printf("date, time, YYMMDD, HH:mm:ss.ss, lat, long, cse, spd\n");
  
  telem.printf("GPS version %s\n",GPS_VERSION);
  telem.printf("Logger version %s\n",LOGGER_VERSION);
  telem.printf("Integrated test of GPS and logging\n");
  telem.printf("Take a walk! Xbee output\n");
  telem.printf("date, time, YYMMDD, HH:mm:ss.ss, lat, long, cse, spd\n");
  
  while(1){
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
    pc.printf("%f, %f, %05.1f, %4.1\n\r",longitude,latitude,course,speed);
    logger.printf("%f, %f, %05.1f, %4.1\n",longitude,latitude,course,speed);
    telem.printf("%f, %f, %05.1f, %4.1\n",longitude,latitude,course,speed);


  
    
    Thread::wait(1000); 
  } // while(1)

  
} // TESTS/integrated/logngps/main
