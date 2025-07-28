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

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    // readPacket();

    static float a = 0.0;
    static bool e = 1;
    robot.Foo(3.0);
    
    // serv[0].setGoalPos(0.0);
    // serv[1].setGoalPos(0.0);
    // serv[2].setGoalPos(0.0);
    // serv[3].setGoalPos(0.0);
    // serv[4].setGoalPos(0.0);
    // serv[5].setGoalPos(0.0);

    // if(encod[3].get_phi() <= 20.0*M_PI)
    // {
    //     serv[n].setGoalSpeed(8.0);
    // }
    // else
    // {
    //     if(e)
    //     {
    //         e = 0;
    //         a = encod[n].get_phi();
    //     }
        // serv[n].setGoalPos(a);
    // }
    

    // Serial.print("          " + String(t_test)+ "          ");
    for(int i = 0; i < 6; i++)
    {
        serv[i].tick();
    }

    // sm.setSpd( 8.0 );
    // sm.StateMachineUpd();
    
}