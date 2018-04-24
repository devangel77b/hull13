/*
  xbee.h header file
  Dennis Evangelista, 2018

  In USNA Sailbot Hull 13 mod 2 rev D
  XBEETX is PC_12, XBEERX is PD_2 
 */

#ifndef XBEE_H
#define XBEE_H

#include "mbed.h"
#include "rtos.h"

#define XBEE_VERSION "13.2.0"

/**
   For now, the XBee inherits from Serial. 
 */
class XBee:public Serial{
 public:

  /**
     XBee constructor just calls superclass (Serial) constructor
     @param(tx) TX pin for Serial like PC_10
     @param(rx) RX pin for Serial like PC_11
     @param(baud) baud rate like 9600
     @returns Logger object
   */
 XBee(PinName tx, PinName rx, int baud):Serial(tx,rx,baud){
  }
};


#endif
