#include <Arduino.h>
bool calibr152 = 0;
bool perehodFix = 1;
float posStatic[6] = {0,0,0,0,0,0};

#include "encoder.h"
#include "obekti.h"
#include "orkestr.h"

// #include "subStateMachine.h"
void setDefaultParams()
{
    robot.setParams(0, 2.0*M_PI, 2.7, 0.5, 0);
}
void setup() {
    Serial.begin(115200);

    float tc = 2.0*M_PI;
    float ts = 2.7;
    float phiS = 0.5;
    float phi0 = 0;
    robot.setParams(0/*M_PI*/, tc, ts, phiS, phi0);
    
    robot.ostCalibr();
    enc_1.encZero();
    enc_2.encZero();
    enc_3.encZero();
    enc_4.encZero();
    enc_5.encZero();
    enc_6.encZero();
    // robot.setParams(M_PI, 2.0*M_PI, 1.9, 0.5, 0);
}

void loop(){
    static uint64_t timer = micros();
    while(micros() - timer < Ts_s);
    timer = micros();

    static uint32_t timeWork = millis();
    
    float velo = 0.0;
    for(int i = 0; i < 4; i++){
    timeWork = millis();
    int ft = 2700;
    while(millis() - timeWork < ft)
    {
        robot.Foo(4.5);
    }
    
    timeWork = millis();
    while(millis() - timeWork < 1000)
    {
        robot.Foo(0);
    }

    timeWork = millis();
    robot.ts = 3.0;
    while(millis() - timeWork < 3000)
    {
        robot._turnL(3.0);
    }
    robot.ts = 2.7;
    timeWork = millis();
    while(millis() - timeWork < 1000)
    {
        robot.Foo(0);
    }
}
while(1)
{
    robot.Foo(0);
}

    // for(static int i = 0; i < 1; i++)
    //     robot.setParams(0/*M_PI*/, 2.0*M_PI, 5.0, 0.5, 0);
    // robot._turnL(6.0);
    // if(millis() - timeWork < 3000)
    // {
    //     velo = 4.5;
    //     robot.Foo(velo);
    // }
    // else
    // {
    //     if(millis() - timeWork < 4000)
    //     {
    //         velo = 0;
    //         robot.Foo(velo);
            
    //     }
    //     else
    //     {
    //         if(millis() - timeWork < 10000)
    //         {
                
    //             robot._turnL(3.0);
    //         }
    //         else
    //         {
    //             if(millis() - timeWork < 13000)
    //             {
    //                 velo = 4.5;
    //                 robot.Foo(velo);
    //             }
    //             else
    //             {
    //                 velo = 0;
    //                 robot.Foo(velo);
    //             }
    //         }
    //     }
    // }













    // while(millis() - timeWork < 1000)
    // {
    //     robot.Foo(velo);
    // }
    // if(millis() - timeWork < 1000)
    // {
    //     static bool flag = 1;
    //     if(flag)
    //     {
    //         robot.legDown2();
    //         flag = 0;
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
    //     }
    // }
    
}