#include "I2Cdev.h"
#include "MPU6050.h"

//以下為mpu6050定義
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO
//以上為mpu6050定義
#include "./iGloves-functions.h"

iGloves glove;

void setup() {
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  
  Serial.begin(38400);
  
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.println("Testing device connections...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

  pinMode(pin_for_index, INPUT);
  pinMode(pin_for_ring, INPUT);
  pinMode(pin_for_light, OUTPUT);
  pinMode(pin_for_touch, INPUT);

  glove.launch();
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  int index = analogRead(pin_for_index);
  int ring = analogRead(pin_for_ring);
  int touched = digitalRead(pin_for_touch);

  int Accel[6];
  Accel[0] = ax;
  Accel[1] = ay;
  Accel[2] = az;
  Accel[3] = gx;
  Accel[4] = gy;
  Accel[5] = gz;
  int Bending[2];
  Bending[0] = index;
  Bending[1] = ring;

  glove.running(Accel, Bending, touched);
  
}
