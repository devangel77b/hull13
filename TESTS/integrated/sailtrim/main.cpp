#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "mainsail.h"
#include "windbirdie.h"
#include "unity.h"
#include "math.h"

Serial pc(USBTX,USBRX);
Mainsail mainsail(PC_6);
WindBirdie windbirdie(PC_4);

Thread sailtrim_thread;
char c;

void sailtrim_callback(void){
  float deg, rdeg;
  float sailtrim;

  // HACK BECAUSE WINDBIRDIE ZERO IS POINTED TO RIGHT
  deg = fmod(windbirdie.deg-90.0,360.0);
  if (deg<180.0)
    rdeg = deg;
  else
    rdeg = -(360.0-deg);
  
  // starboard tack
  if ((0 <= rdeg) && (rdeg < 90.0)) { sailtrim = 15.0*rdeg/90.0; }
  else if ((90.0 <= rdeg) && (rdeg < 120.0)) { sailtrim = 15.0+rdeg-90.0; }
  else if ((rdeg <= 120.0) && (rdeg < 180.0)) { sailtrim = 45.0; }

  // port tack
  if ((0 >= rdeg) && (rdeg > -90.0)) { sailtrim = 15.0*rdeg/90.0; }
  else if ((-90.0 >= rdeg) && (rdeg > -120.0)) { sailtrim = -(15.0-rdeg-90.0); }
  else if ((rdeg >= -120.0) && (rdeg > -180.0)) { sailtrim = -45.0; }

  pc.printf("Birdie %f deg relative, trimming to %f\n\r",rdeg,sailtrim);
  mainsail.write(sailtrim);
  Thread::wait(100); 
}

int main(){
  pc.printf("Integrated test of sail trimming\n\r");
  
  pc.printf("Starting sail trim thread\n\r");
  sailtrim_thread.start(callback(sailtrim_callback));

  for (int i=60; i>0; i--){
    pc.printf("%d s remaining in test\n\r",i);
    Thread::wait(1000); 
  }

  pc.printf("Stopping sail trim thread\n\r");
  sailtrim_thread.terminate();

  pc.printf("Did it work? (y/n) ");
  pc.scanf("%c", &c);
  TEST_ASSERT_TRUE_MESSAGE((c=='y'),"Integrated sail trim test failed\n\r");
}
