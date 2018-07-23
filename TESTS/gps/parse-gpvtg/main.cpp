/*
  TESTS/gps/parse-gpvtg/main.cpp
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
TinyGPSCustom track_made_good_true(parser,"GPVTG",1);
TinyGPSCustom speed_over_ground_knots(parser,"GPVTG",5);
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
  pc.printf("Test if parser does GPVTG.\n\r");
  
  // test a GPVTG message
  pc.printf("$GPVTG,314.4,T,325.3,M,002.6,N,004.8,K,A*2E\n\r");
  sendstring("$GPVTG,314.4,T,325.3,M,002.6,N,004.8,K,A*2E\n");
  TEST_ASSERT_TRUE_MESSAGE(track_made_good_true.isValid(),"failed to parse GPVTG message\n\r");
  pc.printf("track made good %f T\n\r",atof(track_made_good_true.value()));
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(314.4,atof(track_made_good_true.value()),"course wrong\n\r");
  TEST_ASSERT_TRUE_MESSAGE(speed_over_ground_knots.isValid(),"failed to parse GPVTG message\n\r");
  pc.printf("speed over ground %f knots\n\r", atof(speed_over_ground_knots.value()));
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(2.60000,atof(speed_over_ground_knots.value()),"speed wrong\n\r");
  
  pc.printf("date %d%02d%02d\n\r",parser.date.year(),parser.date.month(),parser.date.day());
  pc.printf("time %d:%d:%d.%02d\n\r",parser.time.hour(),parser.time.minute(),parser.time.second(),parser.time.centisecond());


}// main() for TESTS/gps/parse-gpvtg






void sendstring(const char * teststring){
  int c=0;
  bool result;
  while (teststring[c]){
    result = parser.encode(teststring[c]);
    pc.printf("%d %c \n\r ",result, teststring[c]);
    c++;
  } // while
}// sendstring
