/*
  TESTS/windbirdie/calibration_check/main.cpp
  WindBirdie calibration check
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "windbirdie.h"
#include "unity.h"

Serial pc(USBTX, USBRX); 
WindBirdie windBirdie(p19);
char c;
float i; 



int main(void){

  pc.printf("WindBirdie version ");
  pc.printf(WINDBIRDIE_VERSION);
  pc.printf("\n\rWindBirdie calibration check\n\r");
  
  pc.printf("Move WindBirdie from 0 to 360 relative in increments of 10 deg\n\r");
  pc.printf("Record indicated positions to see that it is good\n\r");

  for (i=0; i<360.0; i+=10.0){
    pc.printf("\n\rReading sat at %5.3f deg? (y/n)\n\r",i);
    c = ' ';
    while ((c != 'y') && (c != 'n')){
      pc.printf("%5.1f\r",windBirdie.deg);
      c = pc.getc();
    }
    TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"WindBirdie calibration check failed.\n\r");
  } // for loop

} // main() for TESTS/windbirdie/calibration_check









