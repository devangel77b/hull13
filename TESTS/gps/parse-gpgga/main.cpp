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
  pc.printf("Test if parser can do GPGGA-GPRMC-GPGGA messsage sequence.\n\r");

  
  // test a GPGGA message  
  pc.printf("$GPGGA,201548.000,3014.5529,N,09749.5808,W,1,07,1.5,225.6,M,-22.5,M,18.8,0000*78\n\r");
  sendstring("$GPGGA,201548.000,3014.5529,N,09749.5808,W,1,07,1.5,225.6,M,-22.5,M,18.8,0000*78\n");
  TEST_ASSERT_TRUE_MESSAGE(parser.location.isValid(),"failed to parse GPGGA message\n\r");
  pc.printf("lat %f, lon %f\n\r",parser.location.lat(),parser.location.lng());
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(30.242548,parser.location.lat(),"lat wrong\n\r");
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-97.82634666666,parser.location.lng(),"lng wrong\n\r");
  pc.printf("date %04d-%02d-%02d\n\r",parser.date.year(),parser.date.month(),parser.date.day());
  pc.printf("time %d:%d:%d.%02d\n\r",parser.time.hour(),parser.time.minute(),parser.time.second(),parser.time.centisecond());
  wait(10);
  
  pc.printf("$GPRMC,201548.000,A,3014.5529,N,09749.5808,W,0.17,53.25,040109,,*2B SMEG\n\r");
  sendstring("$GPRMC,201548.000,A,3014.5529,N,09749.5808,W,0.17,53.25,040109,,*2B\nSMEG");
  TEST_ASSERT_TRUE_MESSAGE(parser.location.isValid(),"Failed to parse GPRMC message\n\r");
    pc.printf("lat %f, lon %f\n\r",parser.location.lat(),parser.location.lng());
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(30.24254833333,parser.location.lat(),"lat wrong\n\r");
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-97.82634666666,parser.location.lng(),"lng wrong\n\r");
  pc.printf("course %f\n\r",parser.course.deg());
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(53.25,parser.course.deg(),"course wrong\n\r");
  pc.printf("speed %f\n\r",parser.speed.knots());
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(0.17,parser.speed.knots(),"speed wrong\n\r");
  pc.printf("date %04d-%02d-%02d\n\r",parser.date.year(),parser.date.month(),parser.date.day());
  pc.printf("time %d:%d:%d.%02d\n\r",parser.time.hour(),parser.time.minute(),parser.time.second(),parser.time.centisecond());
  wait(10);

  
  pc.printf("BLAH $GPGGA,201549.000,3014.5533,N,09749.5812,W,1,07,1.5,223.5,M,-22.5,M,18.8,0000*7C SMEG\n\r");
  sendstring("BLAH $GPGGA,201549.000,3014.5533,N,09749.5812,W,1,07,1.5,223.5,M,-22.5,M,18.8,0000*7C\nSMEG");
  TEST_ASSERT_TRUE_MESSAGE(parser.location.isValid(),"failed to parse GPGGA message\n\r");
  pc.printf("lat %f, lon %f\n\r",parser.location.lat(),parser.location.lng());
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(30.242556,parser.location.lat(),"lat wrong\n\r");
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(-97.82635333333,parser.location.lng(),"lng wrong\n\r");
  pc.printf("date %04d-%02d-%02d\n\r",parser.date.year(),parser.date.month(),parser.date.day());
  pc.printf("time %d:%d:%d.%02d\n\r",parser.time.hour(),parser.time.minute(),parser.time.second(),parser.time.centisecond());
}// main() for TESTS/gps/parse-gpgga






void sendstring(const char * teststring){
  int c=0;
  bool result;
  while (teststring[c]){
    result = parser.encode(teststring[c]);
    pc.printf("%d %c \n\r ",result, teststring[c]);
    c++;
  } // while
}// sendstring
