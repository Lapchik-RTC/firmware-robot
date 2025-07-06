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

    // Enc[2].encZero();
    // Enc[3].encZero();
}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();
    printPacket();
    // readPacket();
    
    static float spLim = 50.0;
    int16_t velL = 0.0;
    int16_t velR = 0.0;

    // if(nado_rabotat())
    // {
    //     if(vpered()||vpravo()||vlevo()||nazad())
    //     {
            if(shift())
            {
                spLim = 30.0;
            }
            else
            {
                if(silentShift())
                {
                    spLim = 30.0;
                }
                else
                {
                    // privod[2].setPos( M_PI/6.0 );
                    // privod[3].setPos( M_PI/6.0 );
                    spLim = 10.0;
                }
            }
            int16_t vert = map(gamePad.RightThumbY, -32767, 32767, -spLim, spLim);
            int16_t horz = map(gamePad.RightThumbX, -32767, 32767, -spLim, spLim);

            if(gamePad.RightThumbY < 0)
            {
                horz= -horz;
            }
            velL = vert + horz;
            velR = vert - horz;

            // velL =  vert + ( spLim * horz );
            // velR = vert + ( spLim * -horz );

            // robot.wheel(velL, velR);
            // Serial.println(String(velL) + " " + String(velR));
            // Serial.println(String(Enc[0].()));
    //     }
    // }
    // else
    // {
    //     // robot.wheel(0.0, 0.0);
    //     if(!(vpered()||vpravo()||vlevo()||nazad()))
    //     {
    //         velL = 0.0;
    //         velR = 0.0;
    //     }
    // }//*/
    
   robot.wheel(velL, velR);
        // if(delsec_N())
        // {
        //     uint32_t tt = millis();
        //     while(millis() - tt < 1000)
        //     {
        //         robot.wheel(spLim, spLim );
        //         privod[0].tick();
        //         privod[4].tick();
        //         privod[5].tick();
        //         privod[1].tick();
        //     }

        //     robot.wheel(0, 0);
        //     Serial.println("000");
        // }
    // for(int i = 0; i < 6; i++)
    // {
    //     Serial.print( String(Enc[i].get_tick())  + " | ");
    // }
    // Serial.print(velL);
    // Serial.print("\t");
    // Serial.print(velR);
    // Serial.println();
    // if(vpravo()) Serial.print("vpravo   ");
    // if(vlevo()) Serial.print("vlevo   ");
    // if(nazad()) Serial.print("nazad   ");
    // if(vpered()) Serial.print("vpered   ");
    
    
    privod[0].tick();
    privod[2].tick();
    privod[4].tick();
    privod[5].tick();
    privod[1].tick();
    privod[3].tick();//*/
/*for(int i = 0; i < 50;i++)
{
    Dv[0].update_voltage_in_V(i);
    Dv[1].update_voltage_in_V(i);
    Dv[2].update_voltage_in_V(i);
    Dv[3].update_voltage_in_V(i);
    Dv[4].update_voltage_in_V(i);
    Dv[5].update_voltage_in_V(i); 
    Serial.println("--");
    delay(100);
}
for(int i = 50; i > 0; i--)
{
    Dv[0].update_voltage_in_V(i);
    Dv[1].update_voltage_in_V(i);
    Dv[2].update_voltage_in_V(i);
    Dv[3].update_voltage_in_V(i);
    Dv[4].update_voltage_in_V(i);
    Dv[5].update_voltage_in_V(i); 
    Serial.println("  00");
    delay(100);
}*/
    // Serial.println();
    // Serial.println();
}