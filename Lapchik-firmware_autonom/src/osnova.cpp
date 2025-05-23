#include <Arduino.h>

#include "orkestr.h"
#include "stateMachine.h"

StateMachine sm;

void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);

    memset(&gamePad, 0, sizeof(gamePad));

    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);
    // robot.ostCalibr();
    // robot.allEncZero();

}

void loop(){
    // static uint64_t timer = micros();
    // while(micros() - timer < Ts_s);
    // timer = micros();
    printPacket();
    
    
    // robot.Foo(0);
}
