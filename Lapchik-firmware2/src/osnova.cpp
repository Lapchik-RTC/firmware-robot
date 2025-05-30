#include <Arduino.h>
#include "SLOVAR.h"
#include "stateMachine.h"
#include "hall.h"
#include "obekti.h"

StateMachine sm;
Hall halls;
void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);
    
    memset(&gamePad, 0, sizeof(gamePad));

    halls.Init();
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
    readPacket();
    // halls.Upd();

    sm.setSpd( 4.0 );
    sm.StateMachineUpd();

    // robot.ladFoo(3.5);

    // static int pos= 0;
    // static bool q = 1;
    /*if(halls.getCondition(1))
    {
        serv5.setGoalSpeed(0.5);
    }
    else
    {
        if(q) {pos = enc_5.get_phi(); q=0;}
        serv5.setGoalPos(pos);
    }*/
    // Serial.println(halls.getCondition(3));
    
    // robot.Foo(7.0);
    
    
    // enc_1.enc_tick();
    // Serial.println(enc_4.get_tick());

    // Serial.println(
    //     "enc1: "+ String(modc(enc_1.get_phi(), 2.0*M_PI)) +
    //     "\tenc4: "+ String(modc(enc_4.get_phi(), 2.0*M_PI)) +
    //     "\tenc5: "+ String(modc(enc_5.get_phi(), 2.0*M_PI))
    // );
        
}