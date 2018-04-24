/*
  TESTS/gps/fix/main.cpp
  GPS fix test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "gps.h"
#include "TinyGPS.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
Gps gps(PC_2, PC_3);
bool b;
char c;

float latitude;
float longitude;
unsigned long fix_age;
unsigned long course;
unsigned long speed;
unsigned long date;
unsigned long t;
unsigned int satellites; 

Thread thready;

void printy(void){
  if (gps.newdata){
      pc.printf("New fix\n\r");
      gps.f_get_position(&latitude, &longitude, &fix_age);
      course = gps.f_course();
      speed = gps.f_speed_knots();
      satellites = gps.satellites();
      pc.printf("lat %f, lon %f, cse %f, spd %f, n %d\n",
		latitude, longitude, course, speed, satellites);
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

  pc.printf("Was it successful (y/n)?\n\r");
  pc.scanf("%c", &c);
  TEST_ASSERT_TRUE_MESSAGE((c == 'y'),"GPS fix test failed\n\r");

}// main() for TESTS/gps/fix






