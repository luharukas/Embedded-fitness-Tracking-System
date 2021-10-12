
int shockSensorPin = 2,first_parameter;
bool shockSensorSate = 0;
void setup() {
pinMode(shockSensorPin,INPUT);
shockSensorSate = digitalRead(shockSensorPin);
Serial.begin(9600);
}

void loop() {
  
  if (shockSensorSate == 1){
      Serial.print("PseudoBits Welcome you\n");
      delay(2000);
      Serial.print("Press\n1.Fitness Tracking\n2. Surrounding Parameters\n");
      first_parameter=Serial.read();
      switch (first_parameter){
        case 1: Serial.print("Hii\n");
                break;
        case 2: Serial.print("Hello\n");
                break;
      }
      
      Serial.print("Hiii.... Shubham Welcome to your Fitness Tracking System\n");
      Serial.print("I hope you will do much better today\n");
  }
    else {
      shockSensorSate = digitalRead(shockSensorPin);
      
   }
  
  

}
