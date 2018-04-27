#include "mbed.h"
#include "rtos.h"
#include "math.h"
#include "nav.h"



Position::Position(){
  debug("Position() constructor called.\n");
  Position::longitude=0.0;
  Position::latitude=0.0;
  strcpy(Position::name,"unnamed waypoint");
}

Position::Position(float lon, float lat):longitude(lon),latitude(lat){
  debug("Position(lon,lat) constructor called.\n");
  strcpy(Position::name,"unnamed waypoint");
}

Position::Position(float lon, float lat, char * name):longitude(lon),latitude(lat){
  debug("Position(lon, lat, name) constructor called.\n");
  strcpy(Position::name,name);
}

Position::Position(float lon, float lat, const char * name):longitude(lon),latitude(lat){
  debug("Position(lon, lat, string-literal-name) constructor called.\n");
  strcpy(Position::name,name);
}


Position::~Position(void){
  debug("Position destructor called.\n");
}




/**
   @param(other) is the other point
   see [http://www.movable-type.co.uk/scripts/latlong.html]
 */
float Position::bearing_to(Position * other){
  float lat1,lat2,lon1,lon2,x,y;
  
  lat1 = Position::latitude/RAD2DEG;
  lat2 = other->latitude/RAD2DEG;
  lon1 = Position::longitude/RAD2DEG;
  lon2 = other->longitude/RAD2DEG;
  y = sin(lon2-lon1)*cos(lat2);
  x = cos(lat1)*sin(lat1)-sin(lat1)*cos(lat2)*cos(lon2-lon1);
  return atan2(y,x)*RAD2DEG;
}

/**
   @param(other) is the other point
   see [http://www.movable-type.co.uk/scripts/latlong.html]
 */
float Position::distance_to(Position *other){
  float phi1,phi2,dphi,dlam,a,c;

  phi1 = Position::latitude/RAD2DEG;
  phi2 = other->latitude/RAD2DEG;
  dphi = phi2-phi1;
  dlam = (other->longitude - Position::longitude)/RAD2DEG;

  a = sin(dphi/2.0)*sin(dphi/2.0)+cos(phi1)*cos(phi2)*sin(dlam/2.0)*sin(dlam/2.0);
  c = 2.0*atan2(sqrt(a),sqrt(1-a));
  return REARTH*c;
}





Track::Track(void){
  debug("Track() constructor called.\n");
  Track::startpoint = new Position;
  Track::endpoint = new Position;
  strcpy(Track::name, "unnamed track");
}

Track::Track(Position *startpoint, Position *endpoint):startpoint(startpoint),endpoint(endpoint){
  debug("Track(&startpoint,&endpoint) constructor called.\n");
  strcpy(Track::name, "unnamed track");
}

Track::Track(Position * startpoint, Position * endpoint, char * name):startpoint(startpoint),endpoint(endpoint){
  debug("Track(&startpoint,&endpoint, name) constructor called.\n");
  strcpy(Track::name, name);
}

Track::Track(Position * startpoint, Position * endpoint, const char * name):startpoint(startpoint),endpoint(endpoint){
  debug("Track(&startpoint,&endpoint, string-literal-name) constructor called.\n");
  strcpy(Track::name, name);
}

Track::~Track(void){
  debug("~Track() destructor called.\n");
}

/**
   @param(other) is the other point
   see [http://www.movable-type.co.uk/scripts/latlong.html]
 */
float Track::crosstrack_distance(Position * other){
  float delta13, theta13, theta12;

  delta13 = Track::startpoint->distance_to(other)/REARTH;
  theta13 = Track::startpoint->bearing_to(other)/RAD2DEG;
  theta12 = Track::startpoint->bearing_to(Track::endpoint)/RAD2DEG;
  
  return asin(sin(delta13)*sin(theta13-theta12))*REARTH;
}

/**
   gives signed difference bearing-heading, in degrees
   see [https://stackoverflow.com/questions/16180595/find-the-angle-between-two-bearings]
   @param(to_brg), float bearing 0 to 360 true
   @param(from_hdg), float heading 0 to 360 true
   @returns float, signed -180.0 to 180.0 in degrees relative
   negative is left
 */
float turn_to(float to_brg, float from_hdg){
  return fmodf(fmodf(to_brg-from_hdg,360.0)+540.0,360.0)-180.0; 
}
