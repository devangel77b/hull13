#ifndef NAV_H
#define NAV_H

#include "mbed.h"
#include "rtos.h"
#include "math.h"

#define NAV_VERSION "13.2.0"
#define RAD2DEG 57.2958
#define REARTH 6371.0e3


class Position{
public:
  float longitude; 
  float latitude;
  char *name; 

  Position(void);
  Position(float longitude, float latitude);
  Position(float longitude, float latitude, char * name);
  Position(float longitude, float latitude, const char * name); 
  ~Position(void);
  float bearing_to(Position * other);
  float distance_to(Position * other);
};


class Track{
public:
  Position *startpoint;
  Position *endpoint;
  char *name;

  Track(void);
  Track(Position *startpoint, Position *endpoint);
  Track(Position *startpoint, Position *endpoint, char *name);
  Track(Position *startpoint, Position *endpoint, const char *name); 
  ~Track(void);
  float crosstrack_distance(Position *position);
};

float turn_to(float to_brg, float from_hdg);

#endif
