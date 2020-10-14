#include "iLight.h"

iLight::iLight(): mcs("D9e4h3ov", "pT0Yz4XDXUx54WiJ"), channelLight("for_iLight"){
    currentState = STEADY;
    lightStacks[0].R = 100;
    lightStacks[0].G = 100;
    lightStacks[0].B = 100;
    lightStacks[1].R = 100;
    lightStacks[1].G = 100;
    lightStacks[1].B = 100;
    lightStacks[2].R = 100;
    lightStacks[2].G = 100;
    lightStacks[2].B = 100;
    infoFromCloud = "";
}

int iLight::maximum(int first, int second, int third){
    if (first >= second && first >= third) return first;
    if (second >= first && second >= third) return second;
    if (third >= first && third >= second) return third;
}

int iLight::minimum(int first, int second, int third){
    if (first <= second && first <= third) return first;
    if (second <= first && second <= third) return second;
    if (third <= first && third <= second) return third;
}

void iLight::changeState(){
    if (this->infoFromCloud == "warmer" || this->infoFromCloud == "colder") this->currentState = CHANGING_COLOR;  //need to be modify
    else if (this->infoFromCloud == "brighter" || this->infoFromCloud == "darker") this->currentState = CHANGING_BRIGHTNESS;  //need to be modify
    else if (this->infoFromCloud == "exit")this->currentState = STEADY;
}

void iLight::getInfFromCloud(){
    mcs.process(100);
    if (this->channelLight.updated()) {
        infoFromCloud = this->channelLight.value();
        Serial.println("Upgraded!");
        Serial.println(this->infoFromCloud);
    }
}

void iLight::changeBrightness(){
    this->getInfFromCloud();
    if (this->infoFromCloud == "brighter"){  //need to be modify
        delay(500);
        Serial.println("brighter");
        //if (this->maximum(lightStacks[0].R, lightStacks[0].G, lightStacks[0].B) + 30 >=0 && this->maximum(lightStacks[0].R, lightStacks[0].G, lightStacks[0].B) + 30 <= 255) {
            lightStacks[0].R = 255;
            lightStacks[0].G = 255;
            lightStacks[0].B = 255;
        //}
        //if (this->maximum(lightStacks[1].R, lightStacks[1].G, lightStacks[1].B) + 20 >=0 && this->maximum(lightStacks[1].R, lightStacks[1].G, lightStacks[1].B) + 20 <= 255) {
            lightStacks[1].R = 255;
            lightStacks[1].G = 255;
            lightStacks[1].B = 255;
        //}
        //if (this->maximum(lightStacks[2].R, lightStacks[2].G, lightStacks[2].B) + 10 >=0 && this->maximum(lightStacks[2].R, lightStacks[2].G, lightStacks[2].B) + 10 <= 255) {
            lightStacks[2].R = 255;
            lightStacks[2].G = 255;
            lightStacks[2].B = 255;
        //}
    }
    else if (this->infoFromCloud == "darker"){  //need to be modify
        delay(500);
        Serial.println("darker");
        //if (this->minimum(lightStacks[0].R, lightStacks[0].G, lightStacks[0].B) - 30 >=0 && this->minimum(lightStacks[0].R, lightStacks[0].G, lightStacks[0].B) - 30 <= 255) {
            lightStacks[0].R = 0;
            lightStacks[0].G = 0;
            lightStacks[0].B = 0;
        //}
        //if (this->minimum(lightStacks[1].R, lightStacks[1].G, lightStacks[1].B) - 20 >=0 && this->minimum(lightStacks[1].R, lightStacks[1].G, lightStacks[1].B) - 20 <= 255) {
            lightStacks[1].R = 0;
            lightStacks[1].G = 0;
            lightStacks[1].B = 0;
        //}
        //if (this->minimum(lightStacks[2].R, lightStacks[2].G, lightStacks[0].B) - 10 >=0 && this->minimum(lightStacks[2].R, lightStacks[2].G, lightStacks[2].B) - 10 <= 255) {
            lightStacks[2].R = 0;
            lightStacks[2].G = 0;
            lightStacks[2].B = 0;
        //}
    }
    else if (this->infoFromCloud == "exit"){  //need to be modify
        this->currentState = STEADY;
    }
}

