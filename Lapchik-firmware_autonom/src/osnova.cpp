#include <Arduino.h>

#include "orkestr.h"
#include "stateMachine.h"

StateMachine sm;

void setup() {
    Serial.begin(115200);

    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);
    
    robot.ostCalibr();
    robot.allEncZero();

}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    readPacket();
    sm.StateMachineUpd();
}

//     static uint32_t timeWork = millis();
    
//     float velo = 0.0;
//     for(int i = 0; i < 4; i++){
//     timeWork = millis();
//     int ft = 2700;
//     while(millis() - timeWork < ft)
//     {
//         robot.Foo(4.5);
//     }
    
//     timeWork = millis();
//     while(millis() - timeWork < 1000)
//     {
//         robot.Foo(0);
//     }

//     timeWork = millis();
//     robot.ts = 3.0;
//     while(millis() - timeWork < 3000)
//     {
//         robot.turnL(3.0);
//     }
//     robot.ts = 2.7;
//     timeWork = millis();
//     while(millis() - timeWork < 1000)
//     {
//         robot.Foo(0);
//     }
// }
// while(1)
// {
//     robot.Foo(0);
// }