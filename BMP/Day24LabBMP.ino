#include <Wire.h>
#include <SD.h>
//#include<SoftwareSerial.h>
#include "BMP180Lib.c"
#define BMP180_ADDRESS 0x77
const int CS_PIN=10;
const float p0 = 101325; // Pressure at sea level (Pa)
float altitude;
short temperature;
long pressure;
// Use these for altitude conversions
//SoftwareSerial BT(12,13);

void setup()
{
 Serial.begin(9600);
 //BT.begin(115200);
 Wire.begin();
 Serial.println("Initializing Card");
 pinMode(CS_PIN,OUTPUT);
 bmp180Calibration();
// if(!SD.begin(CS_PIN)) //Print error message if SD.begin fails
//  {
//    Serial.println("Card Failure");
//    return;
//  }
//  Serial.println("Card Ready");
}
// Stores all of the bmp180's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
char bmp180Read(unsigned char address)
{
 unsigned char data;
 Wire.beginTransmission(BMP180_ADDRESS);
 Wire.write(address);
 Wire.endTransmission();
 Wire.requestFrom(BMP180_ADDRESS, 1);
 while(!Wire.available());
 return Wire.read();
}
// Read 2 bytes from the BMP180
// First byte will be from 'address'
// Second byte will be from 'address'+1
int bmp180ReadInt(unsigned char address)
{
 unsigned char msb, lsb;
 Wire.beginTransmission(BMP180_ADDRESS);
 Wire.write(address);
 Wire.endTransmission();

 Wire.requestFrom(BMP180_ADDRESS, 2);
 while(Wire.available()<2)
 ;
 msb = Wire.read();
 lsb = Wire.read();

 return (int) msb<<8 | lsb;
}
void bmp180Calibration()
{
 ac1 = bmp180ReadInt(0xAA);
 ac2 = bmp180ReadInt(0xAC);
 ac3 = bmp180ReadInt(0xAE);
 ac4 = bmp180ReadInt(0xB0);
 ac5 = bmp180ReadInt(0xB2);
 ac6 = bmp180ReadInt(0xB4);
 b1 = bmp180ReadInt(0xB6);
 b2 = bmp180ReadInt(0xB8);
 mb = bmp180ReadInt(0xBA);
 mc = bmp180ReadInt(0xBC);
 md = bmp180ReadInt(0xBE);
}
// Read the uncompensated temperature value
unsigned int bmp180ReadUT()
{
 unsigned int ut;
 // Write 0x2E into Register 0xF4
 // This requests a temperature reading
 Wire.beginTransmission(BMP180_ADDRESS);
 Wire.write(0xF4);
 Wire.write(0x2E);
 Wire.endTransmission();
 // Wait at least 4.5ms
 delay(5);
 // Read two bytes from registers 0xF6 and 0xF7
 ut = bmp180ReadInt(0xF6);
 return ut;
}
// Read the uncompensated pressure value
unsigned long bmp180ReadUP()
{
 unsigned char msb, lsb, xlsb;
 unsigned long up = 0;
 // Write 0x34+(OSS<<6) into register 0xF4
 // Request a pressure reading w/ oversampling setting
 Wire.beginTransmission(BMP180_ADDRESS);
 Wire.write(0xF4);
 Wire.write(0x34 + (OSS<<6));
 Wire.endTransmission();
 // Wait for conversion, delay time dependent on OSS
 delay(2 + (3<<OSS));
 // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
 Wire.beginTransmission(BMP180_ADDRESS);
 Wire.write(0xF6);
 Wire.endTransmission();
 Wire.requestFrom(BMP180_ADDRESS, 3);
 // Wait for data to become available
 while(Wire.available() < 3)
 ;
 msb = Wire.read();
 lsb = Wire.read();
 xlsb = Wire.read();
 up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
 return up;
}

void loop()
{
 temperature = bmp180GetTemperature(bmp180ReadUT());
 pressure = bmp180GetPressure(bmp180ReadUP());
 altitude = (float)44330 * (1 - pow(((float) pressure/p0), 0.190295));
 File dataFile=SD.open("BMP.csv",FILE_WRITE);
// if(dataFile)
// {
//  dataFile.print(millis());
//  dataFile.print(",");
//  dataFile.print(altitude);
//  dataFile.print(",");
//  dataFile.print(temperature);
//  dataFile.print(",");
//  dataFile.println(pressure);
//  dataFile.close();

  
  //Serial.print("Altitude: ");
   Serial.print(altitude, 2);
   Serial.print(",");
   //Serial.println(" m");
  
   //Serial.print("Temperature: ");
   Serial.print(temperature, DEC);
   Serial.print(",");
   //Serial.println(" *0.1 deg C");
   //Serial.print("Pressure: ");
   Serial.print(pressure, DEC);
   //Serial.println(" Pa");
   Serial.println();
// }
// else
// {
//  Serial.println("Couldn't open file");
// }
 


//BT.print("Altitude: ");
// BT.print(altitude, 2);
// BT.println(" m");
//
// BT.print("Temperature: ");
// BT.print(temperature, DEC);
// BT.println(" *0.1 deg C");
// BT.print("Pressure: ");
// BT.print(pressure, DEC);
// BT.println(" Pa");
// BT.println();
 delay(100);
}
