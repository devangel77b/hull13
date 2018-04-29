/*
  TESTS/integrated/coursekeeping/main.cpp
  Integrated course keeping test of compass and rudder together
  D Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "compass.h"
#include "rudder.h"
#include "nav.h"
#include "stdio.h"
#include "xbee.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
XBee telem(PC_12,PD_2,57600);

Rudder rudder(PC_8); 
Compass compass(PB_9, PB_8);

float r, e, ie, u;
float Kp=0.5;
float Ki=0.5;
int DTms=100; 
Thread hdgcontrol_thread;
int i;
char c;




/**
   This is an example of a callback function used to implement 
   proportional-integral control of heading. Feedback is obtained using
   the compass as the sensor. Kp and Ki are set by the global variables
   (float) Kp and Ki, and the timing of the loop is setby the global 
   (int) DTms. The function itself takes no arguments to make it easy
   to use as a callback by the hdgcontrol_thread. 
 */
void hdgcontrol_callback(void){
  float hdg; 
  while(1){
    hdg = compass.hdg;  // get current heading psc
    e = turn_to(r, hdg); // compute error (wrapping angles correctly)
    
    ie = ie + (float) DTms/1000.0 * e; // update integral
    // pin max integrator value so as not to be ridiculous
    // if this is not done, ie gets huge and it never pulls out of turn
    if (ie > 15.0/Ki)
      { ie = 15.0/Ki; }
    else if (ie < -15.0/Ki)
      { ie = -15.0/Ki;}
    
    u = Kp*e + Ki*ie; // proportional+integral control
    rudder.write(-u); // actually set the rudder angle command to servo

    // reformatted for easier plotting of results like es202 style
    pc.printf("%5.1f, %5.1f, %5.1f, %5.1f\n\r",r,e,ie,u);
    telem.printf("%5.1f, %5.1f, %5.1f, %5.1f\n\r",r,e,ie,u); 
    Thread::wait(DTms); // set timing of control loop execution
  } // while(1)
} // headingcontrol_callback()






int main(){

  pc.printf("Rudder version %s\n\r", RUDDER_VERSION);
  pc.printf("Compass version %s\n\r", GPS_VERSION);
  pc.printf("Integrated test of course keeping with rudder and compass\n\r");
  telem.printf("Integrated test of course keeping with rudder and compass\n\r");

  for (int hh=0.0; hh<=270.0; hh=hh+90.0){
    pc.printf("Helm, steer %03f\n\r",hh);
    pc.printf("ref,err,int_err,u\n\r");
    telem.printf("Helm, steer %03f\nr\r",hh);
    telem.pritnf("ref,err,int_err,u\n\r");
    r = hh; ie=0.0;
    hdgcontrol_thread.start(callback(hdgcontrol_callback));
    for (i=30; i>0; i--){
      //pc.printf("%d s remaining\n",i);
      //telem.printf("%d s remaining\n",i);
      Thread::wait(1000);
    }
  }

  pc.printf("Helm, steer 018\n\r");
  pc.printf("ref,err,int_err,u\n\r");
  telem.printf("Helm, steer 018\nr\r");
  telem.pritnf("ref,err,int_err,u\n\r");
  r = 18.0; ie=0.0;
  hdgcontrol_thread.start(callback(hdgcontrol_callback));
  for (i=30; i>0; i--){
    //pc.printf("%d s remaining\n",i);
    //telem.printf("%d s remaining\n",i);
    Thread::wait(1000);
  }

  pc.printf("Test sat? (y/n) ");
  pc.scanf("%c",&c);
  telem.printf("Test sat? (y/n) ");
  telem.scanf("%c",&c);
  TEST_ASSERT_TRUE_MESSAGE((c=='y'),"Coursekeeping test failed\n");
} // TESTS/integrated/coursekeeping/main
