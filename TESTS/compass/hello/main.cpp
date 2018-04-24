/*
  TESTS/compass/hello/main.cpp
  Compass hello world test
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

int main(void){

  pc.printf("Compass version ");
  pc.printf(COMPASS_VERSION);
  pc.printf("\n\rCompass hello world test\n\r");
  pc.printf("Rotate the hull and see if it works\n\r");

  while(1){
    pc.printf("%5.1f\r",compass.hdg);
    Thread::wait(1000);
  }
  
  /*  for (i=0.0; i<360.0; i=i+10.0){
    pc.printf("\n\rReading sat at %3.0f? (y/n)\nr\r",i);
    c = ' ';
    while((c!='y') && (c!='n')){
      pc.printf("%5.1f\r",compass.hdg);
      c = pc.getc();
      Thread::wait(100);
    } // while
    TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Compass hello world test failed\n\r");
  } // for loop
  */
} // main() for TESTS/compass/hello
