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
Track leg1(&WP1, &WP2, "leg1");
Track leg2(&WP2, &WP3, "leg2");
Track leg3(&WP3, &WP1, "leg3");

void sail_to_point(Position*); 
void sail_track(Track*);

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
  telem.printf("  Nav v%s\n", NAV_VERSION);
  telem.printf("\n");

  logger.printf("Welcome to Sailbot version %s\n",SAILBOT_VERSION);
  logger.printf("  Rudder v%s\n",RUDDER_VERSION);
  logger.printf("  Mainsail v%s\n",MAINSAIL_VERSION);
  logger.printf("  Wind birdie v%s\n",WINDBIRDIE_VERSION);
  logger.printf("  Compass v%s\n",COMPASS_VERSION);
  logger.printf("  GPS v%s\n",GPS_VERSION);
  logger.printf("  Logger v%s\n",LOGGER_VERSION);
  logger.printf("  XBee v%s\n",XBEE_VERSION);
  logger.printf("  Nav v%s\n", NAV_VERSION);
  logger.printf("\n");

  // verify waypoints
  telem.printf("Waypoints:\n");
  telem.printf("  %s,%f,%f\n",WP1.name,WP1.longitude,WP1.latitude);
  telem.printf("  %s,%f,%f\n",WP2.name,WP2.longitude,WP2.latitude);
  telem.printf("  %s,%f,%f\n",WP3.name,WP3.longitude,WP3.latitude);
  telem.printf("\n");

  logger.printf("Waypoints:\n");
  logger.printf("  %s,%f,%f\n",WP1.name,WP1.longitude,WP1.latitude);
  logger.printf("  %s,%f,%f\n",WP2.name,WP2.longitude,WP2.latitude);
  logger.printf("  %s,%f,%f\n",WP3.name,WP3.longitude,WP3.latitude);
  logger.printf("\n");

  // all navigation processes running
  // wait a while logging stuff
  // LATER

  // then go
  sail_to_point(&WP1); // sail to WP1
  sail_track(&leg1); // sail from WP1 to WP2
  sail_track(&leg2); // sail from WP2 to WP3
  sail_track(&leg3); // sail from WP3 to WP1
  
  // done
} // main()




void sail_to_point(Position * dest){
  Position* fix = new Position();
  unsigned long fix_age;
  Track* leg = new Track(); 

  // take a fix
  gps.f_get_position(&(fix->latitude), &(fix->longitude), &fix_age);

  // create a track
  leg->startpoint = fix;
  leg->endpoint = dest;

  // sail_track from initial position to dest
  sail_track(leg); 
}

