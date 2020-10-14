#include "./iLight.h"

iLight light;

void setup() {
  Serial.begin(9600);
  
  pinMode(stack1_R, OUTPUT);
  pinMode(stack1_G, OUTPUT);
  pinMode(stack1_B, OUTPUT);
  pinMode(stack2_R, OUTPUT);
  pinMode(stack2_G, OUTPUT);
  pinMode(stack2_B, OUTPUT);
  pinMode(stack3_R, OUTPUT);
  pinMode(stack3_G, OUTPUT);
  pinMode(stack3_B, OUTPUT);

  Serial.println("Begin!");
  light.launch();

  //below are testing code 
}

void loop() {
  light.running();

  //down are testing codes
  /*static int R = 161;
  static int G = 201;
  static int B = 255;

  //R = (R + 13) % 256;
  G = (G + 83) % 256;
  //B = (B + 79) % 256;
  
  analogWrite(stack1_R, 0);
  analogWrite(stack1_G, G);
  analogWrite(stack1_B, 0);

  delay(2000);
  analogWrite(stack2_R, 160);
  analogWrite(stack2_G, 140);
  analogWrite(stack2_B, 120);
  analogWrite(stack3_R, 120);
  analogWrite(stack3_G, 100);
  analogWrite(stack3_B, 80);*/

  
}
