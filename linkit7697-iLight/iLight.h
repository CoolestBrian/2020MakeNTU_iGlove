#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"

#define _SSID "yutoby"
#define _KEY  "19283746"

#define stack1_R 6
#define stack1_G 7
#define stack1_B 8
#define stack2_R 9
#define stack2_G 10
#define stack2_B 11
#define stack3_R 12
#define stack3_G 13
#define stack3_B 14

enum LightState {
    STEADY,
    CHANGING_COLOR,
    CHANGING_BRIGHTNESS
};

struct RGB {
    int R;
    int G;
    int B;
};

class iLight {
public:
    iLight();

    void running();
    void launch();
    LightState getCurrentState();
private:
    int maximum(int first, int second, int third);
    int minimum(int first, int second, int third);
    void changeState();
    void getInfFromCloud();
    void changeBrightness();
    void changeColor();
    void output();

    LightState currentState;
    RGB lightStacks[3];
    String infoFromCloud;
    MCSDevice mcs;
    MCSControllerString channelLight;
};