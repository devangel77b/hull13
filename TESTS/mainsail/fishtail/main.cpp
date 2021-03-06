/*
  TESTS/mainsail/fishtail/main.cpp
  Mainsail fishtail test
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
Thread fishtail_Thread;

void fishtail_callback(){
  while(1){
    mainsail.write(45.0);
    Thread::wait(1000);
    mainsail.write(0.0);
    Thread::wait(1000);
    mainsail.write(-45.0);
    Thread::wait(1000);
    mainsail.write(0.0);
    Thread::wait(1000);
  }
}


int main(){

  pc.printf("Mainsail fishtail movement test\n\r");
  pc.printf("Move mainsail side to side for test\n\r");
  
  fishtail_Thread.start(callback(fishtail_callback));
  
  pc.printf("Was it successful (y/n)?\n\r");
  pc.scanf("%c",&c);

  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Mainsail fishtail test failed.\n\r");

} // main() for TESTS/mainsail/fishtail









