#include <SparkFun_TB6612.h>
#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"

#define _SSID "yutoby"
#define _KEY  "19283746"

enum LockState {
    OPENED,
    CLOSED
};

class iLock {
public:
    iLock();

    void running(Motor motor_run);
    void launch();
    LockState getCurrentState();
private:
    void getInfFromCloud();
    void move(Motor motor_run);

    LockState currentState;
    String infoFromCloud;
    MCSDevice mcs;
    MCSControllerString channelLock;
};
