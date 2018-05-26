int tempPin = 1;
int val;
int red=11;
int green=10;
int blue=9;
//int temp=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(tempPin,INPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val=analogRead(tempPin);
  float mv=val*5000.0/1023;
  float temp=(mv-500.0)/10;
  Serial.println(val);
  Serial.println("Temperature");
  Serial.println(temp);
  delay(500);
  if(temp>22)
  {
    digitalWrite(red,HIGH);
    digitalWrite(green,LOW);
    digitalWrite(blue,LOW);
  }
  if(temp>=18 && temp<=22)
  {
    digitalWrite(red,LOW);
    digitalWrite(green,HIGH);
    digitalWrite(blue,LOW);
  }
  if(temp<18)
  {
    digitalWrite(red,LOW);
    digitalWrite(green,LOW);
    digitalWrite(blue,HIGH);
  }
}


