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
WindBirdie windBirdie(A0);
char c;
float i;
int j; 



int main(void){

  pc.printf("WindBirdie version ");
  pc.printf(WINDBIRDIE_VERSION);
  pc.printf("\n\rWindBirdie calibration\n\r");
  
  for (i=0; i<360.0; i+=10.0){
    pc.printf("Move to %6.3f deg and hit enter\n\r",i);
    pc.scanf("");
    for (j=0; j<10; j++){
      pc.printf("%6.3f,%f\n\r",i,windBirdie.raw);
      Thread::wait(100); 
    } // for loop
  } // for loop

  pc.printf("Calibration routine done\n\r");
  pc.printf("Cut and paste results into Matlab, Excel, etc to get y=mx+b\n\r");

} // main() for TESTS/windbirdie/calibration









