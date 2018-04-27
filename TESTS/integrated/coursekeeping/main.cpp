#include "mbed.h"
#include "rtos.h"
#include "compass.h"
#include "rudder.h"
#include "nav.h"
#include "stdio.h"
#include "unity.h"

Serial pc(USBTX,USBRX);

Rudder rudder(PC_8); 
Compass compass(PB_8, PB_9);

float r, e, ie, u;
float Kp=0.5;
float Ki=0.5;
int DTus=100; 
Thread hdgcontrol_thread;
int i;
char c;

void hdgcontrol_callback(void){
  float hdg; 
  while(1){
    hdg = compass.hdg; 
    e = turn_to(r, hdg);
    ie = ie + (float) DTus/1000.0 * e;
    u = Kp*e + Ki*ie;
    rudder.write(u);
    pc.printf("ref=%f, err=%f, int_err=%f, u=%f\n",r,e,ie,u); 
    Thread::wait(DTus); 
  }
}



int main(){

  pc.printf("Testing course keeping with rudder and compass\n");

  pc.printf("Turn to 000");
  r = 0.0; ie=0.0;
  hdgcontrol_thread.start(callback(hdgcontrol_callback));
  for (i=30; i>0; i--){
    pc.printf("%d s remaining\n",i);
    Thread::wait(1000);
  }

    pc.printf("Turn to 000");
  r = 0.0; ie=0.0;
  hdgcontrol_thread.start(callback(hdgcontrol_callback));
  for (i=30; i>0; i--){
    pc.printf("%d s remaining\n",i);
    Thread::wait(1000);
  }

  pc.printf("Turn to 090");
  r = 90.0; ie=0.0;
  hdgcontrol_thread.start(callback(hdgcontrol_callback));
  for (i=30; i>0; i--){
    pc.printf("%d s remaining\n",i);
    Thread::wait(1000);
  }

  pc.printf("Turn to 180");
  r = 180.0; ie=0.0;
  hdgcontrol_thread.start(callback(hdgcontrol_callback));
  for (i=30; i>0; i--){
    pc.printf("%d s remaining\n",i);
    Thread::wait(1000);
  }

  pc.printf("Turn to 270");
  r = 270.0; ie=0.0;
  hdgcontrol_thread.start(callback(hdgcontrol_callback));
  for (i=30; i>0; i--){
    pc.printf("%d s remaining\n",i);
    Thread::wait(1000);
  }

  pc.printf("Turn to 018");
  r = 18.0; ie=0.0;
  hdgcontrol_thread.start(callback(hdgcontrol_callback));
  for (i=30; i>0; i--){
    pc.printf("%d s remaining\n",i);
    Thread::wait(1000);
  }


  pc.printf("Test sat? (y/n) ");
  pc.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c=='y'),"Coursekeeping test failed\n");
}
