#include <Arduino.h>
bool NCalibrMode = 0;
#include "SLOVAR.h"
#include "obekti.h"
#include "stateMachine.h"

void setup() {
    Serial.begin(115200);

    Serial1.begin(19200);

    memset(&gamePad, 0, sizeof(gamePad));

    // float tc = 2.0*M_PI;
    // float ts = 3.9;
    // float phiS = 0.5;
    // float phi0 = 0;
    // robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);

    // robot.calibr();
    // NCalibrMode = 1;
    // robot.allEncZero();
    
}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    readPacket();
    
    static float spLim = 5.0;
    if(nado_rabotat())
    {
        if(vpered()||vpravo()||vlevo()||nazad())
        {
            if(shift())
            {
                spLim = 10.0;
            }
            else
            {
                if(silentShift())
                {
                    spLim = 3.0;
                }
                else
                {
                    spLim = 5.0;
                }
            }
            float vert = map(gamePad.RightThumbY, -32768.0, 32768.0, -spLim, spLim);
            float horz = map(gamePad.RightThumbX, -32768.0, 32768.0, -1.0, 1.0);
            int16_t velL =  vert + ( spLim * horz );
            int16_t velR = vert - ( spLim * horz );

            robot.wheel(velL, velR);
        }
    }
    else
    {
        robot.wheel(0.0, 0.0);
    }

}