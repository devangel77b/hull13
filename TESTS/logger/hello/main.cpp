/*
  TESTS/logger/hello/main.cpp
  Logger hello world test
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "logger.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
Logger logger(PC_10,PC_11,9600);
char c;

int main(void){

  pc.printf("Logger version ");
  pc.printf(LOGGER_VERSION);
  pc.printf("\n\rLogger hello world test\n\r");

  logger.printf("Hello logger ");
  logger.printf(LOGGER_VERSION);
  logger.printf("\nGo Navy, Beat Army\n");
  logger.printf("The following is a test of the logging system:\n");
  logger.printf("%d,%d,%d... ",1,2,3);
  logger.printf("%f,%f,%f.\n",3,2,1);
  logger.printf("Test sat.");

  pc.printf("Open the log files and verify they were created correctly.\n\r");
  pc.printf("Did it work (y/n)? ");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c == 'y'),"Logger hello world test failed\n\r");
}// main() for TESTS/logger/hello
