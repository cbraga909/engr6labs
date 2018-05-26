const int red=11;
const int green=10;
const int blue=9;
const int button1=4;
const int button2=3;
const int button3=2;
boolean lastbutton1=LOW;
boolean currentbutton1=LOW;
boolean lastbutton2=LOW;
boolean currentbutton2=LOW;
boolean lastbutton3=LOW;
boolean currentbutton3=LOW;
int mode1=1;
int mode2=1;
int mode3=1;
void setup() {
  // put your setup code here, to run once:
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  digitalWrite(red,LOW);
  digitalWrite(green,LOW);
  digitalWrite(blue,LOW);
}
boolean debounce1(boolean last)
{
  boolean current=digitalRead(button1);
  if(last!=current)
  {
    delay(5);
    current=digitalRead(button1);
  }
  return current;
}

boolean debounce2(boolean last)
{
  boolean current=digitalRead(button2);
  if(last!=current)
  {
    delay(5);
    current=digitalRead(button2);
  }
  return current;
}

boolean debounce3(boolean last)
{
  boolean current=digitalRead(button3);
  if(last!=current)
  {
    delay(5);
    current=digitalRead(button3);
  }
  return current;
}
void loop() {
  // put your main code here, to run repeatedly:
  
  currentbutton1=debounce1(lastbutton1);
  if(lastbutton1==LOW && currentbutton1==HIGH)
  {
    mode1++;
  }
  lastbutton1=currentbutton1;
  if(mode1==8)
  {
    mode1=1;
  }
  switch(mode1)
  {
    case 1: //off
      digitalWrite(red,LOW);
    break;

    case 2: //low
      analogWrite(red,40);
    break;

    case 3:
      analogWrite(red,85);
    break;

    case 4: 
      analogWrite(red,127);
    break;

    case 5:
      analogWrite(red,170);
    break;

    case 6:
      analogWrite(red,230);
    break;

    case 7:
      analogWrite(red,255);
    break;
  }
  
  currentbutton2=debounce2(lastbutton2);
  if(lastbutton2==LOW && currentbutton2==HIGH)
  {
    mode2++;
  }
  lastbutton2=currentbutton2;
  if(mode2==8)
  {
    mode2=1;
  }
  
  switch(mode2)
  {
    case 1: //off
      digitalWrite(green,LOW);
    break;

    case 2: //low
      analogWrite(green,40);
    break;

    case 3:
      analogWrite(green,85);
    break;

    case 4: 
      analogWrite(green,127);
    break;

    case 5:
      analogWrite(green,170);
    break;

    case 6:
      analogWrite(green,230);
    break;

    case 7:
      analogWrite(green,255);
    break;
  }
  
  currentbutton3=debounce3(lastbutton3);
  if(lastbutton3==LOW && currentbutton3==HIGH)
  {
    mode3++;
  }
  lastbutton3=currentbutton3;
  if(mode3==8)
  {
    mode3=1;
  }
  switch(mode3)
  {
    case 1: //off
      digitalWrite(blue,LOW);
    break;

    case 2: //low
      analogWrite(blue,40);
    break;

    case 3:
      analogWrite(blue,85);
    break;

    case 4: 
      analogWrite(blue,127);
    break;

    case 5:
      analogWrite(blue,170);
    break;

    case 6:
      analogWrite(blue,230);
    break;

    case 7:
      analogWrite(blue,255);
    break;
  }
}
