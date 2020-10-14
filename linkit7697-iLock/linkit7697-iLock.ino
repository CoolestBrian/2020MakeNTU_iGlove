#include <SparkFun_TB6612.h>

#define AIN1  15
#define AIN2  16
#define PWMA  17
#define STBY  11

const int offsetA = 1;  // 正反轉設定A，可能值為1或-1。
Motor motor_run = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

#include "./iLock.h"

iLock lock;

void setup() {
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  lock.launch();
}

void loop() {
  lock.running(motor_run);
}
