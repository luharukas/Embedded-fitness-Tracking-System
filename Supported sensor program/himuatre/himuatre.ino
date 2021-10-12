#include <dht.h>
#define dht_apin A3 // Analog Pin sensor is connected to
dht DHT;
void setup(){
  Serial.begin(9600);
  delay(500);//Delay to let system boo
}
void loop(){
    tmp_humid();
}
void tmp_humid(){
  DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    delay(5000);
}
