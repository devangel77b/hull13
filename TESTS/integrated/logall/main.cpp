#include "mbed.h"
#include "rtos.h"
#include "stdio.h"
#include "windbirdie.h"
#include "compass.h"
#include "gps.h"
#include "logger.h"
#include "xbee.h"
#include "unity.h"

Serial pc(USBTX,USBRX);
WindBirdie windBirdie(PC_4);
Compass compass(PB_9,PB_8); 
Gps gps(PC_2, PC_3);

Logger logger(PC_10,PC_11,9600);
XBee telem(PC_12,PD_2,57600);

float longitude;
float latitude;
float course;
float speed;
int year;
byte month;
byte day;
byte hour;
byte minute;
byte second;
byte hundredths; 
unsigned long fix_age;
unsigned long gdate;
unsigned long gtime; 
float hdg; 

int main(){
  pc.printf("Sailbot 13.2.0\n\r");
  pc.printf("Integrated test of GPS and logging\n\r");
  pc.printf("Take a walk!\n\r"); 

  logger.printf("Sailbot 13.2.0\n");
  logger.printf("Integrated test of GPS and logging\n");
  logger.printf("OpenLogger output\n");
  
  telem.printf("Sailbot 13.2.0\n");
  telem.printf("Integrated test of GPS and logging\n");
  telem.printf("Xbee output\n");

  while(1){
    pc.printf("wind birdie: %f %f %f\n\r",windBirdie.raw,windBirdie.deg,windBirdie.rdeg);
    logger.printf("wind birdie: %f %f %f\n",windBirdie.raw,windBirdie.deg,windBirdie.rdeg);
    telem.printf("wind birdie: %f %f %f\n",windBirdie.raw,windBirdie.deg,windBirdie.rdeg);

    hdg = compass.hdg; 
    pc.printf("compass: %f\n\r",hdg);
    logger.printf("compass: %f\n",hdg);
    telem.printf("compass: %f\n",hdg);
    
    
    gps.get_datetime(&gdate, &gtime, &fix_age);
    pc.printf("gps: %d %d ",gdate,gtime);
    logger.printf("gps: %d %d ",gdate,gtime);
    telem.printf("gps: %d %d ",gdate,gtime);

    gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths,&fix_age);
    pc.printf("%d%02d%02d %02d:%02d:%02d.%02d ",year,month,day,hour,minute,second,hundredths);
    logger.printf("%d%02d%02d %02d:%02d:%02d.%02d ",year,month,day,hour,minute,second,hundredths);
    telem.printf("%d%02d%02d %02d:%02d:%02d.%02d ",year,month,day,hour,minute,second,hundredths); 
    
    gps.f_get_position(&latitude, &longitude, &fix_age);
    course = gps.f_course();
    speed = gps.f_speed_knots();
    pc.printf("%f %f C%05.1f S%4.1\n\r",longitude,latitude,course,speed);
    logger.printf("%f %f C%05.1f S%4.1\n",longitude,latitude,course,speed);
    telem.printf("%f %f C%05.1f S%4.1\n",longitude,latitude,course,speed);


  
    
    Thread::wait(1000); 
  }

  
}
