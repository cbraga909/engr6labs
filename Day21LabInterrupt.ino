const int ButtonInt=0;
const int red=11;
const int yellow=10;
const int green=9;
volatile int selectLED=red;
int lastLED=green;
void setup() {
  pinMode(red,OUTPUT);
  pinMode(yellow,OUTPUT);
  pinMode(green,OUTPUT);
  attachInterrupt(ButtonInt,swap,RISING);
  Serial.begin(9600);
}

void swap()
{
  analogWrite(selectLED,0);
  if(lastLED==red)
  {
    selectLED=yellow;
  }
  else if(lastLED==yellow)
  {
    selectLED=green;
  }
  else if(lastLED==green)
  {
    selectLED=red; 
  }
  lastLED=selectLED;
  Serial.println(selectLED);
}
void loop() {
  for(int i=0; i<256; i++)
  {
    analogWrite(selectLED,i);
    delay(10);
  }
  for(int i=255; i>=0; i--)
  {
    analogWrite(selectLED,i);
    delay(10);
  }
}
