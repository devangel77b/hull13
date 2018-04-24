/*
  TESTS/xbee/hello/main.cpp
  Logger hello world test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "xbee.h"
#include "unity.h"

#define XBEEBAUD 9600

Serial pc(USBTX,USBRX);
XBee telem(PC_12,PD_2,XBEEBAUD);
char c;
int i;
float f;

int main(void){

  pc.printf("XBee version ");
  pc.printf(XBEE_VERSION);
  pc.printf("\n\rXBee hello world test\n\r");
  pc.printf("Be sure XBee dongle is connected and operating in TeraTerm %d 8N1\n",XBEEBAUD);

  telem.printf("Hello XBee version\n");
  telem.printf(XBEE_VERSION);
  telem.printf("\nGo Navy, Beat Army\n");
  telem.printf("The following is a test of the telemetry system:\n");
  telem.printf("%d,%d,%d... ",1,2,3);
  telem.printf("%f,%f,%f.\n",3.0,2.0,1.0);
  telem.printf("Test sat.\n");

  pc.printf("Messages received correctly (y/n)? ");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c == 'y'),"XBee hello failed, not transmitting\n\r");

  telem.printf("What is 2+2?\n");
  telem.scanf("%d",&i);
  TEST_ASSERT_EQUAL_MESSAGE(4,i,"XBee hello failed, not receiving or you suck at math\n\r");
  telem.printf("You said %d\n",i);
  telem.printf("What is 19.0 + 0.98?\n");
  telem.scanf("%f",&f);
  TEST_ASSERT_EQUAL_MESSAGE(19.98,f,"XBee hello failed, not receiving or you suck at float math\n\r");
  telem.printf("You said %f\n",f);
  
  pc.printf("Overall, mMssages transmitted and received correctly (y/n)? ");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c == 'y'),"XBee hello failed, overall not transmitting or receiving\n\r");
}// main() for TESTS/logger/hello
