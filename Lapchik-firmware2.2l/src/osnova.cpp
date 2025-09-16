#include <Arduino.h>
#include "SLOVAR.h"
#include "obekti.h"
#include "stateMachine.h"
// #include "hall.h"
#include "softCheck.h"

void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);
    
    memset(&gamePad, 0, sizeof(gamePad));

    // sm.preState();
    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    // robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);
    robot.setParams(0/*M_PI*/, tc, 2.4, 0.25, phi0);
    robot.calibr();
    robot.allEncZero();
}

void loop() {
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    
    robot.Foo(3.0, 0.0, 0.0);

    serv[0].tick();
    serv[1].tick();
    serv[2].tick();
    serv[3].tick();
    serv[4].tick();
    serv[5].tick();
}