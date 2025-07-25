#include <Arduino.h>
#include "SLOVAR.h"
#include "obekti.h"
#include "stateMachine.h"
#include "hall.h"

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
    // robot.allEncZero();
    
    
}

void loop(){
    // halls.Upd();
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    readPacket();

    sm.setSpd( 8.0 );
    sm.StateMachineUpd();
    // Serial.println(enc_3.get_tick());
    // robot.ShiftTurnR(3.5);
        
}