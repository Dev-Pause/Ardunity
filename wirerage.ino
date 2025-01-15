#include "FastIMU.h"
#include <Wire.h>

#define RATE 10 // Hz
#define LOOP 1000.0 / RATE // ms
uint32_t timer; // ms

#define IMU_ADDRESS 0x68
MPU9255 imu;

calData calib = {0};
AccelData accel;
GyroData gyro;

#define CALIBRATE true

void setup() {
   Wire.begin();
   Wire.setClock(400000);
   Serial.begin(115200);
   while( !Serial );

   int error = imu.init(calib, IMU_ADDRESS);
   if( error != 0 ) {
      Serial.println("Error initializing IMU ):");
      Serial.println(error);
      while( true );
   }

   if( CALIBRATE ) {
      delay(1000);
      Serial.println("Keep IMU level.");
      delay(5000);
      imu.calibrateAccelGyro(&calib);
      Serial.println("Calibration done! (:");
      imu.init(calib, IMU_ADDRESS);
   }
