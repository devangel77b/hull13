/*
  TESTS/gps/parsing/main.cpp
  GPS parsing test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "gps.h"
#include "TinyGPS.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
TinyGPS parser;
bool b;
char c;

bool sendstring(const char * teststring);
float latitude;
float longitude;
unsigned long fix_age;
unsigned long course;
unsigned long speed;
unsigned long date;
unsigned long t;




int main(void){

  pc.printf("GPS version ");
  pc.printf(GPS_VERSION);
  pc.printf("\n\rGPS parsing test\n\r");
  pc.printf("Test if parser is working right.\n\r");
  pc.printf("This is a port of the original TinyGps static test\n\r");



  pc.printf("Parsing GARBAGE\n\r");
  b = sendstring("GARBAGE");
  TEST_ASSERT_FALSE_MESSAGE(b,"GPS parser test failed, reading garbage as valid\n\r");




  pc.printf("$GPRMC,201547.000,A,3014.5527,N,09749.5808,W,0.24,163.05,040109,,*1A\n\r");
  b = sendstring("$GPRMC,201547.000,A,3014.5527,N,09749.5808,W,0.24,163.05,040109,,*1A\n");
  TEST_ASSERT_TRUE_MESSAGE(b,"GPS praser test failed, not reading valid $GPRMC\n\r");
  parser.f_get_position(&latitude, &longitude, &fix_age);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(30.242544,latitude,
				  "GPS parser test failed, latitude\n\r");
  pc.printf("latitude %f\n\r",latitude);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-97.82634666666,longitude,
				  "GPS parser test failed, longitude\n\r");
  pc.printf("longitude %f\n\r",longitude);
  parser.get_datetime(&date,&t,&fix_age);
  pc.printf("date %d time %d\n\r",date,time);
  course=parser.f_course();
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(163,course,
				  "GPS parser test failed, course\n\r");
  speed=parser.f_speed_knots();
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.240000,speed,"GPS parser test failed, speed\n\r");

  /*
  pc.printf("BLAH$GPGGA,201548.000,3014.5529,N,09749.5808,W,1,07,1.5,225.6,M,-22.5,M,18.8,0000*78\n\r");
  b = sendstring("BLAH$GPGGA,201548.000,3014.5529,N,09749.5808,W,1,07,1.5,225.6,M,-22.5,M,18.8,0000*78\n");
  TEST_ASSERT_TRUE_MESSAGE(b,"GPS praser test failed, not reading valid $GPGGA\n\r");
  parser.f_get_position(&latitude, &longitude, &fix_age);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(latitude,30.252545,
				  "GPS parser test failed, latitude\n\r");
  pc.printf("latitude %f\n\r",latitude);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(longitude,-97.82634666666,
				  "GPS parser test failed, longitude\n\r");
  pc.printf("longitude %f\n\r",longitude);
  parser.get_datetime(&date,&t,&fix_age);
  pc.printf("date %d time %d\n\r",date,time);
  

  pc.printf("$GPRMC,201548.000,A,3014.5529,N,09749.5808,W,0.17,53.25,040109,,*2B SMEG\n\r");
  b = sendstring("$GPRMC,201548.000,A,3014.5529,N,09749.5808,W,0.17,53.25,040109,,*2B\nSMEG");
  TEST_ASSERT_TRUE_MESSAGE(b,"GPS praser test failed, not reading valid $GPRMC\n\r");
  parser.f_get_position(&latitude, &longitude, &fix_age);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(latitude,30.24254833333,
				  "GPS parser test failed, latitude\n\r");
  pc.printf("latitude %f\n\r",latitude);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(longitude,-97.82634666666,
				  "GPS parser test failed, longitude\n\r");
  pc.printf("longitude %f\n\r",longitude);
  parser.get_datetime(&date,&t,&fix_age);
  pc.printf("date %d time %d\n\r",date,time);
  course=parser.f_course();
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(course,53.25,
				  "GPS parser test failed, course\n\r");
  speed=parser.f_speed_knots();
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(speed,0.17,"GPS parser test failed, speed\n\r");


  pc.printf("BLAH $GPGGA,201549.000,3014.5533,N,09749.5812,W,1,07,1.5,223.5,M,-22.5,M,18.8,0000*7C SMEG\n\r");
  b = sendstring("BLAH $GPGGA,201549.000,3014.5533,N,09749.5812,W,1,07,1.5,223.5,M,-22.5,M,18.8,0000*7C\nSMEG");
  TEST_ASSERT_TRUE_MESSAGE(b,"GPS praser test failed, not reading valid $GPGGA\n\r");
  parser.f_get_position(&latitude, &longitude, &fix_age);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(latitude,30.252555,
				  "GPS parser test failed, latitude\n\r");
  pc.printf("latitude %f\n\r",latitude);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(longitude,-97.82635333333,
				  "GPS parser test failed, longitude\n\r");
  pc.printf("longitude %f\n\r",longitude);
  parser.get_datetime(&date,&t,&fix_age);
  pc.printf("date %d time %d\n\r",date,time);
  */

}// main() for TESTS/gps/hello






bool sendstring(const char * teststring){
  int c=0;
  bool result=0;
  while (teststring[c]){
    result = parser.encode(teststring[c]);
    pc.printf("result %d ",result);
    if (result)
      {pc.printf("%c \n\r",teststring[c]);}
    else
      {pc.printf("%c BAD\n\r",teststring[c]);}
    c++;
  }
  return result;
}
