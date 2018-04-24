/*
  TESTS/rudder/range/main.cpp
  Rudder range of motion check
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "rudder.h"
#include "unity.h"

Serial pc(USBTX, USBRX); 
Rudder rudder(PC_8);
char c;



int main(){

  pc.printf("Rudder version ");
  pc.printf(RUDDER_VERSION);
  pc.printf("\n\rRudder range of motion check\n\r");
  pc.printf("Rudder should move the full range of motion\n\r");

  rudder.write(0.0);
  pc.printf("Amidships (y/n)?\n\r");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Rudder range test failed.\n\r");
  
  rudder.write(-45.0);
  pc.printf("Hard right -45 degrees (y/n)?\n\r");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Rudder range test failed.\n\r");
  
  rudder.write(45.0);
  pc.printf("Hard left 45 degrees (y/n)?\n\r");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Rudder range test failed.\n\r");
  
  rudder.write(0.0);
  pc.printf("Returned to amidships (y/n)?\n\r");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Rudder range test failed.\n\r");

} // main() for TESTS/rudder/range









