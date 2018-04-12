void Imu::_update_process(void){
  while(1){
    // if there's serial data read and parse it to update heading
    // non blocking wait otherwise
    thread::wait(IMU_UPDATE_PERIOD_MS);
  } // while(1)
} // Imu::_update_process()

Imu::Imu(PinName tx, PinName rx):_serial(tx,rx){
  debug("Imu constructor called\n");
  // set _imu baudrate and serial port parameters
  // initialize compass readings
  // flush buffer
  // start imu process
} // Imu::Imu constructor

Imu::~Imu(){
  debug("Imu destructor called\n");
}
