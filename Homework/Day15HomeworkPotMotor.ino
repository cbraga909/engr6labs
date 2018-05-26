//Simple Motor Speed Control Program
const int MOTOR=9; //Motor on Digital Pin 9
const int pot=A0; //Potentiometer on analog pin A0
void setup()
{
 pinMode (MOTOR, OUTPUT);
}
void loop()
{
 int val=analogRead(pot);
 val=map(val,0,1023,0,255);
 analogWrite(MOTOR,val);
}