void sail_track(Track * track){
  Position * fix = new Position();
  unsigned long fix_age;
  unsigned long gdate;
  unsigned long gtime; 
  float course_reqd;
  float turn_reqd;
  float distance;
  int tacking;
  float cte; 

  telem.printf("Heading to %s, %f, %f.\n",
	       track->endpoint->name,
	       track->endpoint->longitude,
	       track->endpoint->latitude);
  logger.printf("Heading to %s, %f, %f.\n",
	       track->endpoint->name,
	       track->endpoint->longitude,
	       track->endpoint->latitude);
  
  // take fix
  gps.f_get_position(&(fix->latitude), &(fix->longitude), &fix_age);
  telem.printf("Currently at to %f, %f.\n",
	       fix->latitude,
	       fix->latitude);
  logger.printf("Currently at to %f, %f.\n",
	       fix->latitude,
	       fix->latitude);
  gps.get_datetime(&gdate, &gtime, &fix_age); 
  logger.printf("date %d time %d\n",gdate,gtime); 
  
  // get course to destination
  distance = fix->distance_to(track->endpoint);
  while (distance > 20.0){
    
    course_reqd = fix->bearing_to(track->endpoint);
    cte = track->crosstrack_distance(fix);
    turn_reqd = turn_to(course_reqd, compass.hdg);
    telem.printf("Mark bears %3.0f at %f m. ",turn_reqd,distance);
    logger.printf("Mark bears %3.0f at %f m. ",turn_reqd,distance); 

    if (turn_reqd > 2.0) // right turn required
      {
	telem.printf("Come right. ");
	logger.printf("Come right. ");
	if (windBirdie.rdeg < 0.0)
	  { // falling off on right turn ok
	    tacking = 0;
	    rudder.right();
	    	// trim the sail 
	if (windBirdie.deg < 45.0) { mainsail.closehaul_stbd(); rudder.right();}
	else if (windBirdie.deg < 60.0) { mainsail.closehaul_stbd();}
	else if (windBirdie.deg < 90.0) { mainsail.closereach_stbd(); }
	else if (windBirdie.deg < 135.0) { mainsail.beamreach_stbd(); }
	else if (windBirdie.deg < 180.0) { mainsail.run(); }
	else if (windBirdie.rdeg > -45.0) { mainsail.closehaul_port(); rudder.left();}
	else if (windBirdie.rdeg > -60.0) { mainsail.closehaul_port(); }
	else if (windBirdie.rdeg > -90.0) { mainsail.closereach_port(); }
	else if (windBirdie.rdeg > -135.0) { mainsail.beamreach_port(); }
	else if (windBirdie.rdeg > -180.0) { mainsail.run(); } 
	  }
	if (windBirdie.rdeg > 45)
	  { // heading up right turn ok
	    telem.printf("Upwinding, starboard tack. ");
	    logger.printf("Upwinding, starboard tack. "); 
	    tacking = 1; // starboard tack
	    rudder.right();
	    mainsail.closehaul_stbd();
	  } // right turn ok
	else if ((tacking == 1) && (cte < 50.0))
	  { // tacking, keep going
	    tacking = 1; 
	    rudder.amidships();
	    mainsail.closehaul_stbd(); 
	  } // keep going
	else
	  {
	    telem.printf("Gybing. ");
	    logger.printf("Gybing. ");
	    tacking = -1; 
	    rudder.left_full();
	    mainsail.beamreach_stbd();
	    Thread::wait(2000);
	  } // chicken gybe
	telem.printf("\n");
	logger.printf("\n");
      }
    
    else if (turn_reqd < -2.0) // left turn required
      {
	telem.printf("Come left. ");
	logger.printf("Come left. ");
	if (windBirdie.rdeg > 0.0)
	  { // falling off on left turn ok
	    tacking = 0;
	    rudder.left();
	    	// trim the sail 
	if (windBirdie.deg < 45.0) { mainsail.closehaul_stbd(); rudder.right();}
	else if (windBirdie.deg < 60.0) { mainsail.closehaul_stbd();}
	else if (windBirdie.deg < 90.0) { mainsail.closereach_stbd(); }
	else if (windBirdie.deg < 135.0) { mainsail.beamreach_stbd(); }
	else if (windBirdie.deg < 180.0) { mainsail.run(); }
	else if (windBirdie.rdeg > -45.0) { mainsail.closehaul_port(); rudder.left();}
	else if (windBirdie.rdeg > -60.0) { mainsail.closehaul_port(); }
	else if (windBirdie.rdeg > -90.0) { mainsail.closereach_port(); }
	else if (windBirdie.rdeg > -135.0) { mainsail.beamreach_port(); }
	else if (windBirdie.rdeg > -180.0) { mainsail.run(); } 
      }
	if (windBirdie.rdeg < -45)
	  { // heading up right turn ok
	    telem.printf("Upwinding, port tack. ");
	    logger.printf("Upwinding, port tack. ");
	    tacking = -1; // port tack
	    rudder.left();
	    mainsail.closehaul_port();
	  } // right turn ok
	else if ((tacking == -1) && (cte < 50.0))
	  { // tacking, keep going
	    tacking = -1; 
	    rudder.amidships();
	    mainsail.closehaul_port(); 
	  } // keep going
	else
	  {
	    telem.printf("Gybing. ");
	    logger.printf("Gybing. "); 
	    tacking = 1; 
	    rudder.right_full();
	    mainsail.beamreach_port();
	    Thread::wait(2000); 
	  } // chicken gybe
	telem.printf("\n");
	logger.printf("\n");
      }
    else
      {
	telem.printf("Steady as she goes.\n");
	logger.printf("Steady as she goes.\n");
	rudder.amidships();
	
	// trim the sail 
	if (windBirdie.deg < 45.0) { mainsail.closehaul_stbd(); rudder.right();}
	else if (windBirdie.deg < 60.0) { mainsail.closehaul_stbd();}
	else if (windBirdie.deg < 90.0) { mainsail.closereach_stbd(); }
	else if (windBirdie.deg < 135.0) { mainsail.beamreach_stbd(); }
	else if (windBirdie.deg < 180.0) { mainsail.run(); }
	else if (windBirdie.rdeg > -45.0) { mainsail.closehaul_port(); rudder.left();}
	else if (windBirdie.rdeg > -60.0) { mainsail.closehaul_port(); }
	else if (windBirdie.rdeg > -90.0) { mainsail.closereach_port(); }
	else if (windBirdie.rdeg > -135.0) { mainsail.beamreach_port(); }
	else if (windBirdie.rdeg > -180.0) { mainsail.run(); } 
      }

    Thread::wait(1000); 
    
      // take fix
    gps.f_get_position(&(fix->latitude), &(fix->longitude), &fix_age);
    telem.printf("Currently at to %f, %f.\n",
		 fix->latitude,
		 fix->latitude);
    logger.printf("Currently at to %f, %f.\n",
		 fix->latitude,
		 fix->latitude);
    gps.get_datetime(&gdate, &gtime, &fix_age); 
    logger.printf("date %d time %d\n",gdate,gtime); 
    
    // get course to destination
    distance = fix->distance_to(track->endpoint);

  }
  telem.printf("Reached %s, %f, %f\n",
	       track->endpoint->name,
	       track->endpoint->longitude,
	       track->endpoint->latitude);
  logger.printf("Reached %s, %f, %f\n",
		track->endpoint->name,
		track->endpoint->longitude,
		track->endpoint->latitude);
  
}

