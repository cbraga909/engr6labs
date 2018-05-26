//Define pins
const int led=9;
const int cds=A0;
const int pir=2;
int count=0;
int val=0;
boolean currentbutton=LOW;
boolean lastbutton=LOW;
int k=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  pinMode(cds,INPUT);
  pinMode(pir,INPUT);
  digitalWrite(led,LOW);
  Serial.begin(9600);
}

//Create debounce function
boolean debounce(boolean last)
{
  boolean current=digitalRead(pir);
  if(last!=current)
  {
    delay(5);
    current=digitalRead(pir);
  }
  return current;
}
void loop() {
  // put your main code here, to run repeatedly:
  //Use debounce function to ensure that it does not continuously count, and increments neatly
  currentbutton=debounce(lastbutton);
  //If the pir is high, the light will turn on, and the count increments by one
  if(lastbutton==LOW && currentbutton==HIGH)
  {
    digitalWrite(led,HIGH);
    count++;
    Serial.print("Count: ");
    Serial.println(count);
  }
  lastbutton=currentbutton;
  //If the pir is low, we will do one of two things depending on the reading of the light sensor
  if(currentbutton==LOW)
  {
    val=analogRead(cds);
    //If the light sensor is uncovered, the reading will be over 300 and therefore I write the led low
    if(val>300 && digitalRead(pir)==LOW)
    {
      digitalWrite(led,LOW);
    }
    //If the light sensor is covered, the reading will be 300 or less
    //I therefore want the led to blink the amount of times the pir has been activated
    if(val<=300 && digitalRead(pir)==LOW)
    {
      //By using a while loop, I can have the code to make the LED blink the amount of times I want it to
      while(k<=count)
      {
        digitalWrite(led,HIGH);
        delay(250);
        digitalWrite(led,LOW);
        delay(250);
        k++;
        //Once I reach the count, I reset k to 0 and write the LED low for 1000 milliseconds to indicate a reset
        if(k==count)
        {
          k=0;
          digitalWrite(led,LOW);
          delay(1000);
          break;
        }
      }
    }
  }
}
