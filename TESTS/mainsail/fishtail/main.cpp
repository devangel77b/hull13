/*
  TESTS/mainsail/fishtail/main.cpp
  Mainsail fishtail test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "mainsail.h"
#include "unity.h"

Serial pc(USBTX, USBRX); 
Rudder mainsail();
char c;



int main(){

  pc.printf("Mainsail fishtail movement test\n\r");

  // LATER
  
  pc.printf("Was it successful (y/n)?\n\r");
  pc.scanf("%c",&c);

  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Mainsail fishtail test failed.\n\r");

} // main() for TESTS/mainsail/fishtail









