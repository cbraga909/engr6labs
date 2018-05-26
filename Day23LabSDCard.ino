//Write to SD Card
//Note to self: Connect VCC to 5V, not 3.3V
#include <SD.h>
//The following variables are set by default for the SD card library
//MOSI: pin 11
//MISO: pin 12
//SCLK: pin 13

//However, we need to set the CS pin
const int CS_PIN = 10;
 
void setup() {
  Serial.begin(9600);
  Serial.println("Initializing Card");
  //CS pin is an output
  pinMode(10, OUTPUT);
  if(!SD.begin(CS_PIN)) //If SD.begin fails, return error message and end
  {
    Serial.println("Card Failure");
    return;
  }
  Serial.println("Card Ready"); //Otherwise, execute program
}

void loop() {
  long timeStamp=millis();
  String dataString="Hello";

  //Open a file and write to it
  File dataFile=SD.open("log.csv",FILE_WRITE);
  if(dataFile)
  {
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.println(dataString);
    dataFile.close(); //data not written until connection is closed
    Serial.print(timeStamp);
    Serial.print(",");
    Serial.println(dataString);
  }
  else
  {
    Serial.println("Couldn't open log file");
  }
  delay(5000);
}
