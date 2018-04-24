/*
  TESTS/compass/calibration/main.cpp
  Compass calibration test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "compass.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
Compass compass(PB_9, PB_8);
char c;
float hdg;
float i;
int j; 

int main(void){

  pc.printf("Compass version ");
  pc.printf(COMPASS_VERSION);
  pc.printf("\n\rCompass calibration\n\r");
  pc.printf("Rotate the hull and record readings\n\r");
  pc.printf("Use another compass to check\n\r");

  for (i=0.0; i<=360.0; i=i+10.0){
    for (j=0; j<100; j++){
      pc.printf("\r%5.1f", compass.hdg);
      Thread::wait(100);
    }
    pc.printf(". Readings looked OK at %3.0f? (y/n)\n\r",i);
    pc.scanf("%c",&c);
    TEST_ASSERT_TRUE_MESSAGE((c == 'y'),"Compass hello world test failed\n\r");
  }
} // main() for TESTS/compass/calibration
