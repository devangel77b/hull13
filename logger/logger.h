/*
  logger.h header file
  Dennis Evangelista, 2018

  In USNA Sailbot Hull 13 mod 2 rev D
  LOGTX is PC_10, LOGRX is PC_11 
 */

#ifndef LOGGER_H
#define LOGGER_H

#include "mbed.h"
#include "rtos.h"

#define LOGGER_VERSION "13.2.0"

/**
   For now, the Logger inherits from Serial. 
   TODO in the future maybe make it to expose some of the OpenLog 
   command modes, for example, sending 26 26 26 to then be able to alter
   the filenames, etc. 
   TODO in future add fancy processes or callbacks to log specific things
   TODO in future add Python style logging.info, logging.debug, logging.error
 */
class Logger:public Serial{
 public:

  /**
     Logger constructor just calls superclass (Serial) constructor
     @param(tx) TX pin for Serial like PC_10
     @param(rx) RX pin for Serial like PC_11
     @param(baud) baud rate like 9600
     @returns Logger object
   */
 Logger(PinName tx, PinName rx, int baud):Serial(tx,rx,baud){
  }
};


#endif
