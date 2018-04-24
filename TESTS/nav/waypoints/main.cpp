/*
  TESTS/nav/waypoints/main.cpp
  Nav waypoints test checking the objects work right
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "nav.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
Position WP1;
Position WP2(-76.45824247091318,38.97715200765768);
Position WP3(-76.47184839108753,38.97126294386471,"Waypoint 3");
char c;

int main(){
  pc.printf("Nav version ");
  pc.printf(NAV_VERSION);
  pc.printf("\n\rNav waypoints test\n\r");

  WP1.longitude=-76.47538051521539;
  WP1.latitude=38.98428991077217;
  strcpy(WP1.name,"Waypoint 1");
  pc.printf("%f, %f, %s\n\r",WP1.longitude, WP1.latitude, WP1.name);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(WP1.longitude,-76.47538051521539,"Nav waypoint test failed, longitude not assigned\n"); 

  strcpy(WP2.name,"Waypoint 2"); 
  pc.printf("%f, %f, %s\n\r",WP2.longitude, WP2.latitude, WP2.name);
  TEST_ASSERT_EQUAL_FLOAT_MESSAGE(WP2.latitude,38.97715200765768,"Nav waypoint test failed, latitude not assigned\n");

  pc.printf("%f, %f, %s\n\r",WP3.longitude, WP3.latitude, WP3.name);

  pc.printf("Looks ok? (y/n) ");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c=='y'),"Nav waypoint test failed\n");
}
