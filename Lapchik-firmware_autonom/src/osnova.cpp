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
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();
    robot.ostCalibr();
}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();

    robot._turnL(1);

    // static uint32_t timeWork = millis();
    // // enc_3.enc_tick();
    // // Serial.println(enc_3.get_tick());    
    // int velo = 4.5;
    // static bool a = 1;
    // if (millis() - timeWork < 2100)
    // {
    //     robot.Foo(velo);
    // }
    // else
    // {
    //     if(a)
    //     {
    //         a = 0;
    //         static uint32_t tWait_ = millis();
    //         statPosUpd();
    //         float ust1 = 0 - (M_PI/8.0);
    //         float ust2 = 0 - (M_PI/8.0);
    //         float ust3 = 0 - (M_PI/8.0);
    //         float ust4 = 0 - (M_PI/8.0);
    //         float ust5 = 0 - (M_PI/8.0);
    //         float ust6 = 0 - (M_PI/8.0);
    //         bool btest = 1;
    //         while((millis() - tWait_ < 4000) &&
    //             (abs( modc(enc_1.get_phi(), 2.0*M_PI) ) > ust1) &&
    //             (abs( modc(enc_2.get_phi(), 2.0*M_PI) ) > ust2) &&
    //             (abs( modc(enc_3.get_phi(), 2.0*M_PI) ) > ust3) &&
    //             (abs( modc(enc_4.get_phi(), 2.0*M_PI) ) > ust4) &&
    //             (abs( modc(enc_5.get_phi(), 2.0*M_PI) ) > ust5) &&
    //             (abs( modc(enc_6.get_phi(), 2.0*M_PI) ) > ust6)                
    //         )
    //         {
    //             if(modc(enc_1.get_phi(), 2.0*M_PI) > M_PI)
    //             {
    //                 ust1 -= M_PI;
    //                 btest = 0;
    //             }
    //             serv1.setGoalPos(ust1 - modc(enc_1.get_phi(), 2.0*M_PI)); 

    //             if(modc(enc_2.get_phi(), 2.0*M_PI) > M_PI)
    //             {
    //                 ust2 -= M_PI;
    //                 btest = 0;
    //             }
    //             serv2.setGoalPos(ust2 - modc(enc_2.get_phi(), 2.0*M_PI)); 

    //             if(modc(enc_3.get_phi(), 2.0*M_PI) > M_PI)
    //             {
    //                 ust3 -= M_PI;
    //                 btest = 0;
    //             }
    //             serv3.setGoalPos(ust3 - modc(enc_3.get_phi(), 2.0*M_PI)); 

    //             if(modc(enc_4.get_phi(), 2.0*M_PI) > M_PI)
    //             {
    //                 ust4 -= M_PI;
    //                 btest = 0;
    //             }
    //             serv4.setGoalPos(ust4 - modc(enc_4.get_phi(), 2.0*M_PI)); 

    //             if(modc(enc_5.get_phi(), 2.0*M_PI) > M_PI)
    //             {
    //                 ust5 -= M_PI;
    //                 btest = 0;
    //             }
    //             serv5.setGoalPos(ust5 - modc(enc_5.get_phi(), 2.0*M_PI)); 

    //             if(modc(enc_6.get_phi(), 2.0*M_PI) > M_PI)
    //             {
    //                 ust6 -= M_PI;
    //                 btest = 0;
    //             }
    //             serv6.setGoalPos(ust6 - modc(enc_6.get_phi(), 2.0*M_PI)); 
    //         }
    //         btest = 1;
    //         statPosUpd();
    //     }
    //     else
    //     {
    //         serv1.setGoalPos(posStatic[0]); 
    //         serv2.setGoalPos(posStatic[1]);
    //         serv3.setGoalPos(posStatic[2]);
    //         serv4.setGoalPos(posStatic[3]);
    //         serv5.setGoalPos(posStatic[4]);
    //         serv6.setGoalPos(posStatic[5]);
    //         Serial.println( String(posStatic[2]) + String(modc(posStatic[2], 2.0*M_PI)));
    //     }
    // }
}