#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <dht.h>
#define dht_apin A3
#define samp_siz 20
#define rise_threshold 5
int shockSensorPin = 2,first_parameter;
float accelaration,new_accelaration[3],old_accelaration[3]={0},old_velocity=0,new_velocity,distance=0;
bool shockSensorSate = 0;
int sensorPin = 0,count=0;
int buzzer = 10;
int smokeA0 = A5;
int sensorThres = 700;
Adafruit_MPU6050 mpu;
dht DHT;
void heartbeat(void);
void mpu_param(void);
void temp_humid(void);
int smoke(void);
void setup() {
pinMode(buzzer, OUTPUT);
pinMode(smokeA0, INPUT);
pinMode(shockSensorPin,INPUT);
pinMode(3,OUTPUT);
shockSensorSate = digitalRead(shockSensorPin);
Serial.begin(9600);
while (!Serial)
    delay(10);
  if (!mpu.begin()) {
    while (1) {
      delay(10);
    }
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
}
void loop() {
  int smoke_state;
  if (shockSensorSate == 1){
      digitalWrite(3, HIGH);
      Serial.print("PseudoBits Welcome you\n");
      delay(2000);
      while(1){
      Serial.print("Press\n1.Fitness Tracking\n2. Surrounding Parameters\n");
      while (Serial.available() == 0)   
      {   } 
      first_parameter=Serial.read();
      switch (first_parameter){
        case 49: Serial.print("Hiii.... Shubham Welcome to your Fitness Tracking System\n");
                Serial.print("I hope you will do much better today\n");
                delay(2000);
                heartbeat();
                break;
        case 50: Serial.print("Wait...\n");
                 delay(1000);
                 tmp_humid();
                 smoke_state=smoke();
                 Serial.print("Smoke level: ");
                 Serial.print(smoke_state);
                 Serial.print("\n");
                 break;
        default: Serial.print("Wrong Input...");
      }
      }
  }
    else {
      shockSensorSate = digitalRead(shockSensorPin);  
   }
}
void heartbeat()
{
  float reads[samp_siz], sum;
  long int now, ptr;
  float last, reader, start;
  float first, second, third, before, print_value;
  bool rising;
  int rise_count;
  int n,count=0;
  long int last_beat;
  for (int i = 0; i < samp_siz; i++)
    reads[i] = 0;
  sum = 0;
  ptr = 0;
  while (1)
  {
    n = 0;
    start = millis();
    reader = 0.;
    do
    {
      reader += analogRead (sensorPin);
      n++;
      now = millis();
    }
    while (now < start + 20);
    reader /= n;  // we got an average
    sum -= reads[ptr];
    sum += reader;
    reads[ptr] = reader;
    last = sum / samp_siz;
    if (last > before)
    {
      rise_count++;
      if (!rising && rise_count > rise_threshold)
      {
        // Ok, we have detected a rising curve, which implies a heartbeat.
        // Record the time since last beat, keep track of the two previous
        // times (first, second, third) to get a weighed average.
        // The rising flag prevents us from detecting the same rise
        // more than once.
        rising = true;
        first = millis() - last_beat;
        last_beat = millis();
        // Calculate the weighed average of heartbeat rate
        // according to the three last beats
        print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third);
        if (print_value<40 || print_value>80){
          Serial.print("Please Insert finger.....\n");
        }
        else{
          Serial.print("Heartbeat: ");
          Serial.print(print_value);
          Serial.print('\n');
        }
        
        mpu_param();
        count++;
        if (count>=30){
          break;
        }
        third = second;
        second = first;
      }
    }
    else
    {
      // Ok, the curve is falling
      rising = false;
      rise_count = 0;
    }
    before = last;
    ptr++;
    ptr %= samp_siz;
  }
  
}
void mpu_param()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  new_accelaration[0]=a.acceleration.x;
  new_accelaration[1]=a.acceleration.y;
  new_accelaration[2]=a.acceleration.z;
  accelaration=sqrt(pow(new_accelaration[0],2)+pow(new_accelaration[1],2)+pow(new_accelaration[2],2));
  Serial.print("Accelaration is :");
  Serial.print(accelaration-8.60);
  Serial.println(" m/s^2");
  
  new_velocity=sqrt(pow((new_accelaration[0]-old_accelaration[0]),2)+pow((new_accelaration[1]-old_accelaration[1]),2)+pow((new_accelaration[2]-old_accelaration[2]),2));
  Serial.print("Speed is :");
  Serial.print(new_velocity);
  Serial.println(" m/s");

  distance+=sqrt(pow((old_velocity-new_velocity),2));
  Serial.print("Distance Covered :");
  Serial.print(distance-17.35);
  Serial.println(" m");
  for (int i=0;i<3;i++){
    old_accelaration[i]=new_accelaration[i];
  }
  old_velocity=new_velocity;
  Serial.print("Angular velocity is:");
  Serial.print(sqrt(pow(g.gyro.x,2)+pow(g.gyro.y,2)+pow(g.gyro.z,2)));
  Serial.print("rad/sec\n");

  Serial.println("");
  delay(100);
}
void tmp_humid(){
  DHT.read11(dht_apin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%\n");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    delay(2000);
}
int smoke(){
  int analogSensor = analogRead(smokeA0);
  // Checks if it has reached the threshold value
  if (analogSensor > sensorThres)
  {
    tone(buzzer, 1000, 200);
  }
  else
  {
    noTone(buzzer);
  }
  
  delay(1000);
  return analogSensor;
}
