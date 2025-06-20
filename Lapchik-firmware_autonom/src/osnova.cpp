#include <Arduino.h>
#include "SLOVAR.h"
#include "stateMachine.h"
// #include "hall.h"
#include "obekti.h"

StateMachine sm;
// Hall halls;
void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);

    memset(&gamePad, 0, sizeof(gamePad));

    // halls.Init();
    // sm.preState();
    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);
    robot.calibr();
    
    
}

void loop(){
    readPacket();
    sm.setSpd( 3.5 );
    // robot.Foo(3.5);
    // halls.Upd();
    
    sm.StateMachineUpd();
    
    // enc_3.enc_tick();
    // Serial.println(enc_3.get_tick());
        
}