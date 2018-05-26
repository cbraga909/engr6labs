//Motor control code for Vishnay board

const int EN=A0; // Enable 
const int MC1=7; //Motor Control 1 
const int MC2=8; //Motor Control 2 
const int POT=1; //POT on Analog Pin 1 
const int PWM = 5; //PMW on pin 5 
int val = 0; //for storing the reading from the POT 
int previousval=0;
int velocity; //For storing the desired velocity (from 0-255) 
void setup() 
{ 
  pinMode(EN, OUTPUT); 
  pinMode(MC1, OUTPUT); 
  pinMode(MC2, OUTPUT); 
  pinMode(PWM, OUTPUT); 
  brake(); //Initialize with motor stopped 
  velocity=100;
  Serial.begin(9600);
  Serial.println("Begin Motor Control");
  Serial.println("Enter number for control option:");
  Serial.println("1. Stop");
  Serial.println("2. Forward");
  Serial.println("3. Reverse");
  //Serial.println("4. Read Current");
  Serial.println("4 Increase Speed");
  Serial.println("5. Decrease Speed");
} 
void loop() 
{ 
  val = Serial.read();

  if (val=='1') 
  { 
    brake(); 
    previousval='1';
  } 

  else if (val=='2') 
  { 
  forward(velocity); 
  previousval='2';
  } 
  
  else if (val=='3')
  { 
  reverse(velocity);
  previousval='3';
  } 

  else if(val=='4')
  {
    velocity+=20;
    if(velocity<=255)
    {
       if(previousval=='2')
      {
        forward(velocity);
      }
      else if(previousval=='3')
      {
        reverse(velocity);
      }
    }
    else if(velocity>255)
    {
      velocity=255;
    }
    
    
  }

  else if(val=='5')
  {
    velocity-=20;
    if(previousval=='2')
    {
      forward(velocity);
    }
    else if(previousval=='3')
    {
      reverse(velocity);
    }
  }

//  else 
//  {
//    Serial.print("Enter valid motor control value");
//  }
} 
//Motor goes forward at given rate (from 0-255) 
void forward (int rate) 
{ 
digitalWrite(EN, LOW); 
digitalWrite(MC1, HIGH); 
digitalWrite(MC2, LOW); 
analogWrite(PWM, rate); 
digitalWrite(EN, HIGH); 

} 
//Motor goes backward at given rate (from 0-255) 
void reverse (int rate) 
{ 
digitalWrite(EN, LOW); 
digitalWrite(MC1, LOW); 
digitalWrite(MC2, HIGH); 
analogWrite(PWM, rate); 
digitalWrite(EN, HIGH); 

} 
//Stops motor 
void brake () 
{ 
digitalWrite(EN, LOW); 
digitalWrite(MC1, LOW); 
digitalWrite(MC2, LOW); 
analogWrite(PWM, 0); 
digitalWrite(EN, HIGH); 
}
