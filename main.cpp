/*
  USNA Sailbot Hull 13, Mod 2
  USNA Department of Weapons & Systems Engineering
*/

#include "mbed.h"
#include "rtos.h"

#include "rudder.h"
#include "mainsail.h"
#include "windbirdie.h"
#include "compass.h"
#include "gps.h"
#include "logger.h"
#include "xbee.h"
#include "nav.h"

#define SAILBOT_VERSION "13.2.0"

// actuators
Rudder rudder(PC_8);       // rudder, Hitec HS5646WP
Mainsail mainsail(PC_6);   // mainsail, Hitec D845WP

// sensors
WindBirdie windBirdie(PC_4); // wind birdie, Honeywell RTY360LVNAX
Compass compass(PB_9, PB_8); // imu/compass, Adafruit BNO055 Absolute (SDA,SCL)
Gps gps(PC_2, PC_3); // gps, Sparkfun Copernicus II (TX,RX)

// comms
Logger logger(PC_10,PC_11,9600); // OpenLogger (PC_10, PC_11)
//XBee telem(PC_12,PD_2); // Xbee module, (PC_12, PD_2)
Serial telem(USBTX,USBRX,9600); // when working with wired connection

// waypoints
Position WP1(-76.47538051521539,38.98428991077217,"WP1");
Position WP2(-76.45824247091318,38.97715200765768,"WP2");
Position WP3(-76.47184839108753,38.97126294386471,"WP3");


int main(void){
  // startup messages
  telem.printf("Welcome to Sailbot version %s\n",SAILBOT_VERSION);
  telem.printf("  Rudder v%s\n",RUDDER_VERSION);
  telem.printf("  Mainsail v%s\n",MAINSAIL_VERSION);
  telem.printf("  Wind birdie v%s\n",WINDBIRDIE_VERSION);
  telem.printf("  Compass v%s\n",COMPASS_VERSION);
  telem.printf("  GPS v%s\n",GPS_VERSION);
  telem.printf("  Logger v%s\n",LOGGER_VERSION);
  telem.printf("  XBee v%s\n",XBEE_VERSION);
  telem.printf("  Nav v%s\n", NAV_VERISON);
  telem.printf("\n");
  
  // verify waypoints
  telem.printf("Waypoints:\n");
  telem.printf("  %s,%f,%f\n",WP1.name,WP1.longitude,WP1.latitude);
  telem.printf("  %s,%f,%f\n",WP2.name,WP2.longitude,WP2.latitude);
  telem.printf("  %s,%f,%f\n",WP3.name,WP3.longitude,WP3.latitude);
  telem.printf("\n");

  // initialize and start all navigation processes
  // WAIT FOR FIX LATER

  // turn to 1
  
  
  // sail to 1

  // turn to 2
  // sail to 2

  // turn to 3
  // sail to 3

  // done
} // main()
