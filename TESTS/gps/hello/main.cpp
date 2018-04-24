/*
  TESTS/gps/hello/main.cpp
  GPS hello world test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "gps.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
Serial dummygps(PC_2,PC_3,4800); 
char rawstring[83]; 
char c;

int main(void){

  pc.printf("GPS version ");
  pc.printf(GPS_VERSION);
  pc.printf("\n\rGPS hello world test\n\r");
  pc.printf("Just see if we can get GPS sentences back, no parsing.\n\r");
  pc.printf("Be sure antenna is installed\n\r");

  //dummygps.baud(4800);
  //dummygps.format(8,SerialBase::None,1); 

  while(1){
    if (dummygps.readable()){
      pc.putc(dummygps.getc());
    }    
  }
  
  //c = ' ';
  //while ((c!='y') && (c!='n')){
    //dummygps.scanf("%s", rawstring);
    //pc.printf("OK? (y/n): %s\n\r",rawstring);
    //c = pc.getc();
    //Thread::wait(1000); 
  //}
  
  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"GPS hello world test failed\n\r");
}// main() for TESTS/gps/hello
