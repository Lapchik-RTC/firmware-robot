#include <Arduino.h>
#include "Parameters.h"
#include "Obj.h"
#include "f.h"
#include "softCheck.h"
#include "Pods.h"
#include "Rhex.h"
RHex rhex;

void StendUp()
{
    int n = 1, n2 = 3, n3 = 5;
    static uint32_t timerSt = millis();
    while (millis() - timerSt < 4000)
    {
        static float t = 0.0;
        if(t < 1.9) t += 1.5*Ts_s;

        Serv[0].setPos(t);
        Serv[1].setPos(t);
        Serv[2].setPos(t);
        Serv[3].setPos(t);
        Serv[4].setPos(t);
        Serv[5].setPos(t);

        Serv[0].tick();
        Serv[1].tick();
        Serv[2].tick();
        Serv[3].tick();
        Serv[4].tick();
        Serv[5].tick();
    }

    // Serv[0].zeroEnc();
    // Serv[1].zeroEnc();
    // Serv[2].zeroEnc();
    // Serv[3].zeroEnc();
    // Serv[4].zeroEnc();
    // Serv[5].zeroEnc();
    
    Serv[0].setPos(0.0);
    Serv[1].setPos(0.0);
    Serv[2].setPos(0.0);
    Serv[3].setPos(0.0);
    Serv[4].setPos(0.0);
    Serv[5].setPos(0.0);

    // rhex.ClassicWalk(0.0);
    // for(int i = 0; i < 6; i++)
    //     Serv[i].tick();


    // Serv[n].tick();
    // Serv[n2].tick();
    // Serv[n3].tick();



    // rhex.tick();

    // for(int i = 0; i < 6; i++)
    //     Serv[i].setPos(0.0);
    // for(int i = 0; i < 6; i++)
    //     Serv[i].tick();

}


void setup() {
    Serial.begin(115200);
    // rhex.setParams(0.0, 2.0*M_PI, 3.9, 0.5, 0.0);


    
    rhex.setParams(0.0, 2.0*M_PI, 1.5, 0.4, 1.96);
    // StendUp();
    
}


void loop() {
    static uint64_t timer = micros();
    while(micros() - timer < Ts_us);
    timer = micros();
    
    
    // while (1);

    Serial.println("LOOP");
    rhex.ClassicWalk(2.0);
    // rhex.tick();
    for(int i = 0; i < 6; i++)
    {
        Serv[i].tick();
    }
    // Serv[1].tick();
    // Serv[3].tick();
    // Serv[5].tick();


    // StendUp();
    // while(1)
    // {
    //     for(int i = 0; i < 6; i++)
    //     {
    //         Serv[i].setPos(0.0);
    //         Serv[i].tick();
    //     }
    // }
    
}
