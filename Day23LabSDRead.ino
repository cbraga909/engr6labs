//SD read and write
#include <SD.h>
//Set CS Pin
const int CS_PIN=10;
const int POW_PIN=8;
//Default rate 5 seconds
int refresh_rate=5000;

void setup() {  
  Serial.begin(9600);
  Serial.println("Initializing Card");
  //CS pin is output
  pinMode(CS_PIN,OUTPUT);

  //Card draws power from pin 8, therefore set high
  pinMode(POW_PIN,OUTPUT);
  digitalWrite(POW_PIN,HIGH);

  //Print error message if SD.begin fails
  if(!SD.begin(CS_PIN))
  {
    Serial.println("Card Failure");
    return;
  }
  
  Serial.println("Card Ready");

  //Read configuration information
  File commandFile = SD.open("speed.txt");
  if(commandFile)
  {
    Serial.println("Reading Command File");
    
    while(commandFile.available())
    {
      refresh_rate=commandFile.parseInt();
    }
    Serial.print("Refresh Rate = ");
    Serial.print(refresh_rate);
    Serial.println("ms");
    commandFile.close();
  }
  else
  {
    Serial.println("Could not read command file.");
    return;
  }
}

void loop() {
  long timeStamp=millis();
  String dataString="Hello";

  //Open file and write to it
  File dataFile=SD.open("log.csv",FILE_WRITE);
  if(dataFile)
  {
    dataFile.print(timeStamp);
    dataFile.print(",");
    dataFile.println(dataString);
    dataFile.close(); //Close connection in order to write data

    //Print same info to serial monitor for debugging
    Serial.print(timeStamp);
    Serial.print(",");
    Serial.println(dataString);
  }
  else
  {
    Serial.println("Couldn't open log file");
  }
  delay(refresh_rate);
}
