//Servo Potentiometer Control
#include <Servo.h>
const int SERVO=9; //Servo on Pin 9
const int pir=2; //pir on pin 2
Servo myServo;
int val = 0; //for storing the reading from the POT

void setup()
  {
   myServo.attach(SERVO);
   myServo.write(90);
  }

void loop()
  {
   val = digitalRead(pir); //Read pir
   if(val==HIGH)
   {
    myServo.write(0);
    delay(2000);
    myServo.write(90);
   }
   
   delay(15); //waits for the servo
  }

