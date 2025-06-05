#include <Arduino.h>
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
    robot.allEncZero();
    
}

/*void encToRoundCalibr()
{
    static uint32_t lastTimeDetect[6] = {millis(), millis(), millis(), millis(), millis(), millis()};
    static int32_t encOld[6] = {Enc[0].get_tick(), Enc[1].get_tick(), Enc[2].get_tick(), Enc[3].get_tick(), Enc[4].get_tick(), Enc[5].get_tick()};
    static int n[6] = {0, 0, 0, 0, 0, 0};
    float kT = 0.2;

    for(int i = 0; i < 6; i++)
    {
        if(digitalRead(hallPin[i]) == 0 && millis() - lastTimeDetect[i] > (350))
        {
            // kolvTickRate[i] = ( ((Enc[i].get_tick() - encOld[i]) * kT) + (kolvTickRate[i] * (1-kT)) );
            // encOld[i] = Enc[i].get_tick();
            if(i > 1)
            {
                Enc[i].setRotErr( 0.0 - modc(Enc[i].get_phi(), 2.0*M_PI) );
            }
            else
            {
                Enc[i].setRotErr( M_PI - modc(Enc[i].get_phi(), 2.0*M_PI) );
            }
            // n[i]++;
            // kolvTickRate[i] = abs(Enc[i].get_tick())/n[i];
               Serial.println(String(1111111111));
            lastTimeDetect[i] = millis();
        }
    }
}//*/

void loop(){

    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    // encToRoundCalibr();

    
    // readPacket();
    // sm.setSpd( 5.0 );
    // sm.StateMachineUpd();
    
    // robot.l2(M_PI/2.0);
    Serial.println(String( modc(Enc[1].get_phi(), 2.0*M_PI) ));
    robot.Foo(5.0);
    // privod[1].setGoalSpeed(0.0);
}