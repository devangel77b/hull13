/*
  USNA Sailbot Hull 13, Mod 2
  USNA Department of Weapons & Systems Engineering
  Pin definitions for Hull 13 mod 2, rev D board
 */

#ifndef HULL13_H
#define HULL13_H

#include "mbed.h"
#include "rtos.h"

#define RUDDER_PWM PC_8
#define MAINSAIL_PWM PC_6

#define WINDBIRDIE_AIN PC_4
#define IMU_SDA PB_9
#define IMU_SCL PB_8
#define GPS_TX PC_2
#define GPS_RX PC_3
#define LOG_TX PC_10
#define LOG_RX PC_11
#define XBEE_TX PC_12
#define XBEE_RX PD_2

#endif
