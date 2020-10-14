#include "iLock.h"

iLock::iLock() :mcs("DuEA00oC","AgAxdaJmywe1HKTG"), channelLock("for_iLock"){
    currentState = OPENED;
    infoFromCloud = "";
}

void iLock::running(Motor motor_run){
    this->getInfFromCloud();
    this->move(motor_run);

    while(!mcs.connected()){
        Serial.println("re-connect to MCS...");
        mcs.connect();
        if(mcs.connected()) Serial.println("MCS connected !!");
    }
    //Serial.println("loop finished");
}

void iLock::launch(){
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
    this->mcs.addChannel(this->channelLock);
    Serial.println("Lock channel created!");

    while (!this->mcs.connected()){
        Serial.println("MCS.connect()...");
        mcs.connect();
    }
    Serial.println("MCS connected !!");
}

LockState iLock::getCurrentState(){
    return this->currentState;
}

void iLock::getInfFromCloud(){
    mcs.process(100);
    if (this->channelLock.updated()) {
        this->infoFromCloud = this->channelLock.value();
        Serial.println(this->infoFromCloud);
    }
}

void iLock::move(Motor motor_run){
    if (this->currentState == OPENED && this->infoFromCloud == "close"){
        /*digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);  //direction need to be certified
        analogWrite(PWMA, 255);
        delay(1000);  //need to be modify*/
        motor_run.drive(255,1500);
        Serial.println("closing");
        motor_run.drive(0,100);
        //analogWrite(PWMA, 0);
        this->currentState = CLOSED;
    }
    else if (this->currentState == CLOSED && this->infoFromCloud == "open"){
        /*digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);  //direction need to be certified
        analogWrite(PWMA, 255);
        delay(1000);  //need to be modify*/
        motor_run.drive(-255,1500);
        Serial.println("opening");
        motor_run.drive(0,100);
        //analogWrite(PWMA, 0);
        this->currentState = OPENED;
    }
}
