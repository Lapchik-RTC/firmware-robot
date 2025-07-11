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