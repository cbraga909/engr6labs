//Temperature Logger SD Card
#include <SD.h>
#include <Wire.h>
int temp_address=72; //1001000 written as decimal number
const int CS_PIN=10; //Define CS pin
long lastTime=0; //Initialize last time

//Define interrupt buttons
const int decreaseButton=0;
const int increaseButton=1;
volatile int interval=1000; //Initial interval

void setup() {
  Serial.begin(9600);
  Wire.begin(); //Create wire object
  Serial.println("Initializing Card"); 
  pinMode(CS_PIN,OUTPUT); //Set CS pin as output


  //Attach interrupts
  attachInterrupt(decreaseButton,decrease,RISING);
  attachInterrupt(increaseButton,increase,RISING);
  
  if(!SD.begin(CS_PIN)) //Print error message if SD.begin fails
  {
    Serial.println("Card Failure");
    return;
  }
  Serial.println("Card Ready");
}

//Function to decrease interval by 200 milliseconds
void decrease()
{
  if(interval>200 && interval<=10000)
  {
    interval-=200;
  }
  else if(interval<=200)
  {
    interval=200; //Minimum interval is 200 milliseconds
  }
}

//Function to increase interval by 200 milliseconds
void increase()
{
  if(interval<10000 && interval>=200)
  {
    interval+=200;
  }
  else if(interval>=10000)
  {
    interval=10000; //Maximum interval is 10000 milliseconds
  }
}

void loop() {
  //Send request and start talking to device at specified address
  Wire.beginTransmission(temp_address);
  Wire.write(0); //Send bit asking for register zero, the data register
  Wire.endTransmission(); //Complete Transmission
  
  //Read temperature from the device
  //Request 1 byte from specified address
  Wire.requestFrom(temp_address,1);
  //Wait for response
  while(Wire.available() ==0);
  //Get temperature and read it into variable
  int temperature=Wire.read();

  long timeStamp=millis();
  //Find difference between time stamp and the last time
  long timeDiff=timeStamp-lastTime;

  //Continue for 60 seconds, reading after every interval
  if(timeStamp<=60000 && timeDiff>=interval)
  {
    //Open a file and write to it
    File dataFile=SD.open("temps.csv",FILE_WRITE);
    if(dataFile)
    {
      dataFile.print(timeStamp);
      dataFile.print(",");
      dataFile.println(temperature);
      dataFile.close(); //data not written until connection is closed

      //Print information to screen for debugging
      Serial.print(timeStamp);
      Serial.print(",");
      Serial.print(interval);
      Serial.print(",");
      Serial.println(temperature);
      
    }
    else //Print error message if file cannot be opened
    {
      Serial.println("Couldn't open temps file");
    }
    //Reset the last time
    lastTime=timeStamp;
  }

  //Stop reading if time exceeds 60 seconds
  else if(timeStamp>60000)
  {
    return;
  }
}
