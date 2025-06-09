#include <Arduino.h>
bool NCalibrMode = 0;
#include "SLOVAR.h"
#include "obekti.h"
#include "stateMachine.h"

void setup() {
    Serial.begin(115200);

    Serial1.begin(19200);

    memset(&gamePad, 0, sizeof(gamePad));

    
    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);

    // robot.calibr();
    NCalibrMode = 0;
    robot.allEncZero();
    
}


void encToRoundCalibr()
{
    static uint32_t lastTimeDetect[6] = {millis(), millis(), millis(), millis(), millis(), millis()};
    static int32_t encOld[6] = {Enc[0].get_tick(), Enc[1].get_tick(), Enc[2].get_tick(), Enc[3].get_tick(), Enc[4].get_tick(), Enc[5].get_tick()};
    static int n[6] = {0, 0, 0, 0, 0, 0};
    static int statErr = 0;
    static float statErrPhi = 0.0;
    static float Phi2R = 2.0*M_PI;
    float kT = 0.2;

    // for(int i = 0; i < 6; i++)
    // {
        int m = 2;
        if(digitalRead(hallPin[m]) == 0 && millis() - lastTimeDetect[m] > (500))
        {
            // kolvTickRate[1] = ( ((Enc[1].get_tick() - encOld[1]) * kT) + (kolvTickRate[1] * (1-kT)) );
            // encOld[i] = Enc[1].get_tick();
            // if(i > 1)
            // {
            //     Enc[i].setRotErr( 0.0 - modc(Enc[i].get_phi(), 2.0*M_PI) );
            // }
            // else
            // {
            //    Enc[1].setRotErr( M_PI - modc(Enc[i].get_phi(), 2.0*M_PI) );
            // }





            n[m]++;
            if(n[m]==1)
            {
                statErr = Enc[m].get_tick();
                statErrPhi = Enc[m].get_phi();
            }
            else
            {
                kolvTickRate[m] = (abs(Enc[m].get_tick()-statErr)/(n[m]-1));
                Phi2R = (abs(Enc[m].get_phi()-statErrPhi)/(n[m]-1));
            }



            
            lastTimeDetect[m] = millis();
        }
        Serial.println("enc2rot: "+String(kolvTickRate[m])+"\tphi2rot: "+String(Phi2R));
    // }
}//*/

void loop(){

    static uint64_t timer = micros();
    
    while(micros() - timer < Ts_s)
    {

    }
    Serial.println();

    timer = micros();
    for(int i = 0; i < 6; i++)
    {
        Enc[i].enc_tick();
    }
    encToRoundCalibr();
    // static uint64_t ti = millis();
    // static float p = 0.0;
    // static float phi_ = 0.0, phiOld = 0.0, stph = 0.0;
    // static int n = 0, t = 0;

    // if(digitalRead(hallPin[3]) == 0 && (millis() - ti > (500)))
    // {
    //     p+=2.0*M_PI;
    //     t+=kolvTickRate[1];
    //     n++;
    //     ti = millis();
    // }

    // if(n==1)
    // {
    //     stph = Enc[1].get_phi();
    // }
    
    
    // robot.Foo(7.0);
    // while (Enc[1].get_phi()<p)
    // {
    //     privod[1].setGoalSpeed(0.7); 
    // }
    // phi_ = Enc[1].get_phi() - phiOld;
    // Serial.println("t: " + String(t) +
    //                 "\ttick: " + String(Enc[1].get_tick()) + 

    //                 "\tphi: "+ String(Enc[1].get_phi())+
    //                 "\tp: " + String(p));
    // phiOld = Enc[1].get_phi();
    privod[2].setGoalSpeed(5.0);
    
    // robot.Foo(4.0);
}





    // readPacket();
    // sm.setSpd( 5.0 );
    // sm.StateMachineUpd();