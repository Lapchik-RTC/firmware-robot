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
    // robot.calibr();
    robot.allEncZero();
    
    
}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    // readPacket();

    static float a = 0.0;
    static bool e = 1;
    if(encod[1].get_phi() <= 10.0*M_PI)
        robot.Foo(3.0);
    else
    {
        if(e) a = encod[1].get_phi();
        serv[1].setGoalPos(a);
        
    }
    

    // Serial.print("          " + String(t_test)+ "          ");
    // for(int i = 0; i < 6; i++)
    // {
        serv[1].tick();
    // }

    // sm.setSpd( 8.0 );
    // sm.StateMachineUpd();
    
}