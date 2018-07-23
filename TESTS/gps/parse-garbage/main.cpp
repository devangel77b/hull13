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
  pc.printf("Test if parser is working right.\n\r");
  pc.printf("Show me a negative before I'll give you a positive.");
  
  pc.printf("Parsing GARBAGE...\n\r");
  sendstring("GARBAGE$GPGGA,GO,ARMY,,BEAT,NAVY,1,2,3,4,5,6,3.14159\n\r");
  TEST_ASSERT_FALSE_MESSAGE(parser.date.isValid(),"Reading garbage as valid\n\r");
  TEST_ASSERT_FALSE_MESSAGE(parser.time.isValid(),"Reading garbage as valid\n\r");
  TEST_ASSERT_FALSE_MESSAGE(parser.location.isValid(),"Reading garbage as valid\n\r");
  TEST_ASSERT_FALSE_MESSAGE(parser.course.isValid(),"Reading garbage as valid\n\r");
  TEST_ASSERT_FALSE_MESSAGE(parser.speed.isValid(),"Reading garbage as valid\n\r");

  pc.printf("Test passed!\n\r");



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
