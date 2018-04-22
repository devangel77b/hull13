/*
  TESTS/rudder/fishtail/main.cpp
  Rudder fishtail test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "rudder.h"
#include "unity.h"

Serial pc(USBTX, USBRX); 
Rudder rudder(PC_8);
char c;
Thread fishtail_Thread;

void fishtail_callback(void){
  while(1){
    rudder = 1.0; // right full rudder
    Thread::wait(1000);
    rudder = 0.0; // amidships
    Thread::wait(1000);
    rudder = -1.0; // left full rudder
    Thread::wait(1000);
    rudder = 0.0; // amidships
    Thread::wait(1000);
  }
}

int main(){

  pc.printf("Rudder fishtail movement test\n\r");
  pc.printf("Practice doing jam recovery maneuver\n\r");

  fishtail_Thread.start(callback(fishtail_callback));
  
  pc.printf("Was it successful (y/n)?\n\r");
  pc.scanf("%c",&c);

  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Rudder fishtail test failed.\n\r");

} // main() for TESTS/rudder/fishtail









