int counter=0;
int const button1=13;
int const button2=12;
int const switchbutton=2;
boolean last=LOW;
boolean current=LOW;
boolean b2stat=LOW;
boolean switchbstat=LOW;
int buttonstate=0;
int LED=9;


void setup() {
  Serial.begin(9600);
  pinMode(button1,INPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  switchbstat=digitalRead(button1);
  
  if(current!=last)
  {
    delay(150);
    if(current==HIGH)
    {
      counter++;
      int val=counter*85;
      analogWrite(LED,val);
    }
    if(counter==4)
    {
      counter=0;
      analogWrite(LED,0);
    }
    Serial.println(counter);
  }
}
