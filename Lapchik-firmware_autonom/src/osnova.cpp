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
    // robot.ostCalibr();
}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    static uint32_t timeWork = millis();
    // enc_3.enc_tick();
    // Serial.println(enc_3.get_tick());    
    int velo = 4.5;
    static bool a = 1;
    if (millis() - timeWork < 2100)
    {
        robot.Foo(velo);
    }
    else
    {

        if(a)
        {
            // robot.legDown(velo);
        
            a = 0;
            // perehodFix = 0;
            static uint32_t tWait_ = millis();
            statPosUpd();
            float ust = 0 + (M_PI/8.0);
            bool btest = 1;
            while((abs( modc(enc_3.get_phi(), 2.0*M_PI) ) > ust) && (millis() - tWait_ < 3000))
            {
                if(modc(enc_3.get_phi(), 2.0*M_PI) > M_PI)
                {
                    ust -= M_PI;
                    btest = 0;
                }
                serv3.setGoalPos(ust - modc(enc_3.get_phi(), 2.0*M_PI)); 
            }
            btest = 1;
            statPosUpd();
        }
        else
        {
            serv3.setGoalPos(posStatic[2]); 
            Serial.println( String(posStatic[2]) + String(modc(posStatic[2], 2.0*M_PI)));
            
        }
    }
}