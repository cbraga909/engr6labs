int counter = 100;
int mypins[]={
  11, 10, 9, 6, 5, 3
};
int pinCount =6;


void setup() {
  // put your setup code here, to run once:
  for (int k=0; k<pinCount; k++)
  {
    pinMode(mypins[k], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int k=0; k<pinCount; k++)
  {
    analogWrite(mypins[k],255);
    delay(counter);
    analogWrite(mypins[k],60);
    analogWrite(mypins[k-1],0);
    Serial.print("First Loop :");
    Serial.println(k);
  }
  for (int k=pinCount-1;k>=0; k--)
  {
    analogWrite(mypins[k],255);
    delay(counter);
    analogWrite(mypins[k],60);
    analogWrite(mypins[k+1],0);
    Serial.println("Second Loop :");
    Serial.println(k);
  }
}
