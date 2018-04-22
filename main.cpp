/*
  USNA Sailbot Hull 13, Mod 2
  USNA Department of Weapons & Systems Engineering
*/

#include "mbed.h"
#include "rtos.h"

#include "hull13.h"
#include "rudder.h"
#include "mainsail.h"
#include "windbirdie.h"
#include "compass.h"

// actuators
Rudder rudder(RUDDER_PWM);       // rudder, Hitec HS5646WP
Mainsail mainsail(MAINSAIL_PWM);   // mainsail, Hitec D845WP

// sensors
WindBirdie windBirdie(WINDBIRDIE_AIN); // wind birdie, Honeywell RTY360LVNAX
// imu/compass, Sparkfun 9dof (SDA PB_9, SCL PB_8) 
// gps, Sparkfun Copernicus II (PC_2, PC_3)

// comms
// OpenLogger (PC_10, PC_11)
// telemetry, ?? (Xbee module, PC_12, PD_2)

// navigational processes
// wind estimator
// ship state observer
// waypoint planner
// minor loop stuff to get to track
// in irons detection

// low level navigation primitives
// steer steady course and trim as needed
// steer full and by
// tack
// gybe




int main(void){
  // startup
  // load waypoints
  // load estimated position
  // initialize and start all navigation processes
  
  // main loop
  // keep navigating
} // main()
