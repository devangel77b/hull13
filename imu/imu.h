#ifndef IMU_H
#define IMU_H

#include "mbed.h"
#include "rtos.h"

#define IMU_VERSION "13.2.0"
#define IMU_UPDATE_PERIOD_MS 20

class Imu{
 private:
  Serial _serial;
  Thread _thread;
  void _update_process(void);

 public:
  float hdg; 
  Imu(PinName pin);
  ~Imu(void);
};

#endif
