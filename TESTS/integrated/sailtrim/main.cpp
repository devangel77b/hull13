/*
  TESTS/integrated/sailtrim/main.cpp
  Integrated sail trimming test of wind birdie and mainsail together
  Dennis Evangelista, 2018
*/

#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "xbee.h"
#include "mainsail.h"
#include "windbirdie.h"
#include "unity.h"
#include "math.h"

Serial pc(USBTX,USBRX);
XBee telem(PC_12,PD_2,57600); 
Mainsail mainsail(PC_6);
WindBirdie windbirdie(PC_4);

Thread sailtrim_thread; // thread for running sail trim in
char c;

/**
   Here's an example of a callback function used to run logic control
   for sail trimming within a thread. This function uses calls to the
   global windbirdie and mainsail objects and performs a crude version
   of logic control to implement a lookup table to select the correct
   point of sail based on where the wind is relative to the sailbot. 
   The values here are a hack not based on actual sailing data, and 
   may be limited by the +/-45 degree range of the current mainsail servo
   Hitec D845WP installed in Hull 13 mod 2. These are also wierd because
   the windbirdie zero point is pointed to the right. 
 */
void sailtrim_callback(void){
  float deg, rdeg;
  float sailtrim;

  while(1){
    // HACK BECAUSE WINDBIRDIE ZERO IS POINTED TO RIGHT
    deg = fmod(windbirdie.deg+90.0,360.0);
    if (deg<180.0)
      rdeg = deg;
    else
      rdeg = -(360.0-deg);
  
    // starboard tack
    if ((0 <= rdeg) && (rdeg < 90.0)) { sailtrim = 15.0*rdeg/90.0; }
    else if ((90.0 <= rdeg) && (rdeg < 120.0)) { sailtrim = 15.0+rdeg-90.0; }
    else if ((rdeg <= 120.0) && (rdeg < 180.0)) { sailtrim = -45.0; }
    
    // port tack
    if ((0 >= rdeg) && (rdeg > -90.0)) { sailtrim = 15.0*rdeg/90.0; }
    else if ((-90.0 >= rdeg) && (rdeg > -120.0))
      { sailtrim = -(15.0-rdeg-90.0); }
    else if ((rdeg >= -120.0) && (rdeg > -180.0))
      { sailtrim = 45.0; }

    pc.printf("%5.1f, %5.1f\n\r",rdeg,sailtrim);
    telem.printf("%5.1f, %5.1f\n\r",rdeg,sailtrim);
    mainsail.write(sailtrim);
    Thread::wait(100);
  } // while(1)
} // sailtrim_callback




int main(){

  pc.printf("Mainsail version %s\n\r",MAINSAIL_VERSION);
  pc.printf("Windbirdie version %s\n\r",WINDBIRDIE_VERSION);
  pc.printf("Integrated test of sail trimming\n\r");
  pc.printf("Starting sail trim thread\n\r");
  pc.printf("wind_rel, sailtrim\n\r");
  
  telem.printf("Mainsail version %s\n\r",MAINSAIL_VERSION);
  telem.printf("Windbirdie version %s\n\r",WINDBIRDIE_VERSION);
  telem.printf("Integrated test of sail trimming\n\r");
  telem.printf("Starting sail trim thread\n\r");
  telem.printf("wind_rel, sailtrim\n\r");
  
  sailtrim_thread.start(callback(sailtrim_callback));

  for (int i=180; i>0; i--){
    //pc.printf("%d s remaining in test\n\r",i);
    //telem.printf("%d s remaining in test\n\r",i);
    Thread::wait(1000); 
  }

  pc.printf("Stopping sail trim thread\n\r");
  telem.printf("Stopping sail trim thread\n\r");
  sailtrim_thread.terminate();
  pc.printf("Cut and paste results for plotting in Matlab etc\n\r");
  telem.printf("Cut and paste results for plotting in Matlab etc\n\r");
  
  pc.printf("Did it work? (y/n) ");
  pc.scanf("%c", &c);
  telem.printf("Did it work? (y/n) ");
  telem.scanf("%c", &c);
  TEST_ASSERT_TRUE_MESSAGE((c=='y'),"Integrated sail trim test failed\n\r");
}
