#include "iGloves-functions.h"

iGloves::iGloves(): mcs("DwHgZZlg", "qPJZlPGOOXeK3Xxc"), to_light("to_iLight"), to_lock("to_iLock"), _state("state"){
    current_state = WAITING_INFORMATION;
    acceleration[0] = 0;
    acceleration[1] = 0;
    acceleration[2] = 0;
    acceleration[3] = 0;
    acceleration[4] = 0;
    acceleration[5] = 0;
    bending[0] = 0;
    bending[1] = 0;
    touch = 0;  //stands for untouched
    mes = "";
    infoFromCloud = "";
}

void iGloves::running(int Acceleration[6], int Bending[2], int Touch){
    this->renewSensorData(Acceleration, Bending, Touch);
    if (current_state == WAITING_INFORMATION) {
        int first = digitalRead(pin_for_touch);
        delay(100);
        int second = digitalRead(pin_for_touch);
        delay(100);
        int third = digitalRead(pin_for_touch);
        delay(100);
        if (first == 1 && second == 1 && third == 1) {
            this->_state.set("changing state...");
            Serial.println("changing state...");
            this->current_state = this->gestureForChangeState();
        }
    }
    switch (this->current_state){
        //要讀感測器資料
        case CONTROL_LIGHT:
            delay(3000); //to avoid noise
            this->gestureForControlLight();
            break;
        case CONTROL_LOCK:
            delay(3000); //to avoid noise
            this->gestureForControlLock();
            break;
        case LIGHTING:
            delay(3000); //to avoid noise
            this->gestureForLighting();
            break;
    }
    if (this->finishGesture) {
        this->_state.set("gesture finished!");
        Serial.println("gesture finished!");
        this->finishGesture = false;
        this->mes = "";
        this->current_state = WAITING_INFORMATION;
        delay(2000);
    }

    while(!mcs.connected()){
        this->_state.set("re-connect to MCS...");
        Serial.println("re-connect to MCS...");
        mcs.connect();
        if(mcs.connected()) {
            this->_state.set("MCS connected !!");
            Serial.println("MCS connected !!");
        }
    }
}

GloveState iGloves::gestureForChangeState(){
    delay(1000);
    //連續讀10個touch，若全都是1，則進入LIGHTING
    bool enter_Lighting = true;
    for (int i = 0; i < 10; i++){
        if (digitalRead(pin_for_touch) != 1) {
            enter_Lighting = false;
            break;
        }
        delay(50);
    }
    if (this->bending[0] <= 2700 && this->bending[1] <= 2700){  //會優先判斷，所以就算連讀10個1也不會進到lighting state
        this->_state.set("enter controlling iLock state");
        Serial.println("enter controlling iLock state");
        return CONTROL_LOCK;
    }
    else if (this->acceleration[1] >= 7000){
       this->_state.set("enter controlling iLight state");
       Serial.println("enter controlling iLight state");
        return CONTROL_LIGHT;
    }
    else if (enter_Lighting){
        this->_state.set("enter lighting state");
        Serial.println("enter lighting state");
        return LIGHTING;
    }
    else return WAITING_INFORMATION;
}

