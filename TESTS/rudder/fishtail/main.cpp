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
Rudder rudder();
char c;



int main(){

  pc.printf("Rudder fishtail movement test\n\r");

  // LATER
  
  pc.printf("Was it successful (y/n)?\n\r");
  pc.scanf("%c",&c);

  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Rudder fishtail test failed.\n\r");

} // main() for TESTS/rudder/fishtail









