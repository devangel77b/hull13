#ifndef NAV_H
#define NAV_H

#include "mbed.h"
#include "rtos.h"
#include "math.h"

#define NAV_VERSION "13.2.0"
#define RAD2DEG 57.2958
#define REARTH 6371.0


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
  float crosstrack_distance(Position position);
};





/*


class GenericBehavior{
public:
  GenericBehavior();
  ~GenericBehavior();
  void callback(void);
  bool is_done(void);
  GenericBehavior nextAction;
};

class HeaveTo: public GenericBehavior{
public:
  HeaveTo(void);
  ~HeaveTo(void);
};

class SailToWaypoint: public GenericBehavior{
public:
  bool starboardTack;
  SailToWaypoint(void);
  ~SailToWaypoint(void);
}

class Gybe: public GenericBehavior{
public:
  bool turningRight;
  Gybe(void);
  ~Gybe(void);
}
*/
#endif
