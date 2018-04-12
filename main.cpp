/*
  USNA Sailbot Hull 13, Mod 2
  USNA Department of Weapons & Systems Engineering
*/

#include "mbed.h"
#include "rtos.h"
#include "rudder.h"
#include "mainsail.h"
#include "windbirdie.h"
#include "imu.h"

// actuators
Rudder rudder(PA_1);       // rudder, Hitec HS5646WP
Mainsail mainsail(PA_2);   // mainsail, Hitec D845WP

// sensors
WindBirdie windBirdie(A0); // wind birdie, Honeywell RTY360LVNAX
// imu/compass, Sparkfun 9dof
// gps, Sparkfun Copernicus II

// comms
// telemetry, ?? (Xbee module)

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
