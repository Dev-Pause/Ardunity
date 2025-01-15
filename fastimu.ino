#include "FastIMU.h"
#include <Wire.h>

#define RATE 10 
#define LOOP 1000.0 / RATE
uint32_t timer; 

#define IMU_ADDRESS 0x68
MPU9255 imu;

calData calib = {0};
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

   timer = millis();
}
void loop() {
   imu.update();
   imu.getGyro(&gyro);   
   Serial.printf("%f, %f, %f\n",
      gyro.gyroX, gyro.gyroY, gyro.gyroZ
   );
}

