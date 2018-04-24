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

// actuators
Rudder rudder(PC_8);       // rudder, Hitec HS5646WP
Mainsail mainsail(PC_6);   // mainsail, Hitec D845WP

// sensors
WindBirdie windBirdie(PC_4); // wind birdie, Honeywell RTY360LVNAX
Compass compass(PB_9, PB_8); // imu/compass, Adafruit BNO055 Absolute (SDA,SCL)
Gps gps(PC_2, PC_3); // gps, Sparkfun Copernicus II (TX,RX)

// comms
Logger logger(PC_10,PC_11); // OpenLogger (PC_10, PC_11)
XBee telem(PC_12,PD_2); // Xbee module, (PC_12, PD_2)

// navigational processes
// wind estimator
// ship state observer LATER
// waypoint planner LATER
// minor loop stuff to get to track LATER
// in irons detection

// low level navigation primitives
// steer towards a waypoint
// steer steady course and trim as needed LATER
// steer full and by LATER
// tack LATER
// gybe




int main(void){
  // startup
  // load waypoints
  // load estimated position
  // initialize and start all navigation processes
  
  // main loop
  // keep navigating
} // main()
