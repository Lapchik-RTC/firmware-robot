#include <Arduino.h>
bool calibr152 = 0;
bool perehodFix = 1;
float posStatic[6] = {0,0,0,0,0,0};

#include "encoder.h"
#include "obekti.h"
#include "orkestr.h"
Orkestr robot;

void setup() {
    Serial.begin(115200);

    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    
    robot.setParams(M_PI, tc, ts, phiS, phi0);
}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    static uint32_t timeWork = millis();
    robot.Foo(1.5);
    // while (millis() - timeWork < 5000)
    // {
    //     robot.Foo(1.5);
    // }
    // static bool a = 1;
    // if(a)
    // {
    //     robot.legDown(4.0);
    //     a = 0;
    //     statPosUpd();
    // }
    // else
    // {
    //     serv3.setGoalPos(posStatic[0]);
    // }
}