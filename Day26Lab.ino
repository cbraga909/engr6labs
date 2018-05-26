#include <MPU9250.h>
#include <quaternionFilters.h>

#include "MPU9250.h"
MPU9250 myIMU;
void setup()
{
 Wire.begin();
 Serial.begin(38400);
 myIMU.MPU9250SelfTest(myIMU.SelfTest); // Start by performing self test and reporting values
 myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias); // Calibrate gyro and accelerometers, load biases in bias registers
 myIMU.initMPU9250(); // Initialize device for active mode read of acclerometer, gyroscope, and temperature
 myIMU.initAK8963(myIMU.magCalibration); // Initialize device for active mode read of magnetometer
}
void loop()
{
 if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
 {
 myIMU.readAccelData(myIMU.accelCount); // Read the x/y/z adc values
 myIMU.getAres();
 // Now we'll calculate the accleration value into actual g's
 // This depends on scale being set
 myIMU.ax = (float)myIMU.accelCount[0]*myIMU.aRes; // - accelBias[0];
 myIMU.ay = (float)myIMU.accelCount[1]*myIMU.aRes; // - accelBias[1];
 myIMU.az = (float)myIMU.accelCount[2]*myIMU.aRes; // - accelBias[2];
 myIMU.readGyroData(myIMU.gyroCount); // Read the x/y/z adc values
 myIMU.getGres();
 // Calculate the gyro value into actual degrees per second
 // This depends on scale being set
 myIMU.gx = (float)myIMU.gyroCount[0]*myIMU.gRes;
 myIMU.gy = (float)myIMU.gyroCount[1]*myIMU.gRes;
 myIMU.gz = (float)myIMU.gyroCount[2]*myIMU.gRes;
 myIMU.readMagData(myIMU.magCount); // Read the x/y/z adc values
 myIMU.getMres();
 myIMU.magbias[0] = +470.;
 // User environmental x-axis correction in milliGauss TODO axis??
 myIMU.magbias[1] = +120.;
 // User environmental x-axis correction in milliGauss
 myIMU.magbias[2] = +125.;
 myIMU.mx = (float)myIMU.magCount[0]*myIMU.mRes*myIMU.magCalibration[0] -
 myIMU.magbias[0];
 myIMU.my = (float)myIMU.magCount[1]*myIMU.mRes*myIMU.magCalibration[1] -
 myIMU.magbias[1];
 myIMU.mz = (float)myIMU.magCount[2]*myIMU.mRes*myIMU.magCalibration[2] -
 myIMU.magbias[2];
 } // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
 // Must be called before updating quaternions!
 myIMU.updateTime();
 myIMU.delt_t = millis() - myIMU.count;
 if (myIMU.delt_t > 500)
 {
 // Print acceleration values in milligs!
 Serial.print("X-acceleration: "); Serial.print(1000*myIMU.ax);
 Serial.print(" mg ");
 Serial.print("Y-acceleration: "); Serial.print(1000*myIMU.ay);
 Serial.print(" mg ");
 Serial.print("Z-acceleration: "); Serial.print(1000*myIMU.az);
 Serial.println(" mg ");
 // Print gyro values in degree/sec
 Serial.print("X-gyro rate: "); Serial.print(myIMU.gx, 3);
 Serial.print(" degrees/sec ");
 Serial.print("Y-gyro rate: "); Serial.print(myIMU.gy, 3);
 Serial.print(" degrees/sec ");
 Serial.print("Z-gyro rate: "); Serial.print(myIMU.gz, 3);
 Serial.println(" degrees/sec");
 // Print mag values in degree/sec
 Serial.print("X-mag field: "); Serial.print(myIMU.mx);
 Serial.print(" mG ");
 Serial.print("Y-mag field: "); Serial.print(myIMU.my);
 Serial.print(" mG ");
 Serial.print("Z-mag field: "); Serial.print(myIMU.mz);
 Serial.println(" mG");
 myIMU.tempCount = myIMU.readTempData(); // Read the adc values
 // Temperature in degrees Centigrade
 myIMU.temperature = ((float) myIMU.tempCount) / 333.87 + 21.0;
 // Print temperature in degrees Centigrade
 Serial.print("Temperature is "); Serial.print(myIMU.temperature, 1);
 Serial.println(" degrees C");
 myIMU.count = millis();
 }
}

