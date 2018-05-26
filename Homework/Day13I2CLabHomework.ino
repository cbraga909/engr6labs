//Reads Temp from I2C temperature sensor and prints it on the serial port
//Include Wire I2C library
#include <Wire.h>
#include <LiquidCrystal.h>
int temp_address = 72; //1001000 written as decimal number
int btn=A0;
int tempMode=0;
int lastVal=0;

void setup()
{
  //Set up LCD number of column and rows
  lcd.begin(16,2);
  lcd.print("Day 13 Homework");
 //Start serial communication at 9600 baud
 Serial.begin(9600);
 //Create a Wire object
 Wire.begin();
}
void currentMode()
{
  int sensorVal=analogRead(btn);
  if(sensorVal==479 && lastVal!=1)
  {
    tempMode=1;
    lastVal=1;
  }
  if(sensorVal==0 && lastVal!=2)
  {
    tempMode=2;
    lastVal=2;
  }
}

void loop()
{
 //Send a request
 //Start talking to the device at the specified address
 Wire.beginTransmission(temp_address);
 //Send a bit asking for register zero, the data register
 Wire.write(0);
 //Complete Transmission
 Wire.endTransmission();
 //Read the temperature from the device
 //Request 1 Byte from the specified address
 Wire.requestFrom(temp_address, 1);
 //Wait for response
 while(Wire.available() == 0);
 //Get the temp and read it into a variable
 int c = Wire.read();
 //Do some math to convert the Celsius to Fahrenheit
 int f = round(c*9.0/5.0 +32.0);
 //Send the temperature in degrees C and F to the serial monitor
 Serial.print(c);
 Serial.print("C ");
 Serial.print(f);
 Serial.println("F");
 lcd.setCursor(0,1);
 currentMode();
 if(tempMode==1)
 {
  lcd.print(c);
 }
 if(tempMode==2)
 {
  lcd.print(f);
 }
 delay(500);
}

