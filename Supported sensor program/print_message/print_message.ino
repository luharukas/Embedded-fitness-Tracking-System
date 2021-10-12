int Led=8;//
int Shock=3;//
int val;//
char old_thing[10];
char new_thing[10];
void setup()
{
pinMode(Led,OUTPUT);//
pinMode(Shock,INPUT);//
Serial.begin(9600);
}
void loop()
{
  val=digitalRead(Shock);
  if(val==HIGH)
  {
    digitalWrite(Led,HIGH);
    Serial.print("Enter\n");
    Serial.print("1. For HeartBeat Rate\n2. ");
    
  }
  else
  {
    digitalWrite(Led,LOW);
    Serial.print("OFF\n");
    
  }
}
