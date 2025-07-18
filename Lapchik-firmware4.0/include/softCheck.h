#pragma once
#include <Arduino.h>
#include "Parameters.h"
#include "Obj.h"
void motorUcheck()
{
    static float testU = 0.0;
    static bool riseTestU = 1;
    if(riseTestU)
    {
        testU += 0.05;
        if(testU > SUPPLY_VOLTAGE)
        {
            riseTestU = 0;
        }
    }
    if(!riseTestU)
    {
        testU -= 0.05;
        if(testU < -SUPPLY_VOLTAGE)
        {
            riseTestU = 1;
        }
    }
    for(int i = 0; i < 6; i++)
    {
        Serv[i].setU(testU);
    }

}

void SpeedRegSens_R_F_pers(int n = 3)
{
    static float prs = 0, prs2 = 0;
    static float right = 1, fall = 1, all = 1;
    prs = (right/all)*100;
    prs2 = (fall/all)*100;
    Serial.print(String(prs) + "%   " + String(prs2) + "%     ");
    if(Serv[n].getRealSpd() > 2.8)
    {
      Serial.print("      w_rads   ");
      right++;
    }
    else
    {
      Serial.print("FALL   ");
      fall++;
    }
    all++;
    Serial.println(String(Serv[n].getRealSpd()));
}