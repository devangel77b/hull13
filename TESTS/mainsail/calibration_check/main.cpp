/*
  TESTS/mainsail/calibration_check/main.cpp
  Mainsail calibration check
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "mainsail.h"
#include "unity.h"

Serial pc(USBTX, USBRX); 
Mainsail mainsail(PC_6);
char c;
float i; 



int main(){

  pc.printf("Mainsail version ");
  pc.printf(MAINSAIL_VERSION);
  pc.printf("\n\rMainsail calibration check\n\r");
  pc.printf("Mainsail should move from -45 to 45 deg in increments of 5 deg\n\r");
  pc.printf("Record actual mainsail positions to see that it is good\n\r");

  for (i=-45.0; i<=45.0; i+=5.0){
    mainsail.write(i);
    pc.printf("Mainsail at %2.2f (y/n)?\n\r",i);
    pc.scanf("%c",&c);
    TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Mainsail calibration check failed.\n\r");
  } // for loop

} // main() for TESTS/mainsail/calibration_check









