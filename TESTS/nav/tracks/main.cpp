/*
  TESTS/nav/tracks/main.cpp
  Nav tracks test checking that the objects work right
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "nav.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
Position WP1(-76.47538051521539,38.98428991077217,"WP1");
Position WP2(-76.45824247091318,38.97715200765768,"WP2");
Position WP3(-76.47184839108753,38.97126294386471,"WP3");

Track leg1;
Track leg2(&WP2, &WP3);
Track leg3(&WP3, &WP1, "leg3"); 

char c;

int main(){
  pc.printf("Nav version ");
  pc.printf(NAV_VERSION);
  pc.printf("\n\rNav tracks test\n\r");
  
  leg1.startpoint = &WP1;
  leg1.endpoint = &WP2;
  strcpy(leg1.name,"leg1");
  pc.printf("%s, %s to %s\n\r",leg1.name,leg1.startpoint->name,leg1.endpoint->name);
  
  strcpy(leg2.name,"leg2");
  pc.printf("%s, %s to %s\n\r",leg2.name,leg2.startpoint->name,leg2.endpoint->name);

  pc.printf("%s, %s to %s\n\r",leg3.name,leg3.startpoint->name,leg3.endpoint->name);

  pc.printf("Looks ok? (y/n)\n\r");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c=='y'),"Nav tracks test failed\n");
}
