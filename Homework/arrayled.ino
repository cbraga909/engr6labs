int ledPins[]={
  3,5,6,9,10,11
};
int pinCount=6

void setup() {
  // put your setup code here, to run once:
  for(int k=0; k<pinCount; k++){
    pinMode(ledPins[k],OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int k=0; k<pinCount;k++){
    digitalWrite(ledPins[k],HIGH);
    delay(500);
    digitalWrite(ledPins[k],LOW);
  }

}
