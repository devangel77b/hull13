#ifndef COMPASS_H
#define COMPASS_H

#include "mbed.h"
#include "rtos.h"

#define COMPASS_VERSION "13.2.0"
#define COMPASS_UPDATE_PERIOD_MS 20

class Compass{
 private:
  Serial _serial;
  Thread _thread;
  void _update_process(void);

 public:
  float hdg; 
  Compass(PinName pin);
  ~Compass(void);
};

#endif
