/*
  TESTS/mainsail/range/main.cpp
  Mainsail range of motion check
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "mainsail.h"
#include "unity.h"

Serial pc(USBTX, USBRX);
Mainsail mainsail(PC_6);
char c;



int main(){

  pc.printf("Mainsail version ");
  pc.printf(MAINSAIL_VERSION);
  pc.printf("\n\rMainsail range of motion check\n\r");
  pc.printf("Mainsail should move the full range of motion\n\r");

  mainsail.write(0.0);
  pc.printf("Beam reach (y/n)?\n\r");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Mainsail range test failed.\n\r");
  
  mainsail.write(90.0);
  pc.printf("Close hauled on port tack 90 deg (y/n)?\n\r");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Mainsail range test failed.\n\r");
  
  mainsail.write(-90.0);
  pc.printf("Close hauled on starboard tack -90 deg (y/n)?\n\r");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Mainsail range test failed.\n\r");
  
  mainsail.write(0.0);
  pc.printf("Returned to beam reach (y/n)?\n\r");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c != 'n'),"Mainsail range test failed.\n\r");

} // main() for TESTS/mainsail/range









