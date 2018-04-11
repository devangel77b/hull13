/*
  TESTS/mainsail/calibration_check/main.cpp
  Mainsail calibration check
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "mainsail.h"
#include "unity.h"

Serial pc(USBTX, USBRX); 
Rudder mainsail(PA_1);
char c;
float i; 



int main(){

  pc.printf("Mainsail version ");
  pc.printf(MAINSAIL_VERSION);
  pc.printf("\n\rMainsail calibration check\n\r");
  pc.printf("Mainsail should move from -90 to 90 deg in increments of 15 deg\n\r");
  pc.printf("Record actual mainsail positions to see that it is good\n\r");

  for (i=-90.0; i<90.0; i+=15.0){
    mainsail.write(i);
    pc.printf("Mainsail at %2.2f (y/n)?\n\r",i);
    pc.scanf("%c",&c);
    TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Mainsail calibration check failed.\n\r");
  } // for loop

} // main() for TESTS/mainsail/calibration_check









