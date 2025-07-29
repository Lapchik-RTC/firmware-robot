#include <Arduino.h>
#include "SLOVAR.h"
#include "obekti.h"
#include "stateMachine.h"
#include "hall.h"
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
    robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);
    robot.calibr();
    robot.allEncZero();
}

void loop() {
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    // readPacket();

    static float a = 0.0;
    static bool e = 1;
    
    static uint32_t timerTurn = millis();
    // if(millis() - timerTurn < 2000 && 1)
    // {
    //     robot.Foo(3.0, 0.0, 0.0);
    // }
    // else
    // {
    //     robot.Foo(3.0, 1.3, M_PI/14.5);
    // }

    robot.Foo(3.0, 0.0, 0.0);

    // if(modc(robot.t, 2.0*M_PI) == 2.0)
    // {
    //     robot.phi0 -= 0.5;
    // }
    
    for(int i = 0; i < 6; i++)
    {
        serv[i].tick();
    }
    float modPhi = modc(robot.t, 2.0*M_PI);

    if( modPhi > 0.0)
    {
        if(modPhi < 0.02)
        {
            robot.phi0 -= 0.025;
            // Serial.println("   ///");
        }
    }
    else
        Serial.println(robot.phi0);
    
}