void iGloves::gestureForControlLight(){
    //讀資料
    this->bending[0] = analogRead(pin_for_index);
    this->bending[1] = analogRead(pin_for_ring);
    if (this->bending[0] <= 2700 && this->bending[1] <= 2700){
        this->_state.set("changing light color...");
        Serial.println("changing light color...");
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        this->acceleration[0] = ax; this->acceleration[1] = ay; this->acceleration[2] = az;
        this->acceleration[3] = gx; this->acceleration[4] = gy; this->acceleration[5] = gz;
        //for (int i = 0; i < 6; i++) this->_state.set(this->acceleration[i]);
        if (this->acceleration[0] > 0){
            while (true){
                accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
                this->acceleration[0] = ax; this->acceleration[1] = ay; this->acceleration[2] = az;
                this->acceleration[3] = gx; this->acceleration[4] = gy; this->acceleration[5] = gz;
                if (this->acceleration[0] > 0){
                    this->sendInfToLight("warmer");
                    delay(100);
                    this->sendInfToLight("exit");
                    break;
                }
                /*else if (this->acceleration[0] < 2000){
                    this->sendInfToLight("exit");
                    break;
                }*/
            }
        }
        else{
            while (true){
                accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
                this->acceleration[0] = ax; this->acceleration[1] = ay; this->acceleration[2] = az;
                this->acceleration[3] = gx; this->acceleration[4] = gy; this->acceleration[5] = gz;
                if (this->acceleration[0] <= 0){
                    this->sendInfToLight("colder");
                    delay(100);
                    this->sendInfToLight("exit");
                    break;
                }
                /*else if (this->acceleration[0] > 10000){
                    this->sendInfToLight("exit");
                    break;
                }*/
            }
        }
    }
    else if (this->bending[0] >= 2700 && this->bending[1] >= 2700){
        this->_state.set("changing light brightness..");
        Serial.println("changing light brightness..");
        accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        this->acceleration[0] = ax; this->acceleration[1] = ay; this->acceleration[2] = az;
        this->acceleration[3] = gx; this->acceleration[4] = gy; this->acceleration[5] = gz;
        //for (int i = 0; i < 6; i++) this->_state.set(this->acceleration[i]);
        if (this->acceleration[0] > 0){
            while (true){
                accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
                this->acceleration[0] = ax; this->acceleration[1] = ay; this->acceleration[2] = az;
                this->acceleration[3] = gx; this->acceleration[4] = gy; this->acceleration[5] = gz;
                if (this->acceleration[0] > 0){
                    this->sendInfToLight("brighter");
                    delay(50);
                    this->sendInfToLight("exit");
                    break;
                }
                /*else if (this->acceleration[0] < 2000){
                    this->sendInfToLight("exit");
                    break;
                }*/
            }
        }
        else{
            while (true){
                accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
                this->acceleration[0] = ax; this->acceleration[1] = ay; this->acceleration[2] = az;
                this->acceleration[3] = gx; this->acceleration[4] = gy; this->acceleration[5] = gz;
                if (this->acceleration[0] <= 0){
                    this->sendInfToLight("darker");
                    delay(50);
                    this->sendInfToLight("exit");
                    break;
                }
                /*else if (this->acceleration[0] > 7000){
                    this->sendInfToLight("exit");
                    break;
                }*/
            }
        }
    }
    this->finishGesture = true;
}

void iGloves::gestureForControlLock(){
    //讀資料
    int _index = analogRead(pin_for_index);
    int _ring = analogRead(pin_for_ring);
    bool to_exit = true;
    for (int i = 0; i < 3; i++){
        if (digitalRead(pin_for_touch) != 1){
            to_exit = false;
            break;
        }
        delay(50);
    }
    if (_index > 2700 && _ring > 2700) {
        if (!to_exit) this->sendInfToLock("open");
    }
    else if (_index <= 2700 && _ring <= 2700) this->sendInfToLock("close");
    this->finishGesture = true;
}

void iGloves::gestureForLighting(){
    digitalWrite(pin_for_light, HIGH);
    while (digitalRead(pin_for_touch) == 1){  //需要停止觸摸才進入下一階段
        delay(100);
    }

    delay(1000);

    while (true){
        bool to_exit = true;
        for (int i = 0; i < 3; i++){
            if (digitalRead(pin_for_touch) != 1){
                to_exit = false;
                break;
            }
            delay(50);
        }
        if (to_exit){
            this->_state.set("exit lighting state");
            Serial.println("exit lighting state");
            digitalWrite(pin_for_light, LOW);
            break;
        }
    }
    delay(2000);  //to avoid keep touching
    this->finishGesture = true;
}

void iGloves::sendInfToLock(String cmd){
    //use to_lock
    this->to_lock.set(cmd);
}

void iGloves::sendInfToLight(String cmd){
    //use to_light
    this->to_light.set(cmd);
}

void iGloves::renewSensorData(int Acceleration[6], int Bending[2], int Touch){
    for (int i = 0; i < 6; i++) this->acceleration[i] = Acceleration[i];
    for (int i = 0; i < 2; i++) this->bending[i] = Bending[i];
    this->touch = Touch;
}

void iGloves::launch(){
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
    this->mcs.addChannel(this->to_light);
    Serial.println("Channel to light created!");
    this->mcs.addChannel(this->to_lock);
    Serial.println("Channel to lock created!");
    this->mcs.addChannel(this->_state);
    Serial.println("Channel state created!");

    while (!this->mcs.connected()){
        Serial.println("MCS.connect()...");
        mcs.connect();
    }
    Serial.println("MCS connected !!");
}

GloveState iGloves:: getCurrentState(){
    return current_state;
}