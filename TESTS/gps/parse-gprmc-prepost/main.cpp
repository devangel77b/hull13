/*
  TESTS/gps/parsing/main.cpp
  GPS parsing test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "gps.h"
#include "TinyGPSplus.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
TinyGPSPlus parser;
bool b;
char c;

void sendstring(const char * teststring);
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
  pc.printf("Test if parser correctly parses a GPRMC message with junk pre and post\n\r");
  

  // test a GPRMC message
  pc.printf("BLAH... $GPRMC,201547.000,A,3014.5527,N,09749.5808,W,0.24,163.05,040109,,*1A\n\r SMEG");
  sendstring("BLAH... $GPRMC,201547.000,A,3014.5527,N,09749.5808,W,0.24,163.05,040109,,*1A\n SMEG");
  TEST_ASSERT_TRUE_MESSAGE(parser.location.isValid(),"failed to parse GPRMC message\n\r");
  pc.printf("lat %f, lon %f\n\r",parser.location.lat(),parser.location.lng());
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(30.242544,parser.location.lat(),"lat wrong\n\r");
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-97.82634666666,parser.location.lng(),"lng wrong\n\r");
  pc.printf("course %f\n\r",parser.course.deg());
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(163.0500003,parser.course.deg(),"course wrong\n\r");
  pc.printf("speed %f\n\r",parser.speed.knots());
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.240000,parser.speed.knots(),"speed wrong\n\r");
  pc.printf("date %d%02d%02d\n\r",parser.date.year(),parser.date.month(),parser.date.day());
  pc.printf("time %d:%d:%d.%02d\n\r",parser.time.hour(),parser.time.minute(),parser.time.second(),parser.time.centisecond());

  
}// main() for TESTS/gps/hello






void sendstring(const char * teststring){
  int c=0;
  bool result;
  while (teststring[c]){
    result = parser.encode(teststring[c]);
    pc.printf("%d %c \n\r ",result, teststring[c]);
    c++;
  } // while
}// sendstring