void iLight::changeColor(){
    this->getInfFromCloud();
    if (this->infoFromCloud == "warmer"){  //need to be modify
        delay(500);
        Serial.println("warmer");
        /*if (lightStacks[0].R + 20 <= 255) lightStacks[0].R += 20;
        if (lightStacks[0].G >= 120) lightStacks[0].G -= 10;
        if (lightStacks[0].B - 20 >= 0) lightStacks[0].B -= 20;
        lightStacks[1].R = lightStacks[0].R / 2;
        lightStacks[1].G = lightStacks[0].G / 2;
        lightStacks[1].B = lightStacks[0].B / 2;
        lightStacks[2].R = lightStacks[0].R / 20;
        lightStacks[2].G = lightStacks[0].G / 20;
        lightStacks[2].B = lightStacks[0].B / 20;*/
        lightStacks[0].R = 255;
        lightStacks[0].G = 0;
        lightStacks[0].B = 0;
        lightStacks[1].R = 170;
        lightStacks[1].G = 0;
        lightStacks[1].B = 0;
        lightStacks[2].R = 80;
        lightStacks[2].G = 0;
        lightStacks[2].B = 0;
    }
    else if (this->infoFromCloud == "colder"){  //need to be modify
        delay(500);
        Serial.println("colder");
        /*if (lightStacks[0].R - 20 >= 0) lightStacks[0].R -= 20;
        if (lightStacks[0].G <= 180) lightStacks[0].G += 10;
        if (lightStacks[0].B + 20 <= 255) lightStacks[0].B += 20;
        lightStacks[1].R = lightStacks[0].R / 2;
        lightStacks[1].G = lightStacks[0].G / 2;
        lightStacks[1].B = lightStacks[0].B / 2;
        lightStacks[2].R = lightStacks[0].R / 20;
        lightStacks[2].G = lightStacks[0].G / 20;
        lightStacks[2].B = lightStacks[0].B / 20;*/
        lightStacks[0].R = 0;
        lightStacks[0].G = 200;
        lightStacks[0].B = 255;
        lightStacks[1].R = 0;
        lightStacks[1].G = 120;
        lightStacks[1].B = 175;
        lightStacks[2].R = 0;
        lightStacks[2].G = 40;
        lightStacks[2].B = 95;
    }
    else if (this->infoFromCloud == "exit"){  //need to be modify
        this->currentState = STEADY;
    }
}

void iLight::output(){
    analogWrite(stack1_R,lightStacks[0].R);
    analogWrite(stack1_G,lightStacks[0].G);
    analogWrite(stack1_B,lightStacks[0].B);
    analogWrite(stack2_R,lightStacks[1].R);
    analogWrite(stack2_G,lightStacks[1].G);
    analogWrite(stack2_B,lightStacks[1].B);
    analogWrite(stack3_R,lightStacks[2].R);
    analogWrite(stack3_G,lightStacks[2].G);
    analogWrite(stack3_B,lightStacks[2].B);
}

void iLight::running(){
    this->getInfFromCloud();
    //Serial.println(this->infoFromCloud);
    if (currentState == STEADY) this->changeState();
    switch (this->currentState){
        case CHANGING_COLOR:
            this->changeColor();
            break;
        case CHANGING_BRIGHTNESS:
            this->changeBrightness();
            break;
    }
    this->output();
    //Serial.println(this->currentState);

    while(!mcs.connected()){
        Serial.println("re-connect to MCS...");
        mcs.connect();
        if(mcs.connected()) Serial.println("MCS connected !!");
    }
}

void iLight::launch(){
    while (WL_CONNECTED != WiFi.status()){
        Serial.print("WiFi.begin(");
        Serial.print(_SSID);
        Serial.print(",");
        Serial.print(_KEY);
        Serial.println(")...");
        WiFi.begin(_SSID, _KEY);
    }
    Serial.println("WiFi connected!");
    //mcs channel still need to be certified
    this->mcs.addChannel(this->channelLight);
    Serial.println("Light channel created!");

    while (!this->mcs.connected()){
        Serial.println("MCS.connect()...");
        mcs.connect();
    }
    Serial.println("MCS connected !!");

    while(!this->channelLight.valid()){
        Serial.println("read value from MCS...");
        this->channelLight.value();
    }
    Serial.print("done, value = ");
    Serial.println(this->channelLight.value());
}

LightState iLight::getCurrentState(){
    return this->currentState;
}
