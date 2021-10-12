
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
float accelaration,new_accelaration[3],old_accelaration[3]={0},old_velocity=0,new_velocity,distance=0;
Adafruit_MPU6050 mpu;
void mpu_param(void);
void setup(void) {
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
  mpu_param();
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
  
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  delay(1000);
}
