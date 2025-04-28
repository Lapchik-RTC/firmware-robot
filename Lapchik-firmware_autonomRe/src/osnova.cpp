#include <Arduino.h>
#include "SLOVAR.h"
#include "orkestr/orkestr.h"

// #include "subStateMachine.h"

void setup() {
    Serial.begin(115200);

    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    robot.setParams(M_PI, tc, ts, phiS, phi0);
    
    robot.ostCalibr();
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();
    // robot.setParams(M_PI, 2.0*M_PI, 1.9, 0.5, 0);
}
// SubStateMachine ssm;
// void foo(){Serial.println("foo");}
// void foo2(){Serial.println("foo2");}


void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();

    static uint32_t timeWork = millis();
    // enc_3.enc_tick();
    // Serial.println(enc_3.get_tick());    
    // static bool ld = 1;
    int velo = 4.5;
    robot.Foo(velo);
    // if (millis() - timeWork < 3100)
    // {
    //     robot.Foo(velo);
    // }
    // else
    // {
    //     static bool spu = 1;
        
    //     if(ld)
    //     {
            
            
    //         robot.legDown2();
    //         perehodFix = 1;
    //         ld = 0;
            
    //     }
    //     else
    //     {
    //         if(spu) {statPosUpd();spu = 0;}
    //         serv1.setGoalPos(posStatic[0]); 
    //         serv2.setGoalPos(posStatic[1]);
    //         serv3.setGoalPos(posStatic[2]);
    //         serv4.setGoalPos(posStatic[3]);
    //         serv5.setGoalPos(posStatic[4]);
    //         serv6.setGoalPos(posStatic[5]);
    //         // Serial.println( String(posStatic[3]) + String(modc(posStatic[3], 2.0*M_PI)));
    //         /*Serial.println(
    //             "enc_1: " + String(modc(enc_1.get_phi(), 2.0*M_PI)) + '\t' +
    //              "enc_2: " + String(modc(enc_2.get_phi(), 2.0*M_PI)) + '\t' +
    //              "enc_3: " + String(modc(enc_3.get_phi(), 2.0*M_PI)) + '\t' +
    //              "enc_4: " + String(modc(enc_4.get_phi(), 2.0*M_PI)) + '\t' +
    //              "enc_5: " + String(modc(enc_5.get_phi(), 2.0*M_PI)) + '\t' +
    //              "enc_6: " + String(modc(enc_6.get_phi(), 2.0*M_PI))
    //         );//*/
    //     }
    //}
}