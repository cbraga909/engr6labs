void setup() {
  // put your setup code here, to run once:

pinMode(11, OUTPUT);
pinMode(10, OUTPUT);
pinMode(9, OUTPUT);
pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(11, HIGH);
  
  delay(500);
  digitalWrite(11,LOW);
  digitalWrite(10,HIGH);
  
  delay(500);
  digitalWrite(10,LOW);
  digitalWrite(9,HIGH);
  
  delay(500);
  digitalWrite(9,LOW);
  
  delay(100);
  digitalWrite(11, HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(9,HIGH);
  delay(100);
  digitalWrite(11, LOW);
  digitalWrite(3,LOW);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
  delay(100);
  digitalWrite(11, HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(9,HIGH);
  delay(100);
  digitalWrite(11, LOW);
  digitalWrite(3,LOW);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
  delay(100);
  digitalWrite(11, HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(9,HIGH);
  delay(100);
  digitalWrite(11, LOW);
  digitalWrite(3,LOW);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
  delay(100);
  digitalWrite(11, HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(9,HIGH);
  delay(1000);
  digitalWrite(11, LOW);
  digitalWrite(3,LOW);
  digitalWrite(10,LOW);
  digitalWrite(9,LOW);
  delay(500);
}
