#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"
#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"

extern MPU6050 accelgyro;
extern int16_t ax, ay, az;
extern int16_t gx, gy, gz;

//以下為wifi定義
#define _SSID "yutoby"
#define _KEY  "19283746"
//以上為wifi定義
//以下為手指的灣區感測器接腳
#define pin_for_index 16
#define pin_for_ring 17
//以上為手指的灣區感測器接腳
//以下為燈光的輸出接腳
#define pin_for_light 6
//以上為燈光的輸出接腳
//以下為觸摸感測器接腳
#define pin_for_touch 11
//以上為觸摸感測器接腳

enum GloveState {
    CONTROL_LIGHT,
    CONTROL_LOCK,
    LIGHTING,
    WAITING_INFORMATION
};

class iGloves {
public:
    iGloves();

    void running(int Acceleration[6], int Bending[2], int Touch);  //main code to run on arduino IDE
    void launch();  //initialization
    GloveState getCurrentState();  //return current state
private:
    GloveState gestureForChangeState();  //get gesture from user to change the item controlling
    void gestureForControlLight();  //get gesture from user to change smart light
    void gestureForControlLock();  //get gesture from user to unlock smart lock
    void gestureForLighting();  //get gesture from user to control light on glove
    //void getInfFromCloud();  //get information from cloud sandbox
    void sendInfToLock(String cmd);  //send TCP Data to cloud sandbox:Lock
    void sendInfToLight(String cmd);  //send TCP Data to cloud sandbox:Light
    void renewSensorData(int Acceleration[6], int Bending[2], int Touch);  //renew data from sensors on glove
    
    GloveState current_state;
    int acceleration[6];
    int bending[2]; 
    int touch;
    String mes;
    String infoFromCloud;
    bool finishGesture;
    MCSDevice mcs;
    MCSDisplayString to_light;//MCSControllerOnOff led
    MCSDisplayString to_lock;//MCSDisplayOnOff remote;
    MCSDisplayString _state;
};
