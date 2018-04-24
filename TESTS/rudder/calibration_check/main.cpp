/*
  TESTS/rudder/range/main.cpp
  Rudder range of motion check
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "rudder.h"
#include "unity.h"

Serial pc(USBTX, USBRX); 
Rudder rudder(PC_8);
char c;
float i; 



int main(){

  pc.printf("Rudder version ");
  pc.printf(RUDDER_VERSION);
  pc.printf("\n\rRudder calibration check\n\r");
  pc.printf("Rudder should move from -45 to 45 deg in increments of 5 deg\n\r");
  pc.printf("Record actual rudder positions to see that it is good\n\r");

  for (i=-45.0; i<45.0; i+=5.0){
    rudder.write(i);
    pc.printf("Rudder at %2.2f (y/n)?\n\r",i);
    pc.scanf("%c",&c);
    TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Rudder calibration check failed.\n\r");
  } // for loop

} // main() for TESTS/rudder/calibration_check









