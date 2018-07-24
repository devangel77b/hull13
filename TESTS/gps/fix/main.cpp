/*
  TESTS/gps/fix/main.cpp
  GPS fix test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "gps.h"
#include "TinyGPSplus.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
Gps gps(PC_2, PC_3);
char c;

int n=0;

Thread thready;

void printy(void){
  while(1){
    pc.printf("%d. ",n++);
    if (gps.parser.location.isValid())
      pc.printf("lat %f, lon %f ",
		gps.parser.location.lat(),
		gps.parser.location.lng());
    else
      pc.printf("lat NA, lon NA ");

    if (gps.parser.course.isValid())
      pc.printf("course %f, ",gps.parser.course.deg());
    else
      pc.printf("course NA, ");

    if (gps.parser.speed.isValid())
      pc.printf("speed %f knots, ",gps.parser.speed.knots());
    else
      pc.printf("speed NA, ");

    pc.printf("sats %d\n\r",gps.parser.satellites.value());
    Thread::wait(1000);
  }
}



int main(void){

  pc.printf("GPS version ");
  pc.printf(GPS_VERSION);
  pc.printf("\n\rGPS fix test\n\r");
  pc.printf("Try to get actual GPS fixes.\n\r");
  pc.printf("This is a version of TinyGPS simple test / test with gps device.\n\r");
  pc.printf("Be sure antenna is attached; may take some time to get satellites.\n\r");

  thready.start(callback(printy));

  //pc.printf("Was it successful (y/n)?\n\r");
  //pc.scanf("%c", &c);
  //TEST_ASSERT_TRUE_MESSAGE((c == 'y'),"GPS fix test failed\n\r");

}// main() for TESTS/gps/fix






